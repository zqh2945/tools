#include "userserveredit.h"
#include <QHBoxLayout>
#include <QHostInfo>

UserServerEdit::UserServerEdit(int port,QWidget *parent) : QWidget(parent)
{
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    QHostAddress address("0.0.0.0");
    for(int i=1;i<hostInfo.addresses().count();i++) {
        if(hostInfo.addresses().at(i).protocol()==QAbstractSocket::IPv4Protocol) {
            address = hostInfo.addresses().at(i);
            break;
        }
    }
    serverLayout(address.toString(),port);
}

UserServerEdit::UserServerEdit(const QString &ipaddr,int port,QWidget *parent) : QWidget(parent)
{
    serverLayout(ipaddr,port);
}

UserServerEdit::~UserServerEdit()
{

}

void UserServerEdit::setEnabled(bool enable)
{
    ipv4Edit->setEnabled(enable);
    portEdit->setEnabled(enable);
}

void UserServerEdit::serverLayout(const QString &ipaddr,int port)
{
    labelIPv4 = new UserLabel(tr("IP地址"));
    labelIPv4->setFixedWidth(48);
    ipv4Edit = new UserIPv4Edit(ipaddr);
    ipv4Edit->setFixedWidth(128);
    labelPort = new UserLabel(tr("端口"));
    labelPort->setFixedWidth(32);
    portEdit = new UserPortEdit(port);
    portEdit->setFixedWidth(48);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(labelIPv4);
    layout->addWidget(ipv4Edit);
    layout->addWidget(labelPort);
    layout->addWidget(portEdit);
    layout->setSpacing(5);
    layout->setMargin(0);
}
