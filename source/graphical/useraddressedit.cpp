#include "useraddressedit.h"
#include <QHBoxLayout>

UserAddressEdit::UserAddressEdit(enum PlatformType type,QWidget *parent) : QWidget(parent)
{
    labelVersion = new UserLabel(tr("标准版本"));
    labelVersion->setFixedWidth(64);
    lineEditVersion = new UserLineEdit(UserLineEdit::NONE);
    lineEditVersion->setText("HJ/T212-2016");
    lineEditVersion->setFixedWidth(128);
    lineEditVersion->setReadOnly(true);
    lineEditVersion->setEnabled(false);

    labelServer = new UserLabel(tr("服 务 器"));
    labelServer->setFixedWidth(64);
    lineEditServer = new UserLineEdit(UserLineEdit::IP);
    lineEditServer->setFixedWidth(178);
    lineEditServer->setReadOnly(true);
    lineEditServer->setEnabled(false);

    labelDirection = new UserLabel(tr("<-------->"));
    labelDirection->setFixedWidth(80);
    labelClient = new UserLabel(tr("数 采 仪"));
    labelClient->setFixedWidth(64);
    lineEditClient = new UserLineEdit(UserLineEdit::IP);
    lineEditClient->setFixedWidth(178);
    lineEditClient->setReadOnly(true);
    lineEditClient->setEnabled(false);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(labelVersion);
    mainLayout->addWidget(lineEditVersion);
    if(type==SERVER) {
        mainLayout->addWidget(labelServer);
        mainLayout->addWidget(lineEditServer);
        mainLayout->addWidget(labelDirection);
        mainLayout->addWidget(labelClient);
        mainLayout->addWidget(lineEditClient);
    } else if(type==CLIENT) {
        mainLayout->addWidget(labelClient);
        mainLayout->addWidget(lineEditClient);
        mainLayout->addWidget(labelDirection);
        mainLayout->addWidget(labelServer);
        mainLayout->addWidget(lineEditServer);
    }
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);
}

UserAddressEdit::~UserAddressEdit()
{

}

int UserAddressEdit::version()
{
    if(lineEditVersion->text()=="HJ/T212-2005") {
        return 0;
    } else if(lineEditVersion->text()=="HJ/T212-2016") {
        return 1;
    } else {
        return 1;
    }
}

void UserAddressEdit::setVersion(int version)
{
    if(version==0) {
        lineEditVersion->setText("HJ/T212-2015");
    } else if(version==1) {
        lineEditVersion->setText("HJ/T212-2016");
    }
}

QString UserAddressEdit::serverIPAddr()
{
    return toIPAddr(lineEditServer->text());
}

int UserAddressEdit::serverPort()
{
    return toPort(lineEditServer->text());
}

void UserAddressEdit::setServerIPAddrAndPort(const QString &ipaddr,int port)
{
    lineEditServer->setText(toAddress(ipaddr,port));
}

QString UserAddressEdit::clinetIPAddr()
{
    return toIPAddr(lineEditClient->text());
}

int UserAddressEdit::clientPort()
{
    return toPort(lineEditClient->text());
}

void UserAddressEdit::setClientIPAddrAndPort(const QString &ipaddr,int port)
{
    lineEditClient->setText(toAddress(ipaddr,port));
}

QString UserAddressEdit::toIPAddr(const QString &address)
{
    return address.left(address.indexOf(':',0));
}

int UserAddressEdit::toPort(const QString &address)
{
    int pos = address.indexOf(':',0) + 1;
    return address.mid(pos,address.length()-pos).toInt();
}

QString UserAddressEdit::toAddress(const QString &ipaddr,int port)
{
    return QString("%1:%2").arg(ipaddr).arg(port);
}

