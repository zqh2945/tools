#ifndef USERDEVICEEDIT_H
#define USERDEVICEEDIT_H

#include <QWidget>
#include "userlabel.h"
#include "userlineedit.h"
#include "usercombobox.h"
#include "usertablewidget.h"
#include "userbutton.h"

class UserDeviceEdit : public QWidget
{
    Q_OBJECT
public:
    explicit UserDeviceEdit(QWidget *parent = 0);
    ~UserDeviceEdit();
    QStringList deviceCodeList() {return tableWidget->dataColumn(1);}
    QList<QStringList> devicesList() {return tableWidget->datas();}
    void setDeviceList(const QList<QStringList> &list);
signals:

public slots:

private:
    int SelectRow;

    UserLabel *labelVersion;
    UserComboBox *comboBoxVersion;
    UserLabel *labelMN;
    UserLineEdit *lineEditMN;
    UserLabel *labelPW;
    UserLineEdit *lineEditPW;
    UserLabel *labelST;
    UserComboBox *comboBoxST;
    UserTableWidget *tableWidget;
    UserButton *buttonAddition;
    UserButton *buttonModified;
    UserButton *buttonDelete;
private slots:
    void comboBoxVersionCurrentIndexChangedHandle();
    void tableWidgetRowDoubleClickedHandle(int row,const QStringList &list);
    void buttonAdditionClickedHandle();
    void buttonModifiedClickedHandle();
    void buttonDeleteClickedHandle();
};

#endif // USERDEVICEEDIT_H
