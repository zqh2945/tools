#include "usertcpsocket.h"
#include <QHostAddress>
#include <QDebug>

UserTcpSocket::UserTcpSocket(QObject *parent) : QTcpSocket(parent)
{
    Identification = false;
    TimerWait = startTimer(600000); //等待10分钟
    connect(this,SIGNAL(disconnected()),this,SLOT(disconnectedHandle()));
    connect(this,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}

UserTcpSocket::~UserTcpSocket()
{
    disconnectedSocket();
}
//设置链接槽识别标志
void UserTcpSocket::setIdentification(bool flag)
{
    Identification = flag;
}
//定时器触发事件
void UserTcpSocket::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==TimerWait) {
        emit runningLog(QString("服务器(%1)与客户端(%2)链接超时...").arg(toServerAddress()).arg(toSocketAddress()));
        disconnectedSocket();
    }
}
//链接槽断开
void UserTcpSocket::disconnectedSocket()
{
    killTimer(TimerWait);
    disconnectFromHost();
}
//发送消息
void UserTcpSocket::sendMessage(const QString &msg)
{
    if(state()==QAbstractSocket::ConnectedState) {
        write(msg.toLatin1(),msg.length());
        waitForBytesWritten();
    }
}
//链接断开槽函数
void UserTcpSocket::disconnectedHandle()
{
    if(state()==QAbstractSocket::UnconnectedState) {
        emit runningLog(QString("服务器(%1)与客户端(%2)断开链接...").arg(toServerAddress()).arg(toSocketAddress()));
        emit linkerClose(this);
    }
}
//接收消息槽函数
void UserTcpSocket::receiveMessage()
{
    while(bytesAvailable()>0) {
        QString msg = readLine().data();
        if(!msg.isEmpty()) {
            if(!Identification) {
                emit identification(this,msg);
                emit receiveMsg(msg);
            } else {
                TimerWait = startTimer(180*1000); //等待30分钟
                emit receiveMsg(msg);
            }
        }
    }
}
//
QString UserTcpSocket::toServerAddress()
{
    QString ipaddr = localAddress().toString();
    int port = localPort();
    return QString("%1:%2").arg(ipaddr).arg(port);
}
//
QString UserTcpSocket::toSocketAddress()
{
    QString ipaddr = peerAddress().toString();
    int port = peerPort();
    return QString("%1:%2").arg(ipaddr).arg(port);
}

