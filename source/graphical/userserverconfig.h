#ifndef USERSERVERCONFIG_H
#define USERSERVERCONFIG_H

#include <QDialog>
#include <QWidget>
#include "userlabel.h"
#include "usercombobox.h"
#include "userserveredit.h"
#include "userdeviceedit.h"
#include "userbutton.h"

class UserServerConfig : public QDialog
{
    Q_OBJECT
public:
    enum ActionType {NEW = 0,EDIT = 1};
    UserServerConfig(enum ActionType type,QWidget *parent);
    ~UserServerConfig();
    QString ipaddr() {return serverEdit->ipaddr();}
    int port() {return serverEdit->port();}
    void setServer(const QString &ipaddr,int port);
    QString address() {return QString("%1:%2").arg(serverEdit->ipaddr()).arg(serverEdit->port());}
    QString filename() {return QString("%1(%2)").arg(serverEdit->ipaddr()).arg(serverEdit->port());}
    QStringList deviceCodeList() {return deviceEdit->deviceCodeList();}
    QList<QStringList> devicesList() {return deviceEdit->devicesList();}
    void setDeviceList(const QList<QStringList> &list);

private:
    enum ActionType Action;

    UserLabel *labelServer;
    UserServerEdit *serverEdit;
    UserDeviceEdit *deviceEdit;
    UserButton *buttonAccept;
    UserButton *buttonReject;
};

#endif // USERSERVERCONFIG_H
