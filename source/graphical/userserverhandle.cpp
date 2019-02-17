#include "userserverhandle.h"
#include "../source/files/userserverlistfile.h"
#include "../source/files/userserverdatabasefile.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QPalette>
//构造函数
UserServerHandle::UserServerHandle(QWidget *parent) : QWidget(parent)
{
    Protocol = new UserProtocol(UserContent::Upper);
    addressEdit = new UserAddressEdit(UserAddressEdit::SERVER);
    packetFieldEdit = new UserPacketFieldEdit(UserPacketFieldEdit::SERVER,Protocol->version());
    contentFieldEdit = new UserContentFieldEdit(Protocol->version());
    frameEdit = new UserFrameEdit();
    emptyServer = new UserRunningLog(UserRunningLog::EMPTY);
    stackWidget = new UserStackedWidget();
    stackWidget->addWidget(emptyServer);
    stackWidget->setCurrentIndex(0);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(addressEdit);
    mainLayout->addWidget(packetFieldEdit);
    mainLayout->addWidget(contentFieldEdit);
    mainLayout->addWidget(frameEdit);
    mainLayout->addWidget(stackWidget);
    mainLayout->setSpacing(12);
    mainLayout->setMargin(4);

    Protocol->setDeviceMN(packetFieldEdit->fieldMN());
    Protocol->setDevicePW(packetFieldEdit->fieldPW());
    Protocol->setDeviceST(packetFieldEdit->fieldST());
    Protocol->setPacketMN(packetFieldEdit->fieldMN());
    Protocol->setPacketPW(packetFieldEdit->fieldPW());
    Protocol->setPacketST(packetFieldEdit->fieldST());
    Protocol->setPacketCN(packetFieldEdit->fieldCN());
    Protocol->setPacketFlag(packetFieldEdit->fieldFlag());

    Protocol->setOverTime(contentFieldEdit->overTime());
    Protocol->setReCount(contentFieldEdit->reCount());
    Protocol->setRealCycle(contentFieldEdit->realCycle());
    Protocol->setMinuteCycle(contentFieldEdit->minuteCycle());
    Protocol->setPassword(contentFieldEdit->password());
    Protocol->setStartTime(contentFieldEdit->startTime());
    Protocol->setStopTime(contentFieldEdit->stopTime());
    Protocol->setAnalyzer(contentFieldEdit->analyzer());
    Protocol->setSamplingStart(contentFieldEdit->samplingStart());
    Protocol->setSamplingCycle(contentFieldEdit->samplingCycle());

    connect(packetFieldEdit,SIGNAL(filedChanged(int)),this,SLOT(packetFieldEditFieldChangedHandle(int)));
    connect(contentFieldEdit,SIGNAL(filedChanged(int)),this,SLOT(contentFieldEditFieldChangedHandle(int)));
    connect(frameEdit,SIGNAL(buttonClicked(int)),this,SLOT(frameEditButtonClickedHandle(int)));


}

UserServerHandle::~UserServerHandle()
{

}
//服务器初始化
void UserServerHandle::initialization()
{
    QList<QStringList> serverList = UserServerListFile::serverList();
    for(int i=0;i<serverList.count();i++) {
        QStringList server = serverList.at(i);
        if(server.count()>=2) {
            QString ipaddr = server.at(0);
            int port = server.at(1).toInt();
            createServer(ipaddr,port); //创建服务器
            QList<QStringList> baseInfoList  = UserServerDatabaseFile::deviceBaseInfoList(ipaddr,port);
            createServerAllDevice(ipaddr,port,baseInfoList); //创建服务器的所有监测点
        }
    }
}
//设置客户端地址
void UserServerHandle::setClientAddress(const QString &ipaddr,int port)
{
    addressEdit->setClientIPAddrAndPort(ipaddr,port);
}
//设置服务器地址
void UserServerHandle::setServerAddress(const QString &ipaddr,int port)
{
    addressEdit->setServerIPAddrAndPort(ipaddr,port);
}
//设置标准版本
void UserServerHandle::setVersion(int version)
{
    Protocol->setVersion(version);
    addressEdit->setVersion(version);
    packetFieldEdit->setVersion(version);
    contentFieldEdit->setVersion(version);
}
//设置设备编码
void UserServerHandle::setDeviceMN(const QString &mn)
{
    Protocol->setDeviceMN(mn);
    Protocol->setPacketMN(mn);
    packetFieldEdit->setFieldMN(mn);
}
//设置设备密码
void UserServerHandle::setDevicePW(const QString &pw)
{
    Protocol->setDevicePW(pw);
    Protocol->setPacketPW(pw);
    packetFieldEdit->setFieldPW(pw);
}
//设置系统类型
void UserServerHandle::setDeviceST(const QString &st)
{
    Protocol->setDeviceST(st);
    Protocol->setPacketST(st);
    packetFieldEdit->setFiledST(st);
}
//查找服务器
int UserServerHandle::findServer(const QString &ipaddr,int port)
{
    int index = -1;
    QString id = QString("%1:%2").arg(ipaddr).arg(port);
    for(int i=0;i<ServerList.count();i++) {
        if(ServerList.at(i)->identifier()==id) {
            index = i;
            break;
        }
    }
    return index;
}

