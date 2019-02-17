#ifndef USERPOLLUTANTEDIT_H
#define USERPOLLUTANTEDIT_H

#include <QWidget>
#include "userlabel.h"
#include "usercombobox.h"
#include "userlineedit.h"
#include "usertablewidget.h"
#include "userbutton.h"

class UserPollutantEdit : public QWidget
{
    Q_OBJECT
public:
    enum PlatformType {SERVER = 0,CLIENT = 1};
    explicit UserPollutantEdit(enum PlatformType type,int version = 1,const QString &st = "32",QWidget *parent = 0);
    QList<QStringList> pollutantList() {return tableWidget->datas();}
    void setPollutantList(const QList<QStringList> &list);
    void setVersion(int version);
    void setDeviceST(const QString &st);
      ~UserPollutantEdit();
signals:

public slots:

private:
    enum PlatformType Platform;
    int Version;
    QString DeviceST;
    int SelectRow;

    UserLabel *labelCode;
    UserComboBox *comboBoxCode;
    UserLabel *labelName;
    UserLineEdit *lineEditName;
    UserLabel *labelType;
    UserComboBox *comboBoxType;
    UserLabel *labelDensityUnit;
    UserComboBox *comboBoxDensityUnit;
    UserLabel *labelDensityDot;
    UserComboBox *comboBoxDensityDot;
    UserLabel *labelQuantityUnit;
    UserComboBox *comboBoxQuantityUnit;
    UserLabel *labelQuantityDot;
    UserComboBox *comboBoxQuantityDot;
    UserButton *buttonAddition;
    UserButton *buttonModified;
    UserButton *buttonDelete;
    UserTableWidget *tableWidget;

    void setDefaultPollutantList(int version,const QString &st);
    void setComboBoxCurrentIndex(int version,const QString &st);
private slots:
    void comboBoxCodeCurrentIndexChangedHandle();
    void tableWidgetRowDoubleClickedHandle(int row,const QStringList &list);
    void buttonAdditionClickedHandle();
    void buttonModifiedClickedHandle();
    void buttonDeleteClickedHandle();
  };

#endif // USERPOLLUTANTEDIT_H
