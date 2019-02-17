#include "userserverdevicelink.h"
#include "../source/files/userserverdatabasefile.h"
#include <QHostAddress>
#include <QDebug>

UserServerDeviceLink::UserServerDeviceLink(const QString &ipaddr,int port,const QStringList &baseInfo,QWidget *parent)
    : UserRunningLog (UserRunningLog::SERVER_DEVICE,parent)
{

    ServerIPAddr = ipaddr;
    ServerPort = port;
    tcpSocket = NULL;
    if(baseInfo.count()>=4) {
        QString mn = baseInfo.at(1);
        QString pw = baseInfo.at(2);
        QString st = baseInfo.at(3);
        int version = baseInfo.at(0).toInt();
        DeviceCode = mn;
        setTitle(DeviceCode);
        Device = new UserDevice(UserDevice::Upper,mn,pw,st,version);
        Device->initialization(ipaddr,port,mn);
        Protocol = new UserProtocol(UserProtocol::Upper,mn,pw,st,version);
        Protocol->setDevice(Device);

        connect(Device,SIGNAL(protocolUpdateQN()),Protocol,SLOT(protocolUpdateQNHandle()));
        connect(Device,SIGNAL(protocolUnpack(QString)),Protocol,SLOT(protocolUnpackHandle(QString)));
        connect(Device,SIGNAL(protocolPack(QString*,int,bool,bool)),Protocol,SLOT(protocolPackHandle(QString*,int,bool,bool)));
        connect(Device,SIGNAL(runningLog(QString)),this,SLOT(deviceRunningLogHandle(QString)));
        connect(Device,SIGNAL(sendMsg(QString)),this,SLOT(deviceSendMsgHandle(QString)));
    }
}

UserServerDeviceLink::~UserServerDeviceLink()
{
    stop();
}
//获取服务器监测点标识符
QString UserServerDeviceLink::identifier()
{
	return QString("%1:%2<%3>").arg(ServerIPAddr).arg(ServerPort).arg(DeviceCode);
}
//获取服务器监测点数采仪
UserDevice* UserServerDeviceLink::device()
{
    return Device;
}
//监测点数采仪初始化
void UserServerDeviceLink::initialization()
{
    Device->initialization(ServerIPAddr,ServerPort,DeviceCode);
}
//服务器监测点链接
void UserServerDeviceLink::start(UserTcpSocket *socket)
{
    tcpSocket = socket;
    SocketIPAddr = tcpSocket->peerAddress().toString();
    SocketPort = tcpSocket->peerPort();

    appendRunningLog(QString("监测点(%1<%2>)与服务器(%3)链接建立...").arg(DeviceCode) \
                     .arg(toSocketAddress()).arg(toServerAddress()));
    connect(tcpSocket,SIGNAL(linkerClose(UserTcpSocket*)),this,SLOT(tcpSocketLinkerCloseHandle()));
    connect(tcpSocket,SIGNAL(receiveMsg(QString)),this,SLOT(tcpSocketReceiveMsgHandle(QString)));
    emit linkerBuild(identifier(),SocketIPAddr,SocketPort);
    Device->start(); //
}
//服务器监测点断开
void UserServerDeviceLink::stop()
{
    if(tcpSocket!=NULL) {
        tcpSocket->disconnectedSocket();
        Device->stop(); //
    }
}
//获取服务器监测点状态
bool UserServerDeviceLink::state()
{
    if(tcpSocket!=NULL) {
        if(tcpSocket->state()==QTcpSocket::ConnectedState) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
//服务器监测点发送消息
void UserServerDeviceLink::sendMessage(const QString &msg)
{
    if(tcpSocket!=NULL && state()) {
        tcpSocket->sendMessage(msg);
        appendSendMsg(toSocketAddress(),msg);
    }
}
//断开链接槽函数
void UserServerDeviceLink::tcpSocketLinkerCloseHandle()
{
    if(tcpSocket!=NULL) {
        appendRunningLog(QString("监测点(%1<%2>)与服务器(%3)链接断开...").arg(DeviceCode) \
                         .arg(toSocketAddress()).arg(toServerAddress()));
        emit linkerClose(identifier());
    }
}

//接收消息槽函数
void UserServerDeviceLink::tcpSocketReceiveMsgHandle(const QString &msg)
{
    if(tcpSocket!=NULL) {
        appendReceiveMsg(toSocketAddress(),msg);
        Device->receiveMessage(msg);
    }
}
//监测点运行日志槽函数
void UserServerDeviceLink::deviceRunningLogHandle(const QString &log)
{
    appendRunningLog(log);
}
//监测点发送消息槽函数
void UserServerDeviceLink::deviceSendMsgHandle(const QString &msg)
{
    sendMessage(msg);
}
//
QString UserServerDeviceLink::toServerAddress()
{
    return QString("%1:%2").arg(ServerIPAddr).arg(ServerPort);
}
//
QString UserServerDeviceLink::toSocketAddress()
{
    return QString("%1:%2").arg(SocketIPAddr).arg(SocketPort);
}

