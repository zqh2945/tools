#include "userserverconfig.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHostInfo>
#include <QHostAddress>
#include <QDebug>

UserServerConfig::UserServerConfig(enum ActionType type,QWidget *parent) : QDialog (parent)
{
    Action = type;

    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    if(Action==NEW) {
        setWindowTitle(tr("创建服务器"));
    } else {
        setWindowTitle(tr("编辑服务器"));
    }

    labelServer = new UserLabel(tr("服务器"));
    labelServer->setFixedWidth(56);
    serverEdit = new UserServerEdit(8095);
    serverEdit->setFixedWidth(272);
    if(Action==EDIT) {serverEdit->setEnabled(false);}

    deviceEdit = new UserDeviceEdit();
    deviceEdit->setFixedWidth(640);
    buttonAccept = new UserButton(tr("确定"));
    buttonReject = new UserButton(tr("取消"));

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(labelServer,0,0,1,1);
    mainLayout->addWidget(serverEdit,0,1,1,5);
    mainLayout->addWidget(deviceEdit,1,0,1,8);
    mainLayout->addWidget(buttonAccept,2,6,1,1);
    mainLayout->addWidget(buttonReject,2,7,1,1);
    mainLayout->setSpacing(12);
    mainLayout->setMargin(10);

    connect(buttonAccept,SIGNAL(clicked()),this,SLOT(accept()));
    connect(buttonReject,SIGNAL(clicked()),this,SLOT(reject()));
}

UserServerConfig::~UserServerConfig()
{

}

void UserServerConfig::setServer(const QString &ipaddr,int port)
{
    serverEdit->setIPAddr(ipaddr);
    serverEdit->setPort(port);
}

void UserServerConfig::setDeviceList(const QList<QStringList> &list)
{
    deviceEdit->setDeviceList(list);
}





