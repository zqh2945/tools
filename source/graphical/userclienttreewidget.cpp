#include "userclienttreewidget.h"
#include "../source/files/userclientlistfile.h"
#include "../source/files/userclientdatabasefile.h"
#include <QIcon>
#include <QDebug>


UserClientTreeWidget::UserClientTreeWidget() : QTreeWidget ()
{
    setColumnCount(8);
    setColumnHidden(0,false); //标题
    setColumnHidden(1,true); //状态
    setColumnHidden(2,true); //标准版本
    setColumnHidden(3,true); //MN
    setColumnHidden(4,true); //PW
    setColumnHidden(5,true); //ST
    setColumnHidden(6,true); //IP地址
    setColumnHidden(7,true); //端口
    setHeaderHidden(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(itemClickedHandle(QTreeWidgetItem*)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(itemDoubleClickedHandle(QTreeWidgetItem*)));
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(itemRightClickedHandle(QPoint)));
}

UserClientTreeWidget::~UserClientTreeWidget()
{

}
//判断是否是主项
bool UserClientTreeWidget::isMainItem(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) != -1) {
        return true;
    } else {
        return false;
    }
}
//查找主项
bool UserClientTreeWidget::findMainItem(const QString &mn)
{
    QList<QTreeWidgetItem*> list = findItems(mn,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        return true;
    } else {
        return false;
    }
}
//添加主项
void UserClientTreeWidget::addMainItem(const QStringList &baseInfo)
{
    QList<QTreeWidgetItem*> list = findItems(baseInfo.at(1),Qt::MatchCaseSensitive,0);
    if(list.count()==0 && baseInfo.count()>=4) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setIcon(0,QIcon(":/tree/Icons/trees/stop.png"));
        item->setText(0,baseInfo.at(1));
        item->setText(1,QString::number(0)); //暂停
        item->setText(2,baseInfo.at(0));
        item->setText(3,baseInfo.at(1));
        item->setText(4,baseInfo.at(2));
        item->setText(5,baseInfo.at(3));
        item->setText(6,"0.0.0.0");
        item->setText(7,"0");
        addTopLevelItem(item);
        setCurrentItem(item);
        getDevice(item);
    }
}
//启动主项
void UserClientTreeWidget::startMainItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        item->setIcon(0,QIcon(":/tree/Icons/trees/start.png"));
        item->setText(1,QString::number(1)); //启动
        getDevice(item);
    }
}
//暂停主项
void UserClientTreeWidget::stopMainItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        item->setIcon(0,QIcon(":/tree/Icons/trees/stop.png"));
        item->setText(1,QString::number(0)); //暂停
        getDevice(item);
    }
}
//删除主项
void UserClientTreeWidget::deleteMainItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        takeTopLevelItem(indexOfTopLevelItem(item));
    }
}

//判断是否为子项
bool UserClientTreeWidget::isSubItem(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) == -1)  {
        return true;
    } else {
        return false;
    }
}
//添加子项
void UserClientTreeWidget::addSubItem(const QString &mn,const QString &objIP,int objPort)
{
    QList<QTreeWidgetItem*> list = findItems(mn,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        bool ok = true;
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==toAddress(objIP,objPort)) {
                ok = false; break;
            }
        }
        if(ok) {
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setIcon(0,QIcon(":/tree/Icons/trees/device.png"));
            item->setText(0,toAddress(objIP,objPort));
            item->setText(1,QString::number(0)); //断开
            item->setText(4,"0.0.0.0");
            item->setText(5,"0");
            item->setText(6,objIP);
            item->setText(7,QString::number(objPort));
            parent->addChild(item);
            setCurrentItem(item);
            getDevice(parent);
            getServer(item);
        }
    }
}
//设置一个子项为链接状态
void UserClientTreeWidget::connectSubItem(const QString &mn,const QString &objIP,int objPort,const QString &srcIP,int srcPort)
{
    QList<QTreeWidgetItem*> list = findItems(mn,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==toAddress(objIP,objPort)) {
                parent->child(i)->setIcon(0,QIcon(":/tree/Icons/trees/linker.png"));
                parent->child(i)->setText(1,QString::number(1)); //链接
                parent->child(i)->setText(4,srcIP);
                parent->child(i)->setText(5,QString::number(srcPort));
                break;
            }
        }
    }
}
//设置一个子项为断开状态
void UserClientTreeWidget::disconnectSubItem(const QString &mn,const QString &objIP,int objPort)
{
    QList<QTreeWidgetItem*> list = findItems(mn,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==toAddress(objIP,objPort)) {
                parent->child(i)->setIcon(0,QIcon(":/tree/Icons/trees/device.png"));
                parent->child(i)->setText(1,QString::number(0)); //断开
                parent->child(i)->setText(4,"0.0.0.0");
                parent->child(i)->setText(5,"0");
                break;
            }
        }
    }
}
//删除子项
void UserClientTreeWidget::deleteSubItem(QTreeWidgetItem *item)
{
    if(isSubItem(item)) {
        int index = item->parent()->indexOfChild(item);
        item->parent()->takeChild(index);
    }
}


