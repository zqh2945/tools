#include "usertcpclient.h"
#include <QHostAddress>
#include <QDebug>

UserTcpClient::UserTcpClient(const QString &ipaddr,int port,QObject *parent) : QTcpSocket(parent)
{
    ServerIPAddr = ipaddr;
    ServerPort = port;
    ClientIPAddr = localAddress().toString();
    ClientPort = localPort();
    TimerID = -1;

    setPeerAddress(QHostAddress(ServerIPAddr));
    setPeerPort(ServerPort);
    connect(this,SIGNAL(connected()),this,SLOT(connectedHandle()));
    connect(this,SIGNAL(disconnected()),this,SLOT(disconnectedHandle()));
    connect(this,SIGNAL(readyRead()),this,SLOT(receiveMessageHandle()));
}

UserTcpClient::~UserTcpClient()
{
    stopSocket();
}
//启动槽
void UserTcpClient::startSocket()
{
    if(state()==QAbstractSocket::UnconnectedState) {
        connectToHost(ServerIPAddr,ServerPort);
    }
    //启动槽链接控制定时器
    TimerID = startTimer(10000,Qt::PreciseTimer);
}
//关闭槽
void UserTcpClient::stopSocket()
{
    if(TimerID!=-1) {
        //关闭槽链接控制定时器
        killTimer(TimerID);
        TimerID = -1;
    }
    if(state()==QAbstractSocket::ConnectedState) {
        disconnectFromHost();
    }
}
//获取槽连接状态
bool UserTcpClient::stateSocket()
{
    if(state()==QAbstractSocket::ConnectedState) {
        return true;
    } else {
        return false;
    }

}
//定时器事件
void UserTcpClient::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==TimerID && state()==QAbstractSocket::UnconnectedState) {
        connectToHost(ServerIPAddr,ServerPort);
    }
}
//发送消息
void UserTcpClient::sendMsg(const QString &msg)
{
    write(msg.toLatin1(),msg.length());
    waitForBytesWritten();
}
//链接建立槽函数
void UserTcpClient::connectedHandle()
{
    if(state()==QAbstractSocket::ConnectedState) {
        ClientIPAddr = localAddress().toString();
        ClientPort = localPort();
        QString log = QString("客户端(%1)与服务器(%2)建立链接...").arg(toClientAddress()).arg(toServerAddress());
        emit linkerBuild(ClientIPAddr,ClientPort);
        emit runningLog(log);
    }
}
//链接断开槽函数
void UserTcpClient::disconnectedHandle()
{
    if(state()==QAbstractSocket::UnconnectedState) {
        QString log = QString("客户端(%1)与服务器(%2)断开链接...").arg(toClientAddress()).arg(toServerAddress());
        emit linkerClose();
        emit runningLog(log);
        if(TimerID!=-1) {
            connectToHost(ServerIPAddr,ServerPort);
        }
    }
}
//接收消息槽函数
void UserTcpClient::receiveMessageHandle()
{
    while(bytesAvailable()>0) {
        QString msg = readLine().data();
        if(!msg.isEmpty()) {
            emit receiveMsg(msg);
        }
    }
}
//本地地址
QString UserTcpClient::toClientAddress()
{
    return QString("%1:%2").arg(ClientIPAddr).arg(ClientPort);
}
//目标地址
QString UserTcpClient::toServerAddress()
{
    return  QString("%1:%2").arg(ServerIPAddr).arg(ServerPort);
}



