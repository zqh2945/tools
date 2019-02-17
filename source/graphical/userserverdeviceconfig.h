#ifndef USERSERVERDEVICECONFIG_H
#define USERSERVERDEVICECONFIG_H

#include <QWidget>
#include <QDialog>
#include "userlabel.h"
#include "userlineedit.h"
#include "usercombobox.h"
#include "userpollutantedit.h"
#include "userbutton.h"

class UserServerDeviceConfig : public QDialog
{
    Q_OBJECT
public:
    enum ActionType {NEW = 0,EDIT = 1};
    UserServerDeviceConfig(enum ActionType type,QWidget *parent);
    ~UserServerDeviceConfig();
    int version() {return comboBoxVersion->currentData().toInt();}
    QString deviceCode() {return lineEditMN->text();}
    QString sytemType() {return comboBoxST->currentData().toString();}

    QStringList deviceBaseInfo();
    QStringList deviceConfig();
    void setDeviceConfig(const QStringList &config);
    QList<QStringList> pollutantConfigList();
    void setPollutantConfigList(const QList<QStringList> &list);
private:
    enum ActionType Action;

    UserLabel *labelVersion;
    UserComboBox *comboBoxVersion;
    UserLabel *labelMN;
    UserLineEdit *lineEditMN;
    UserLabel *labelPW;
    UserLineEdit *lineEditPW;
    UserLabel *labelST;
    UserComboBox *comboBoxST;

    UserPollutantEdit *pollutantEdit;
    UserButton *buttonAccept;
    UserButton *buttonReject;
private slots:
    void comboBoxVersionCurrentIndexChangedHandle();
    void comboBoxSTCurrentIndexChangedHandle();
};

#endif // USERSERVERDEVICE_H
