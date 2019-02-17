#include "userservertreewidget.h"
#include "../source/files/userserverlistfile.h"
#include "../source/files/userserverdatabasefile.h"
#include <QIcon>
#include <QDebug>

UserServerTreeWidget::UserServerTreeWidget() : QTreeWidget ()
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

UserServerTreeWidget::~UserServerTreeWidget()
{
}
//判断是否是主项
bool UserServerTreeWidget::isMainItem(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) != -1) {
        return true;
    } else {
        return false;
    }
}
//查找主项
bool UserServerTreeWidget::findMainItem(const QString &ipaddr,int port)
{
    QList<QTreeWidgetItem*> list = findItems(toAddress(ipaddr,port),Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        return true;
    } else {
        return false;
    }
}
//添加主项
void UserServerTreeWidget::addMainItem(const QString &ipaddr,int port)
{
    QList<QTreeWidgetItem*> list = findItems(toAddress(ipaddr,port),Qt::MatchCaseSensitive,0);
    if(list.count()==0) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setIcon(0,QIcon(":/tree/Icons/trees/stop.png"));
        item->setText(0,toAddress(ipaddr,port));
        item->setText(1,QString::number(0)); //暂停
        item->setText(6,ipaddr);
        item->setText(7,QString::number(port));
        addTopLevelItem(item);
        setCurrentItem(item);
        getServer(item);
    }
}
//启动主项
void UserServerTreeWidget::startMainItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        item->setIcon(0,QIcon(":/tree/Icons/trees/start.png"));
        item->setText(1,QString::number(1)); //启用
        getServer(item);
    }
}
//暂停主项
void UserServerTreeWidget::stopMainItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        item->setIcon(0,QIcon(":/tree/Icons/trees/stop.png"));
        item->setText(1,QString::number(0)); //暂停
        getServer(item);
    }
}
//删除主项
void UserServerTreeWidget::deleteMainItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        takeTopLevelItem(indexOfTopLevelItem(item));
    }
}

//判断是否为子项
bool UserServerTreeWidget::isSubItem(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) == -1)  {
        return true;
    } else {
        return false;
    }
}
//查找子项
bool UserServerTreeWidget::findSubItem(const QString &ipaddr,int port,const QString &mn)
{
    bool ok = false;
    QString address = QString("%1:%2").arg(ipaddr).arg(port);
    QList<QTreeWidgetItem*> list = findItems(address,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==mn) {
                ok = true;
                break;
            }
        }
    }
    return ok;
}
//添加子项
void UserServerTreeWidget::addSubItem(const QString &ipaddr,int port,const QStringList &baseInfo)
{
    QString address = QString("%1:%2").arg(ipaddr).arg(port);
    QList<QTreeWidgetItem*> list = findItems(address,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        bool ok = true;
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==baseInfo.first()) {
                ok = false; break;
            }
        }
        if(ok && baseInfo.count()>=4) {
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setIcon(0,QIcon(":/tree/Icons/trees/device.png"));
            item->setText(0,baseInfo.at(1));
            item->setText(1,QString::number(0)); //断开
            item->setText(2,baseInfo.at(0));
            item->setText(3,baseInfo.at(1));
            item->setText(4,baseInfo.at(2));
            item->setText(5,baseInfo.at(3));
            item->setText(6,"0.0.0.0");
            item->setText(7,QString::number(0));
            parent->addChild(item);
            setCurrentItem(item);
            getServer(parent);
            getDevice(item);
        }
    }
}
//更新子项
void UserServerTreeWidget::editSubItem(const QString &ipaddr,int port,const QStringList &baseInfo)
{
    QString address = QString("%1:%2").arg(ipaddr).arg(port);
    QList<QTreeWidgetItem*> list = findItems(address,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==baseInfo.at(1)) {
                QTreeWidgetItem *item = parent->child(i);
                if(baseInfo.count()>=4) {
                    item->setText(2,baseInfo.at(0));
                    item->setText(3,baseInfo.at(1));
                    item->setText(4,baseInfo.at(2));
                    item->setText(5,baseInfo.at(3));
                    parent->addChild(item);
                    setCurrentItem(item);
                    getServer(parent);
                    getDevice(item);
                }
            }
        }
    }
}

