#ifndef USERRUNNINGLOG_H
#define USERRUNNINGLOG_H

#include <QWidget>
#include <QTextEdit>
#include "userlabel.h"
#include "userbutton.h"
#include "../source/network/usertcpsocket.h"
#include "../source/device/userdevice.h"

class UserRunningLog : public QWidget
{
    Q_OBJECT
public:
    enum PlatformType {EMPTY = 0,SERVER = 1,CLIENT = 2,SERVER_DEVICE = 3,CLIENT_LINKER = 4};
    explicit UserRunningLog(enum PlatformType type,QWidget *parent = 0);
    virtual ~UserRunningLog();
    virtual QString identifier(); //获取设备唯一标识
    virtual UserDevice* device(); //获取设备
    virtual void initialization(); //设备初始化
    virtual void start(UserTcpSocket *socket); //设备启动
    virtual void start(); //设备启动
    virtual void stop(); //设备停止
    virtual bool state(); //设备状态
    virtual void setChildIdentifirtList(const QStringList &list); //设置设备的自身唯一标识列表
    virtual void sendMessage(const QString &msg); //发送消息

    void setTitle(const QString &ipaddr,int port);
    void setTitle(const QString &mn);
    void appendRunningLog(const QString &log);
    void appendSendMsg(const QString &target,const QString &msg);
    void appendReceiveMsg(const QString &target,const QString &msg);
  signals:

public slots:

private:
    enum PlatformType Platform;

    UserLabel *labelTitle;
    UserButton *buttonClear;
    QTextEdit *textEditLog;
private slots:
    void buttonClearClickedHandle();
};

#endif // USERRUNNINGLOG_H
