#ifndef USERADDRESSEDIT_H
#define USERADDRESSEDIT_H

#include <QWidget>
#include "../source/graphical/userlabel.h"
#include "../source/graphical/userlineedit.h"

class UserAddressEdit : public QWidget
{
    Q_OBJECT
public:
    enum PlatformType {SERVER = 0,CLIENT = 1};
    explicit UserAddressEdit(enum PlatformType type,QWidget *parent = 0);
    ~UserAddressEdit();
    int version();
    void setVersion(int version);
    QString serverIPAddr();
    int serverPort();
    QString serverAddress() {return lineEditServer->text();}
    void setServerIPAddrAndPort(const QString &ipaddr,int port);
    QString clinetIPAddr();
    int clientPort();
    QString clientAddress() {return lineEditClient->text();}
    void setClientIPAddrAndPort(const QString &ipaddr,int port);
signals:

public slots:

private:
    UserLabel *labelVersion;
    UserLineEdit *lineEditVersion;
    UserLabel *labelServer;
    UserLineEdit *lineEditServer;
    UserLabel *labelDirection;
    UserLabel *labelClient;
    UserLineEdit *lineEditClient;

    QString toIPAddr(const QString &address);
    int toPort(const QString &address);
    QString toAddress(const QString &ipaddr,int port);
};

#endif // USERADDRESSEDIT_H