//设置一个子项为链接状态
void UserServerTreeWidget::connectSubItem(const QString &srcIP,int srcPort,const QString &mn,const QString &objIP,int objPort)
{
    QString address = QString("%1:%2").arg(srcIP).arg(srcPort);
    QList<QTreeWidgetItem*> list = findItems(address,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==mn) {
                parent->child(i)->setIcon(0,QIcon(":/tree/Icons/trees/linker.png"));
                parent->child(i)->setText(1,QString::number(1)); //链接
                parent->child(i)->setText(6,objIP);
                parent->child(i)->setText(7,QString::number(objPort));
                break;
            }
        }
    }
}
//设置一个子项为断开状态
void UserServerTreeWidget::disconnectSubItem(const QString &ipaddr,int port,const QString &mn)
{
    QString address = QString("%1:%2").arg(ipaddr).arg(port);
    QList<QTreeWidgetItem*> list = findItems(address,Qt::MatchCaseSensitive,0);
    if(list.count()>0) {
        QTreeWidgetItem *parent = list.first();
        for(int i=0;i<parent->childCount();i++) {
            if(parent->child(i)->text(0)==mn) {
                parent->child(i)->setIcon(0,QIcon(":/tree/Icons/trees/device.png"));
                parent->child(i)->setText(1,QString::number(0)); //断开
                parent->child(i)->setText(6,"0");
                parent->child(i)->setText(7,"0.0.0.0");
                break;
            }
        }
    }
}

//删除子项
void UserServerTreeWidget::deleteSubItem(QTreeWidgetItem *item)
{
    if(isSubItem(item)) {
        int index = item->parent()->indexOfChild(item);
        item->parent()->takeChild(index);
    }
}

//添加主项的所有子项
void UserServerTreeWidget::addMainAllSubItem(const QString &ipaddr,int port,const QList<QStringList> &baseInfoList)
{
    for(int i=0;i<baseInfoList.count();i++) {
        if(baseInfoList.at(i).count()>=4) {
            addSubItem(ipaddr,port,baseInfoList.at(i));
        }
    }
}
//删除主项的所有子项
void UserServerTreeWidget::deleteMainAllSubItem(QTreeWidgetItem *item)
{
    if(isMainItem(item)) {
        item->takeChildren();
    }
}

//选项单击处理
void UserServerTreeWidget::itemClickedHandle(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) == -1) {
        getServer(item->parent());
        getDevice(item);
        emit subItemClicked(ServerState | DeviceState);
    } else {
        getServer(item);
        emit mainItemClicked(ServerState);
    }
}
//选项双击处理
void UserServerTreeWidget::itemDoubleClickedHandle(QTreeWidgetItem *item)
{
    if(indexOfTopLevelItem(item) == -1) {
        getServer(item->parent());
        getDevice(item);
        emit subItemDoubleClicked(ServerState | DeviceState);
    } else {
        getServer(item);
        emit mainItemDoubleClicked(ServerState);
    }
}
//选中右击处理
void UserServerTreeWidget::itemRightClickedHandle(const QPoint &pos)
{
    if(topLevelItemCount()>0) {
        QTreeWidgetItem *item = itemAt(pos);
        if(item==currentItem()) {
            if(indexOfTopLevelItem(item) == -1) {
                getServer(item->parent());
                getDevice(item);
                emit subItemRightClicked(ServerState | DeviceState);
            } else {
                getServer(item);
                emit mainItemRightClicked(ServerState);
            }
        }
    }
}

//初始化服务器列表
void UserServerTreeWidget::initialization()
{
    //获取服务器列表
    QList<QStringList> serverList = UserServerListFile::serverList();
    for(int i=0;i<serverList.count();i++) {
        QStringList server = serverList.at(i);
        if(server.count()>=2) {
            QString ipaddr = server.at(0); //服务器IP地址
            int port = server.at(1).toInt(); //服务器端口
            addMainItem(ipaddr,port); //添加服务器
            //获取服务器关联监测点列表
            QList<QStringList> baseInfoList = UserServerDatabaseFile::deviceBaseInfoList(ipaddr,port);
            addMainAllSubItem(ipaddr,port,baseInfoList);
        }
    }
}

QString UserServerTreeWidget::toAddress(const QString &ipaddr,int port)
{
    return QString("%1:%2").arg(ipaddr).arg(port);
}

void UserServerTreeWidget::getServer(QTreeWidgetItem *item)
{
    ServerTitle = item->text(0);
    ServerState = item->text(1).toInt();
    ServerIPAddr = item->text(6);
    ServerPort = item->text(7).toInt();
    ServerDeviceCount = item->childCount();
    ServerDeviceList.clear();
    for(int i=0;i<item->childCount();i++) {
        ServerDeviceList.append(item->child(i)->text(0));
    }
}

void UserServerTreeWidget::getDevice(QTreeWidgetItem *item)
{
    DeviceTitle = item->text(0);
    DeviceState = item->text(1).toInt();
    DeviceBaseInfo.clear();
    DeviceBaseInfo.append(item->text(2));
    DeviceBaseInfo.append(item->text(3));
    DeviceBaseInfo.append(item->text(4));
    DeviceBaseInfo.append(item->text(5));
    DeviceIPAddr = item->text(6);
    DevicePort = item->text(7).toInt();
}