//创建服务器
void UserServerHandle::createServer(const QString &ipaddr,int port)
{
    if(findServer(ipaddr,port)==-1) {
        UserRunningLog *server = new UserServerListen(ipaddr,port);
        connect(server,SIGNAL(connection(QString,UserTcpSocket*)), \
                    this,SLOT(listenConnectedHandle(QString,UserTcpSocket*)));
        ServerList.append(server);
        stackWidget->addWidget(server);
    }
}
//启用服务器
void UserServerHandle::startServer(const QString &ipaddr,int port,const QStringList &mnList)
{
    int index = findServer(ipaddr,port);
    if(index!=-1) {
        ServerList.at(index)->setChildIdentifirtList(mnList);
        ServerList.at(index)->start(); //启用服务器监听
        stackWidget->setCurrentWidget(ServerList.at(index));
    }
}
//停止服务器
void UserServerHandle::stopServer(const QString &ipaddr,int port)
{
    int index = findServer(ipaddr,port);
    if(index!=-1) {
        ServerList.at(index)->stop(); //关闭服务器监测
    }
}
//删除服务器
void UserServerHandle::deleteServer(const QString &ipaddr,int port)
{
    int index = findServer(ipaddr,port);
    if(index!=-1) {
        stackWidget->removeWidget(ServerList.at(index));
        delete ServerList.at(index);
        ServerList.removeAt(index);
    }
}
//设置当前需要显示的服务器
void UserServerHandle::setCurrentServer(const QString &ipaddr,int port)
{
    stackWidget->setCurrentIndex(0);
    QString id = QString("%1:%2").arg(ipaddr).arg(port);
    for(int i=1;i<stackWidget->count();i++) {
        UserRunningLog *server = (UserRunningLog*)stackWidget->widget(i);
        if(server->identifier()==id) {
            stackWidget->setCurrentIndex(i);
            Protocol->setDevice(server->device());
            break;
        }
    }
}
//查找服务器监测点
int UserServerHandle::findDevice(const QString &ipaddr,int port,const QString &mn)
{
    int index = -1;
    QString id = QString("%1:%2<%3>").arg(ipaddr).arg(port).arg(mn);
    for(int i=1;i<ServerList.count();i++) {
        if(ServerList.at(i)->identifier()==id) {
            index = i;
            break;
        }
    }
    return index;
}
//创建服务器监测点
void UserServerHandle::createDevice(const QString &ipaddr,int port,const QStringList &baseInfo)
{
    if(baseInfo.count()>=4) {
        int index = findServer(ipaddr,port);
        if(index!=-1 && findDevice(ipaddr,port,baseInfo.at(1))==-1) {
            UserServerDeviceLink *device = new UserServerDeviceLink(ipaddr,port,baseInfo);
            connect(device,SIGNAL(linkerBuild(QString,QString,int)), \
                    this,SLOT(socketLinkerBuildHandle(QString,QString,int)));
            connect(device,SIGNAL(linkerClose(QString)), \
                    this,SLOT(socketLinkerCloseHandle(QString)));
            stackWidget->addWidget(device);
            ServerList.append(device);
        }
    }
}
//启动服务器监测点
void UserServerHandle::connectDevice(const QString &ipaddr,int port,const QString &mn,UserTcpSocket *socket)
{
    int serverIndex = findServer(ipaddr,port);
    int deviceIndex = findDevice(ipaddr,port,mn);
    if(serverIndex!=-1 && deviceIndex!=-1) {
        ServerList.at(deviceIndex)->initialization();
        ServerList.at(deviceIndex)->start(socket);
    }
}
//停止服务器监测点
void UserServerHandle::disconnectDevice(const QString &ipaddr,int port,const QString &mn)
{
    int index = findDevice(ipaddr,port,mn);
    if(index!=-1) {
        ServerList.at(index)->stop();
    }
}
//删除服务器监测点
void UserServerHandle::deleteDevice(const QString &ipaddr,int port,const QString &mn)
{
    int index = findDevice(ipaddr,port,mn);
    if(index!=-1) {
        stackWidget->removeWidget(ServerList.at(index));
        delete ServerList.at(index);
        ServerList.removeAt(index);
    }
}
//设置担心需要显示的服务器监测点
void UserServerHandle::setCurrentDevice(const QString &ipaddr,int port,const QString &mn)
{
    stackWidget->setCurrentIndex(0);
    QString id = QString("%1:%2<%3>").arg(ipaddr).arg(port).arg(mn);
    for(int i=1;i<stackWidget->count();i++) {
        UserRunningLog *device = (UserRunningLog*)stackWidget->widget(i);
        if(device->identifier()==id) {
            stackWidget->setCurrentIndex(i);
            Protocol->setDevice(device->device());
            break;
        }
    }
}

