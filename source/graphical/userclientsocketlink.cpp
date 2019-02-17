#include "userclientsocketlink.h"
#include "../source/files/userclientdatabasefile.h"
#include "../source/files/userclientlogfile.h"
#include <QDebug>

UserClientSocketLink::UserClientSocketLink(const QString &mn,const QString &ipaddr,int port,QWidget *parent)
    : UserRunningLog(UserRunningLog::CLIENT_LINKER,parent)
{
    setTitle(ipaddr,port);
    ServerIPAddr = ipaddr;
    ServerPort = port;
    DeviceCode = mn;
    Device = NULL;
    tcpClient = new UserTcpClient(ipaddr,port);

    connect(tcpClient,SIGNAL(runningLog(QString)),this,SLOT(tcpClientRunningLogHandle(QString)));
    connect(tcpClient,SIGNAL(linkerBuild(QString,int)),this,SLOT(tcpClientLinkerBuildHandle(QString,int)));
    connect(tcpClient,SIGNAL(linkerClose()),this,SLOT(tcpClientLinkerCloseHandle()));
    connect(tcpClient,SIGNAL(receiveMsg(QString)),this,SLOT(tcpClientReceiveMsgHandle(QString)));
}

UserClientSocketLink::~UserClientSocketLink()
{
    stop();
}
//获取客户端链接槽标识符
QString UserClientSocketLink::identifier()
{
    return QString("%1<%2:%3>").arg(DeviceCode).arg(ServerIPAddr).arg(ServerPort);
}
//
UserDevice* UserClientSocketLink::device()
{
    return Device;
}
//启用客户端链接槽
void UserClientSocketLink::start()
{
    tcpClient->startSocket();
}
//关闭客户端链接槽
void UserClientSocketLink::stop()
{
    tcpClient->stopSocket();
}
//获取客户端槽状态
bool UserClientSocketLink::state()
{
    return tcpClient->stateSocket();
}
//发送消息
void UserClientSocketLink::sendMessage(const QString &msg)
{
    if(tcpClient->stateSocket()) {
        QString log = QString("Send(%1:%2):%3").arg(ServerIPAddr).arg(ServerPort).arg(msg);
        UserClientLogFile::writeLog(DeviceCode,ServerIPAddr,ServerPort,log);
        appendSendMsg(toAddress(),msg);
        tcpClient->sendMsg(msg);
        emit sendMsg(identifier(),msg);
    }
}
//发送消息槽函数
void UserClientSocketLink::sendMsgHandle(const QString &id,const QString &msg)
{
    if(id==identifier() && tcpClient->stateSocket()) {
        QString log = QString("Send(%1:%2):%3").arg(ServerIPAddr).arg(ServerPort).arg(msg);
        UserClientLogFile::writeLog(DeviceCode,ServerIPAddr,ServerPort,log);
        appendSendMsg(toAddress(),msg);
        tcpClient->sendMsg(msg);
    }
}
//运行日志槽函数
void UserClientSocketLink::tcpClientRunningLogHandle(const QString &log)
{
    UserClientLogFile::writeLog(DeviceCode,ServerIPAddr,ServerPort,log);
    appendRunningLog(log);
    emit runningLog(identifier(),log);
}
//链接成功槽函数
void UserClientSocketLink::tcpClientLinkerBuildHandle(const QString &ipaddr,int port)
{
    emit linkerBuild(identifier(),ipaddr,port);
}
//断开链接槽函数
void UserClientSocketLink::tcpClientLinkerCloseHandle()
{
    emit linkerClose(identifier());
}

//接收消息槽函数
void UserClientSocketLink::tcpClientReceiveMsgHandle(const QString &msg)
{
    QString log = QString("Receive<%1:%2>:%3").arg(ServerIPAddr).arg(ServerPort).arg(msg);
    UserClientLogFile::writeLog(DeviceCode,ServerIPAddr,ServerPort,log);
    appendReceiveMsg(toAddress(),msg);
    emit receiveMsg(identifier(),msg);
}

QString UserClientSocketLink::toAddress()
{
    return  QString("%1:%2").arg(ServerIPAddr).arg(ServerPort);
}


