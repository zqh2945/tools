#ifndef USERSERVERLISTEN_H
#define USERSERVERLISTEN_H

#include <QWidget>
#include "userrunninglog.h"
#include "../source/network/usertcpserver.h"
#include "../source/network/usertcpsocket.h"
#include "../source/device/userdevice.h"

class UserServerListen : public UserRunningLog
{
    Q_OBJECT
public:
    UserServerListen(const QString &ipaddr,int port,QWidget *parent=0);
    virtual ~UserServerListen();
    virtual QString identifier();
    virtual UserDevice* device();
    virtual void start();
    virtual void stop();
    virtual bool state();
    virtual void setChildIdentifirtList(const QStringList &list);
    virtual void sendMessage(const QString &msg);
signals:
    void connection(const QString &id,UserTcpSocket *socket);
public slots:

private:
    QString ServerIPAddr;
    int ServerPort;
    QStringList DeviceCodeList;

    UserTcpServer *tcpServer;
    QList<UserTcpSocket*> tcpSocketList;
    bool deviceCodeCheck(const QString &msg,const QString &mn);
private slots:
    void tcpServerRunningLogHandle(const QString &log);
    void tcpServerConnectionHandle(UserTcpSocket *socket);
    void tcpSocketRunningLogHandle(const QString &log);
    void tcpSocketIdentificationHandle(UserTcpSocket *socket,const QString &msg);
    void tcpSocketLinkerCloseHandle(UserTcpSocket *socket);
};

#endif // USERSERVERLISTEN_H
