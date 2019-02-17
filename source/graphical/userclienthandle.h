#ifndef USERCLIENTHANDLE_H
#define USERCLIENTHANDLE_H

#include <QWidget>
#include "userpacketfieldedit.h"
#include "userframeedit.h"
#include "useraddressedit.h"
#include "userstackedwidget.h"
#include "userrunninglog.h"
#include "userclientdevice.h"
#include "userclientsocketlink.h"
#include "../source/protocol/userprotocol.h"

class UserClientHandle : public QWidget
{
    Q_OBJECT
public:
    explicit UserClientHandle(QWidget *parent=0);
    ~UserClientHandle();
    void initialization();
    void setClientAddress(const QString &ipaddr,int port);
    void setServerAddress(const QString &ipaddr,int port);
    void setVersion(int version);
    void setDeviceMN(const QString &mn);
    void setDevicePW(const QString &pw);
    void setDeviceST(const QString &st);

    int findDevice(const QString &mn);
    void createDevice(const QStringList &baseInfo);
    void startDevice(const QString &mn,const QList<QStringList> &serList);
    void stopDevice(const QString &mn);
    void deleteDevice(const QString &mn);
    void setCurrentDevice(const QString &mn);

    int findDeviceSocket(const QString &mn,const QString &ipaddr,int port);
    void createDeviceSocket(const QStringList &baseInfo,const QString &ipaddr,int port);
    void startDeviceSocket(const QString &mn,const QString &ipaddr,int port);
    void stopDeviceSocket(const QString &mn,const QString &ipaddr,int port);
    void deleteDeviceSocket(const QString &mn,const QString &ipaddr,int port);
    void setCurrentDeviceSocket(const QString &mn,const QString &ipaddr,int port);

    void createDeviceAllSocket(const QStringList &baseInfo,const QList<QStringList> &serList);
	void startDeviceAllSocket(const QString &mn,const QList<QStringList> &serList);
	void stopDeviceAllSocket(const QString &mn,const QList<QStringList> &serList);
    void deleteDeviceAllSocket(const QString &mn);
signals:
    void linkerBuild(const QString &id,const QString &ipaddr,int port);
    void linkerClose(const QString &id);
private:
    UserPacketFieldEdit *packetFieldEdit;
    UserAddressEdit *addressEdit;
    UserFrameEdit *frameEdit;
    UserRunningLog* emptyClient;
    UserStackedWidget *stackWidget;

    QList<UserRunningLog*> ClientList;

    UserProtocol *Protocol; //当前环保国标协议
private slots:
    void packetFieldEditFieldChangedHandle(int num);
    void frameEditButtonClickedHandle(int num);
    void clientSocketLinkerBuildHandle(const QString &id,const QString &ipaddr,int port);
    void clientSocketLinkerCloseHandle(const QString &id);
};

#endif // USERCLIENTHANDLE_H
