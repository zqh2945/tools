#ifndef USERCLIENTSOCKETLINK_H
#define USERCLIENTSOCKETLINK_H

#include <QWidget>
#include "userrunninglog.h"
#include "../source/network/usertcpclient.h"
#include "../source/device/userdevice.h"

class UserClientSocketLink : public UserRunningLog
{
    Q_OBJECT
public:
    UserClientSocketLink(const QString &mn,const QString &ipaddr,int port,QWidget *parent=0);
    virtual ~UserClientSocketLink();
    virtual QString identifier();
    virtual UserDevice* device();
    virtual void start();
    virtual void stop();
    virtual bool state();
    virtual void sendMessage(const QString &msg);
    void setDevice(UserDevice *device) {Device = device;}
public slots:
    void sendMsgHandle(const QString &id,const QString &msg);
signals:
    void runningLog(const QString &id,const QString &log);
    void receiveMsg(const QString &id,const QString &msg);
    void sendMsg(const QString &id,const QString &msg);
    void linkerBuild(const QString &id,const QString &ipaddr,int port);
    void linkerClose(const QString &id);
private:
    QString ServerIPAddr;
    int ServerPort;
    QString DeviceCode;
    QStringList DeviceConfig;
    UserTcpClient *tcpClient;

    UserDevice *Device;

    QString toAddress();
private slots:
    void tcpClientRunningLogHandle(const QString &log);
    void tcpClientLinkerBuildHandle(const QString &ipaddr,int port);
    void tcpClientLinkerCloseHandle();
    void tcpClientReceiveMsgHandle(const QString &msg);
};

#endif // USERCLIENTSOCKETLINK_H
