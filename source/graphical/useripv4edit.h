#ifndef USERIPEDIT_H
#define USERIPEDIT_H

#include <QLineEdit>

class UserIPv4Edit : public QLineEdit
{
    Q_OBJECT
public:
    UserIPv4Edit(const QString &ipaddr);
    ~UserIPv4Edit();
    QString ipaddr() {return text();}
    void setIPAddr(const QString &ipaddr) {setText(ipaddr);}
};

#endif // USERIPEDIT_H
