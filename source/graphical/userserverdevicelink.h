#ifndef USERSERVERDEVICELINK_H
#define USERSERVERDEVICELINK_H

#include <QWidget>
#include "userrunninglog.h"
#include "../source/network/usertcpsocket.h"
#include "../source/protocol/userprotocol.h"
#include "../source/device/userdevice.h"

class UserServerDeviceLink : public UserRunningLog
{
    Q_OBJECT
public:
    UserServerDeviceLink(const QString &ipaddr,int port,const QStringList &baseInfo,QWidget *parent = 0);
    virtual ~UserServerDeviceLink();
    virtual QString identifier(); //获取监测点唯一标识
    virtual UserDevice* device(); //获取监测点数采仪
    virtual void initialization(); //监测点数采仪初始化
    virtual void start(UserTcpSocket *socket); //监测点链接
    virtual void stop(); //监测点断开
    virtual bool state(); //监测点状态
    virtual void sendMessage(const QString &msg); //发送消息
signals:
    void linkerBuild(const QString &id,const QString &ipaddr,int port);
    void linkerClose(const QString &id);
private:
    QString DeviceCode;
	QString ServerIPAddr;
	int ServerPort;
    QString SocketIPAddr;
    int SocketPort;
    UserTcpSocket *tcpSocket;

    UserDevice *Device; //监测点数采仪
    UserProtocol *Protocol; //环保国标协议

    QString toServerAddress();
    QString toSocketAddress();
private slots:
    void tcpSocketLinkerCloseHandle();
    void tcpSocketReceiveMsgHandle(const QString &msg);
    void deviceRunningLogHandle(const QString &log);
    void deviceSendMsgHandle(const QString &msg);
};

#endif // USERSERVERDEVICELINK_H