//添加主项的所有子项
void UserClientTreeWidget::addMainAllSubItem(const QString &mn,const QList<QStringList> &serList)
{
    for(int i=0;i<serList.count();i++) {
        if(serList.at(i).count()>=3 && serList.at(i).first().toInt()==1) {
            addSubItem(mn,serList.at(i).at(1),serList.at(i).at(2).toInt());
        }
    }
}

//删除主项的所有子项
void UserClientTreeWidget::deleteMainAllSubItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        item->takeChildren();
    }
}

//选项单击处理
void UserClientTreeWidget::itemClickedHandle(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) == -1) {
        getDevice(item->parent());
        getServer(item);
        emit subItemClicked(DeviceState | ServerState);
    } else {
        getDevice(item);
        emit mainItemClicked(DeviceState);
    }
}
//选项双击处理
void UserClientTreeWidget::itemDoubleClickedHandle(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) == -1) {
        getDevice(item->parent());
        getServer(item);
        emit subItemDoubleClicked(DeviceState | ServerState);
    } else {
        getDevice(item);
        emit mainItemDoubleClicked(DeviceState);
    }
}
//选中右击处理
void UserClientTreeWidget::itemRightClickedHandle(const QPoint &pos)
{
    if(topLevelItemCount()>0) {
        QTreeWidgetItem *item = itemAt(pos);
        if(item==currentItem()) {
            if(indexOfTopLevelItem(item) == -1) {
                getDevice(item->parent());
                getServer(item);
                emit subItemRightClicked(DeviceState | ServerState);
            } else {
                getDevice(item);
                emit mainItemRightClicked(DeviceState);
            }
        }
    }
}

//初始化客户端列表
void UserClientTreeWidget::initialization()
{
    QList<QStringList> baseInfoList = UserClientListFile::clientList();
    for(int i=0;i<baseInfoList.count();i++) {
        QStringList baseInfo = baseInfoList.at(i);
        if(baseInfo.count()>=2) {
            addMainItem(baseInfo); //添加客户端
            QString mn = baseInfo.at(1);
            QList<QStringList> socketList = UserClientDatabaseFile::socketConfigList(mn);
            addMainAllSubItem(mn,socketList);
        }
    }
}

QString UserClientTreeWidget::toAddress(const QString &ipaddr,int port)
{
    return QString("%1:%2").arg(ipaddr).arg(port);
}

void UserClientTreeWidget::getDevice(QTreeWidgetItem *item)
{
    DeviceTitle = item->text(0);
    DeviceState = item->text(1).toInt();
    DeviceBaseInfo.clear();
    DeviceBaseInfo.append(item->text(2));
    DeviceBaseInfo.append(item->text(3));
    DeviceBaseInfo.append(item->text(4));
    DeviceBaseInfo.append(item->text(5));
    DeviceServerCount = item->childCount();
    DeviceServerList.clear();
    for(int i=0;i<item->childCount();i++) {
        QStringList server;
        server.append(QString::number(1));
        server.append(item->child(i)->text(6));
        server.append(item->child(i)->text(7));
        DeviceServerList.append(server);
    }
}

void UserClientTreeWidget::getServer(QTreeWidgetItem *item)
{
    ServerTitle = item->text(0);
    ServerState = item->text(1).toInt();
    LocalIPAddr = item->text(4);
    LocalPort = item->text(5).toInt();
    ServerIPAddr = item->text(6);
    ServerPort = item->text(7).toInt();
}



