#ifndef USERSERVEREDIT_H
#define USERSERVEREDIT_H

#include <QWidget>
#include <QLineEdit>
#include "../source/graphical/userlabel.h"
#include "../source/graphical/useripv4edit.h"
#include "../source/graphical/userportedit.h"

class UserServerEdit : public QWidget
{
    Q_OBJECT
public:
    explicit UserServerEdit(int port,QWidget *parent=0);
    explicit UserServerEdit(const QString &ipaddr,int port,QWidget *parent = 0);
    ~UserServerEdit();
    QString ipaddr() {return ipv4Edit->ipaddr();}
    void setIPAddr(const QString &ipaddr) {ipv4Edit->setIPAddr(ipaddr);}
    int port() {return portEdit->port();}
    void setPort(int port) {portEdit->setPort(port);}
    void setEnabled(bool enable);
signals:

public slots:

private:
    UserLabel *labelIPv4;
    UserIPv4Edit *ipv4Edit;
    UserLabel *labelPort;
    UserPortEdit *portEdit;
    void serverLayout(const QString &ipaddr,int port);
};

#endif // USERSERVEREDIT_H
