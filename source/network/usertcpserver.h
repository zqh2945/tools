#ifndef USERTCPSERVER_H
#define USERTCPSERVER_H

#include <QHostAddress>
#include <QTcpServer>
#include "usertcpsocket.h"

class UserTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    UserTcpServer(const QString &ipaddr,int port,QObject *parent=0);
    ~UserTcpServer();
	void startServer();
    void stopServer();
signals:
    void runningLog(const QString &msg);
    void connection(UserTcpSocket *socket);
protected:
    virtual void incomingConnection(qintptr socketDescriptor);
private:
    QString ServerIPAddr;
    int ServerPort;
    QString toServerAddress();
};

#endif // USERTCPSERVER_H
