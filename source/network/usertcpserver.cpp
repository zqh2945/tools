#include "usertcpserver.h"
#include <QHostAddress>
#include <QDebug>

UserTcpServer::UserTcpServer(const QString &ipaddr,int port,QObject *parent) : QTcpServer (parent)
{
    ServerIPAddr = ipaddr;
    ServerPort = port;
}

UserTcpServer::~UserTcpServer()
{
    stopServer();
}
//启用服务器监听
void UserTcpServer::startServer()
{
    listen(QHostAddress(ServerIPAddr),ServerPort);
    emit runningLog(QString("服务器(%1)启动...").arg(toServerAddress()));
}
//关闭服务器监听
void UserTcpServer::stopServer()
{
    emit runningLog(QString("服务器(%1)关闭...").arg(toServerAddress()));
    close();
}
//出现一个链接时，QTcpServer调用该函数
void UserTcpServer::incomingConnection(qintptr socketDescriptor)
{
    UserTcpSocket *tcpSocket = new UserTcpSocket();
    tcpSocket->setSocketDescriptor(socketDescriptor);
    emit connection(tcpSocket);
    QString socketAddress = QString("%1:%2").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());
    emit runningLog(QString("服务器(%1)与客户端(%2)建立链接...").arg(toServerAddress()).arg(socketAddress));
}
//
QString UserTcpServer::toServerAddress()
{
    return QString("%1:%2").arg(ServerIPAddr).arg(ServerPort);
}



