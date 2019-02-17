#ifndef USERPACKETFIELDEDIT_H
#define USERPACKETFIELDEDIT_H

#include <QWidget>
#include "userlabel.h"
#include "userlineedit.h"
#include "usercombobox.h"
#include "usertimeedit.h"
#include "userdatetimeedit.h"

class UserPacketFieldEdit : public QWidget
{
    Q_OBJECT
public:
    enum PlatformType {SERVER = 0,CLIENT = 1};
    explicit UserPacketFieldEdit(enum PlatformType type,int version = 1,QWidget *parent = 0);
    ~UserPacketFieldEdit();
    void setVersion(int version);
    QString fieldMN() {return FieldMN;}
    void setFieldMN(const QString &mn) {lineEditMN->setText(mn);}
    QString fieldPW() {return FieldPW;}
    void setFieldPW(const QString &pw) {lineEditPW->setText(pw);}
    QString fieldST() {return FieldST;}
    void setFiledST(const QString &st);
    int fieldCN() {return FieldCN;}
    int fieldFlag() {return FieldFlag;}
signals:
    void filedChanged(int num);
public slots:

private:
    UserLabel *labelMN;
    UserLineEdit *lineEditMN;
    UserLabel *labelPW;
    UserLineEdit *lineEditPW;
    UserLabel *labelST;
    UserComboBox *comboBoxST;
    UserLabel *labelCN;
    UserComboBox *comboBoxCN;
    UserLabel *labelFlag;
    UserComboBox *comboBoxFlag;

    enum PlatformType Platform;
    QString FieldMN;
    QString FieldPW;
    QString FieldST;
    int FieldCN;
    int FieldFlag;

private slots:
    void lineEditMNTextChangedHandle(const QString &text);
    void lineEditPWTextChangedHandle(const QString &text);
    void comboBoxSTIndexChangedHandle();
    void comboBoxCNIndexChangedHandle();
    void comboBoxFlagIndexChangedHandle();

};

#endif // USERPACKETFIELDEDIT_H
