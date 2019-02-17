#ifndef USERCLIENTCONFIG_H
#define USERCLIENTCONFIG_H

#include <QWidget>
#include <QDialog>
#include <QNetworkAddressEntry>
#include "userlabel.h"
#include "userlineedit.h"
#include "useripv4edit.h"
#include "usercombobox.h"
#include "usercheckbox.h"
#include "userserveredit.h"
#include "userportedit.h"
#include "userpollutantedit.h"
#include "userbutton.h"

class UserClientConfig : public QDialog
{
    Q_OBJECT
public:
    enum ActionType {NEW = 0,EDIT = 1};
    UserClientConfig(enum ActionType type,QWidget *parent);
    ~UserClientConfig();
    QString deviceCode() {return lineEditMN->text();}
    QStringList deviceBaseInfo();
    QStringList deviceConfig();
    void setDeviceConfig(const QStringList &config);
    int serverCount() {return ServerCount;}
    QStringList serverConfig(int num);
    void setServerConfig(int num,const QStringList &config);
    QList<QStringList> serverConfigList();
    void setServerConfigList(const QList<QStringList> &list);
    QList<QStringList> pollutantConfigList();
    void setPollutantConfigList(const QList<QStringList> &list);
signals:

public slots:

private:
    enum ActionType Action;
    const int ServerCount = 4;

    UserLabel *labelVersion;
    UserComboBox *comboBoxVersion;
    UserLabel *labelMN;
    UserLineEdit *lineEditMN;
    UserLabel *labelMNHint;
    UserLabel *labelPW;
    UserLineEdit *lineEditPW;
    UserLabel *labelST;
    UserComboBox *comboBoxST;

    UserLabel *labelIPAddr;
    UserIPv4Edit *ipv4EditIPAddr;
    UserLabel *labelNetmask;
    UserIPv4Edit *ipv4EditNetmask;
    UserLabel *labelGateway;
    UserIPv4Edit *ipv4EditGateway;

    UserCheckBox *checkBoxEnable[4];
    UserServerEdit *serverEdit[4];

    UserPollutantEdit *pollutantEdit;
    UserButton *buttonAccept;
    UserButton *buttonReject;

    QNetworkAddressEntry defalutAdapterAddress();
private slots:
    void comboBoxVersionCurrentIndexChangedHandle();
    void comboBoxSTCurrentIndexChangedHandle();
    void checkBoxOneClickedHandle(bool checked);
    void checkBoxTwoClickedHandle(bool checked);
    void checkBoxThreeClickedHandle(bool checked);
    void checkBoxFourClickedHandle(bool checked);
};

#endif // USERCLIENTCONFIG_H
