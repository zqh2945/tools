#ifndef USERSERVERHANDLE_H
#define USERSERVERHANDLE_H

#include <QWidget>
#include "userpacketfieldedit.h"
#include "usercontentfieldedit.h"
#include "useraddressedit.h"
#include "userframeedit.h"
#include "userstackedwidget.h"
#include "userrunninglog.h"
#include "userserverlisten.h"
#include "userserverdevicelink.h"
#include "../source/protocol/userprotocol.h"

class UserServerHandle : public QWidget
{
    Q_OBJECT
public:
    explicit UserServerHandle(QWidget *parent = 0);
    ~UserServerHandle();
    void initialization();
    void setClientAddress(const QString &ipaddr,int port);
    void setServerAddress(const QString &ipaddr,int port);
    void setVersion(int version);
    void setDeviceMN(const QString &mn);
    void setDevicePW(const QString &pw);
    void setDeviceST(const QString &st);

    int findServer(const QString &ipaddr,int port);
    void createServer(const QString &ipaddr,int port);
    void startServer(const QString &ipaddr,int port,const QStringList &mnList);
    void stopServer(const QString &ipaddr,int port);
    void deleteServer(const QString &ipaddr,int port);
    void setCurrentServer(const QString &ipaddr,int port);

    int findDevice(const QString &ipaddr,int port,const QString &mn);
    void createDevice(const QString &ipaddr,int port,const QStringList &baseInfo);
    void connectDevice(const QString &ipaddr,int port,const QString &mn,UserTcpSocket *socket);
    void disconnectDevice(const QString &ipaddr,int port,const QString &mn);
    void deleteDevice(const QString &ipaddr,int port,const QString &mn);
    void setCurrentDevice(const QString &ipaddr,int port,const QString &mn);

    void createServerAllDevice(const QString &ipaddr,int port,const QList<QStringList> &baseInfoList);
    void deleteServerAllDevice(const QString &ipaddr,int port);
signals:
    void linkerBuild(const QString &id,const QString &ipaddr,int port);
    void linkerClose(const QString &id);
private:
    UserPacketFieldEdit *packetFieldEdit;
    UserContentFieldEdit *contentFieldEdit;
    UserAddressEdit *addressEdit;
    UserFrameEdit *frameEdit;
    UserRunningLog *emptyServer;
    UserStackedWidget *stackWidget;

    QList<UserRunningLog*> ServerList;

    UserProtocol *Protocol; //环保国标协议
private slots:
    void packetFieldEditFieldChangedHandle(int num);
    void contentFieldEditFieldChangedHandle(int num);
    void frameEditButtonClickedHandle(int num);
    void listenConnectedHandle(const QString &id,UserTcpSocket *socket);
    void socketLinkerBuildHandle(const QString &id,const QString &ipaddr,int port);
    void socketLinkerCloseHandle(const QString &id);
};

#endif // USERSERVERHANDLE_H
