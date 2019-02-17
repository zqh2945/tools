#ifndef USERSERVERTREEWIDGET_H
#define USERSERVERTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "userdeviceedit.h"

class UserServerTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    UserServerTreeWidget();
    ~UserServerTreeWidget();

    bool isMainItem(QTreeWidgetItem *item);
    bool findMainItem(const QString &ipaddr,int port);
    void addMainItem(const QString &ipaddr,int port);
    void startMainItem(QTreeWidgetItem *item);
    void stopMainItem(QTreeWidgetItem *item);
    void deleteMainItem(QTreeWidgetItem *item);

    bool isSubItem(QTreeWidgetItem *item);
    bool findSubItem(const QString &ipaddr,int port,const QString &mn);
    void addSubItem(const QString &ipaddr,int port,const QStringList &baseInfo);
    void editSubItem(const QString &ipaddr,int port,const QStringList &baseInfo);
    void connectSubItem(const QString &srcIP,int srcPort,const QString &mn,const QString &objIP,int objPort);
    void disconnectSubItem(const QString &ipaddr,int port,const QString &mn);
    void deleteSubItem(QTreeWidgetItem *item);

    void addMainAllSubItem(const QString &ipaddr,int port,const QList<QStringList> &baseInfoList);
    void deleteMainAllSubItem(QTreeWidgetItem *item);

    void initialization();
    QString address() {return ServerTitle;}
    int serverState() {return ServerState;}
    QString serverIPAddr() {return ServerIPAddr;}
    int serverPort() {return ServerPort;}
    int serverDeviceCount() {return ServerDeviceCount;}
    QStringList serverDeviceList() {return ServerDeviceList;}

    QString deviceCode() {return DeviceTitle;}
    int deviceState() {return DeviceState;}
    int deviceVersion() {return DeviceBaseInfo.first().toInt();}
    QStringList deviceBaseInfo() {return DeviceBaseInfo;}
    QString deviceIPAddr() {return DeviceIPAddr;}
    int devicePort() {return DevicePort;}
signals:
    void mainItemClicked(int state);
    void subItemClicked(int state);
    void mainItemDoubleClicked(int state);
    void subItemDoubleClicked(int state);
    void mainItemRightClicked(int state);
    void subItemRightClicked(int state);
public slots:

private:
    QString ServerTitle; //服务器标题
    int ServerState; //服务器状态，0表示暂停，1表示启用
    QString ServerIPAddr; //服务器IP地址
    int ServerPort; //服务器端口
    int ServerDeviceCount; //设备个数
    QStringList ServerDeviceList; //设备列表

    QString DeviceTitle; //设备标题
    int DeviceState; //设备状态，0表示断开，1表示链接
    QStringList DeviceBaseInfo; //设备基本信息，包括VER,MN、PW、ST
    QString DeviceIPAddr; //设备IP地址
    int DevicePort; //设备端口编号

    QString toAddress(const QString &ipaddr,int port);
    void getServer(QTreeWidgetItem *item);
    void getDevice(QTreeWidgetItem *item);
private slots:
    void itemClickedHandle(QTreeWidgetItem *item);
    void itemDoubleClickedHandle(QTreeWidgetItem *item);
    void itemRightClickedHandle(const QPoint &pos);
};

#endif // USERSERVERTREEWIDGET_H