//创建服务器所有监测点
void UserServerHandle::createServerAllDevice(const QString &ipaddr,int port,const QList<QStringList> &baseInfoList)
{
    for(int i=0;i<baseInfoList.count();i++) {
        createDevice(ipaddr,port,baseInfoList.at(i));
    }
}
//删除服务器所有监测点
void UserServerHandle::deleteServerAllDevice(const QString &ipaddr,int port)
{
    QString id = QString("%1:%2<").arg(ipaddr).arg(port);
    for(int i=0;i<ServerList.count();i++) {
        if(ServerList.at(i)->identifier().indexOf(id,0)!=-1) {
            stackWidget->removeWidget(ServerList.at(i));
            delete ServerList.at(i);
            ServerList.removeAt(i);
        }
    }
}

//
void UserServerHandle::packetFieldEditFieldChangedHandle(int num)
{
    if(num==0) {
        Protocol->setDeviceMN(packetFieldEdit->fieldMN());
        Protocol->setPacketMN(packetFieldEdit->fieldMN());
        qDebug() << packetFieldEdit->fieldMN();
    } else if(num==1) {
        Protocol->setDevicePW(packetFieldEdit->fieldPW());
        Protocol->setPacketPW(packetFieldEdit->fieldPW());
        qDebug() << packetFieldEdit->fieldPW();
    } else if(num==2) {
        contentFieldEdit->setDeviceST(packetFieldEdit->fieldST());
        Protocol->setDeviceST(packetFieldEdit->fieldST());
        Protocol->setPacketST(packetFieldEdit->fieldST());
        qDebug() << packetFieldEdit->fieldST();
    } else if(num==3) {
        contentFieldEdit->setEnabled(packetFieldEdit->fieldCN());
        Protocol->setPacketCN(packetFieldEdit->fieldCN());
        qDebug() << packetFieldEdit->fieldCN();
    } else if(num==4) {
        Protocol->setPacketFlag(packetFieldEdit->fieldFlag());
        qDebug() << packetFieldEdit->fieldFlag();
    }
}
//服务器报文及内容字段取值改变槽函数
void UserServerHandle::contentFieldEditFieldChangedHandle(int num)
{
    if(num==0) {
        Protocol->setOverTime(contentFieldEdit->overTime());
    } else if(num==1) {
        Protocol->setReCount(contentFieldEdit->reCount());
    } else if(num==2) {
        Protocol->setRealCycle(contentFieldEdit->realCycle());
    } else if(num==3) {
        Protocol->setMinuteCycle(contentFieldEdit->minuteCycle());
    } else if(num==4) {
        Protocol->setPassword(contentFieldEdit->password());
    } else if(num==5) {
        Protocol->setSystemTime(contentFieldEdit->systemTime());
    } else if(num==6) {
        Protocol->setStartTime(contentFieldEdit->startTime());
    } else if(num==7) {
        Protocol->setStopTime(contentFieldEdit->stopTime());
    } else if(num==8) {
        Protocol->setAnalyzer(contentFieldEdit->analyzer());
    } else if(num==9) {
        Protocol->setSamplingStart(contentFieldEdit->samplingStart());
    } else if(num==10) {
        Protocol->setSamplingCycle(contentFieldEdit->samplingCycle());
    } else if(num==11) {

    }
}
//服务器帧组包或发送槽函数
void UserServerHandle::frameEditButtonClickedHandle(int num)
{
    if(num==0) { //帧组包
        Protocol->setPacketQN();
        frameEdit->setFrame(Protocol->protocolPack(Protocol->packetCN()));
    } else if(num==1) { //帧发送
        UserRunningLog *currentDevice = (UserRunningLog*)stackWidget->currentWidget();
        QString id = QString("%1<%2>").arg(addressEdit->serverAddress()).arg(Protocol->deviceMN());
        if(currentDevice!=0 && currentDevice->identifier()==id) {
            if(currentDevice->state()) {
                currentDevice->sendMessage(frameEdit->frame());
            } else {
                QMessageBox::information(this,tr("提示"),tr("监测点(%1)未连接!").arg(Protocol->deviceMN()));
            }
        } else {
            QMessageBox::information(this,tr("提示"),tr("请选择一个监测点进行帧发送!"));
        }
    }
}
//识别到一个服务器监测设备链接建立槽函数
void UserServerHandle::listenConnectedHandle(const QString &id,UserTcpSocket *socket)
{
    int ps = id.indexOf(':',0);
    int pd = id.indexOf('<',0);
    int pe = id.indexOf('>',0);
    if(ps!=-1 && pd!=-1 && pe !=-1) {
        QString ipaddr = id.left(ps);
        int port = id.mid(ps+1,pd-ps-1).toInt();
        QString mn = id.mid(pd+1,pe-pd-1);
        connectDevice(ipaddr,port,mn,socket);
    }
}
//监测设备建立链接槽函数
void UserServerHandle::socketLinkerBuildHandle(const QString &id,const QString &ipaddr,int port)
{
    emit linkerBuild(id,ipaddr,port);
}
//监测设备断开链接槽函数
void UserServerHandle::socketLinkerCloseHandle(const QString &id)
{
    emit linkerClose(id);
}




