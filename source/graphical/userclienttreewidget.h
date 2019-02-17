#ifndef USERCLIENTTREEWIDGET_H
#define USERCLIENTTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "userdeviceedit.h"

class UserClientTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    UserClientTreeWidget();
    ~UserClientTreeWidget();

    bool isMainItem(QTreeWidgetItem *item);
    bool findMainItem(const QString &mn);
    void addMainItem(const QStringList &baseInfo);
    void startMainItem(QTreeWidgetItem *item);
    void stopMainItem(QTreeWidgetItem *item);
    void deleteMainItem(QTreeWidgetItem *item);

    bool isSubItem(QTreeWidgetItem *item);
    void addSubItem(const QString &mn,const QString &objIP,int objPort);
    void connectSubItem(const QString &mn,const QString &objIP,int objPort,const QString &srcIP,int srcPort);
    void disconnectSubItem(const QString &mn,const QString &objIP,int objPort);
    void deleteSubItem(QTreeWidgetItem *item);

    void addMainAllSubItem(const QString &mn,const QList<QStringList> &serList);
    void deleteMainAllSubItem(QTreeWidgetItem *item);

    void initialization();
    QString deviceCode() {return DeviceTitle;}
    int deviceState() {return DeviceState;}
    int deviceVersion() {return DeviceBaseInfo.first().toInt();}
    QStringList deviceBaseInfo() {return DeviceBaseInfo;}
    int deviceServerCount() {return DeviceServerCount;}
    QList<QStringList> deviceServerList() {return DeviceServerList;}

    int serverState() {return ServerState;}
    QString localIPaddr() {return LocalIPAddr;}
    int localPort() {return LocalPort;}
    QString serverIPAddr() {return ServerIPAddr;}
    int serverPort() {return ServerPort;}

signals:
    void mainItemClicked(int state);
    void subItemClicked(int state);
    void mainItemDoubleClicked(int state);
    void subItemDoubleClicked(int state);
    void mainItemRightClicked(int state);
    void subItemRightClicked(int state);
public slots:

private:
    QString DeviceTitle; //设备标题
    int DeviceState; //设备状态，0表示断开，1表示链接
    QStringList DeviceBaseInfo; //设备基本信息,VER,MN,PW,ST
    int DeviceServerCount; //设备服务器个数
    QList<QStringList> DeviceServerList; //设备服务器列表

    QString ServerTitle; //服务器标题
    int ServerState; //服务器状态，0表示暂停，1表示启用
    QString LocalIPAddr; //本地地址
    int LocalPort; //本地端口
    QString ServerIPAddr; //服务器地址
    int ServerPort; //服务器端口

    QString toAddress(const QString &ipaddr,int port);
    void getDevice(QTreeWidgetItem *item);
    void getServer(QTreeWidgetItem *item);
private slots:
    void itemClickedHandle(QTreeWidgetItem *item);
    void itemDoubleClickedHandle(QTreeWidgetItem *item);
    void itemRightClickedHandle(const QPoint &pos);
};

#endif // USERCLIENTTREEWIDGET_H
