#ifndef USERCLIENTDEVICE_H
#define USERCLIENTDEVICE_H

#include <QWidget>
#include "userrunninglog.h"
#include "../source/device/userdevice.h"
#include "../source/protocol/userprotocol.h"

class UserClientDevice : public UserRunningLog
{
    Q_OBJECT
public:
    UserClientDevice(const QStringList &baseInfo,QWidget *parent = 0);
    virtual ~UserClientDevice();
    virtual QString identifier(); //获取数采仪唯一标识
    virtual UserDevice* device(); //获取数采仪
    virtual void initialization(); //数采仪初始化
    virtual void start(); //数采仪开机
    virtual void stop(); //数采仪关机
    virtual bool state(); //数采仪状态
    virtual void setChildIdentifirtList(const QStringList &list); //设置数采仪链接槽唯一标识
    virtual void sendMessage(const QString &msg); //数采仪发送消息
    void sendMessage(const QString &id,const QString &msg); //数采仪发送消息给知道链接槽
public slots:
    void socketLinkerBuildHandle(const QString &id,const QString &ipaddr,int port);
    void socketLinkerCloseHandle(const QString &id);
    void socketRunningLogHandle(const QString &id,const QString &log);
    void socketReceiveMsgHandle(const QString &id,const QString &msg);
    void socketSendMsgHandle(const QString &id,const QString &msg);
signals:
    void sendMsg(const QString &id,const QString &msg);
    void linkerBuild(const QString &id,const QString &ipaddr,int port);
    void linkerClose(const QString &id);
private:
    QString DeviceCode; //数采仪编码
    QStringList ConnectIDList; //数采仪链接槽ID列表
    QList<bool> ConnectStateList; //数采仪链接槽状态列表

    UserDevice *Device; //数采仪设备
    UserProtocol *Protocol; //环保国标协议
private slots:
    void deviceRunningLogHandle(const QString &log);
    void deviceSendMsgHandle(const QString &msg);
    void deviceSendMsgHandle(const QString &id,const QString &msg);
};

#endif // USERCLIENTDEVICE_H
