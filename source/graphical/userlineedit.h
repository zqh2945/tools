#ifndef USERLINEEDIT_H
#define USERLINEEDIT_H

#include <QLineEdit>
#include <QHostAddress>

class UserLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    enum TextType {NONE = 0,MN = 1,PW = 2,IP = 3};
    UserLineEdit(enum TextType type,int version = 1);
    ~UserLineEdit();
    void setVersion(int version);
    void setAddress(const QString &ipaddr,int port);
private slots:
    void textChangedHandle(const QString &text);
private:
    enum TextType LineType;
    int Version;
};

#endif // USERLINEEDIT_H
