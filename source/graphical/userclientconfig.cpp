#include "userclientconfig.h"
#include "../source/files/userdefaultparameter.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHostAddress>
#include <QDebug>

UserClientConfig::UserClientConfig(enum ActionType type,QWidget *parent) : QDialog(parent)
{
    Action = type;

    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    if(Action==NEW) {
        setWindowTitle(tr("创建客户端"));
    } else {
        setWindowTitle(tr("编辑客户端"));
    }

    labelVersion = new UserLabel(tr("标准版本"));
    labelVersion->setFixedWidth(64);
    comboBoxVersion = new UserComboBox(UserComboBox::PROTOCOL);
    comboBoxVersion->setCurrentIndex(1);
    comboBoxVersion->setFixedWidth(136);
    if(Action==EDIT) {comboBoxVersion->setEnabled(false);}
    int version = comboBoxVersion->currentData().toInt();

    labelMN = new UserLabel(tr("设备编码"));
    labelMN->setFixedWidth(64);
    lineEditMN = new UserLineEdit(UserLineEdit::MN);
    lineEditMN->setFixedWidth(220);
    if(Action==EDIT) {lineEditMN->setEnabled(false);}

    labelPW = new UserLabel(tr("设备密码"));
    labelPW->setFixedWidth(64);
    lineEditPW = new UserLineEdit(UserLineEdit::PW);
    lineEditPW->setFixedWidth(64);
    if(Action==EDIT) {lineEditPW->setEnabled(false);}

    labelST = new UserLabel(tr("系统编码"));
    labelST->setFixedWidth(64);
    comboBoxST = new UserComboBox(UserComboBox::CLIENT_ST,version);
    comboBoxST->setCurrentIndex(comboBoxST->findData("32"));
    comboBoxST->setFixedWidth(192);
    if(Action==EDIT) {comboBoxST->setEnabled(false);}
    QString systemType = comboBoxST->currentData().toString();

    QHBoxLayout *baseInfoLayout = new QHBoxLayout();
    baseInfoLayout->addWidget(labelVersion);
    baseInfoLayout->addWidget(comboBoxVersion);
    baseInfoLayout->addWidget(labelMN);
    baseInfoLayout->addWidget(lineEditMN);
    baseInfoLayout->addWidget(labelPW);
    baseInfoLayout->addWidget(lineEditPW);
    baseInfoLayout->addWidget(labelST);
    baseInfoLayout->addWidget(comboBoxST);
    baseInfoLayout->setSpacing(4);

    QNetworkAddressEntry adapter = defalutAdapterAddress();
    labelIPAddr = new UserLabel(tr("IP地址"));
    labelIPAddr->setFixedWidth(64);
    ipv4EditIPAddr = new UserIPv4Edit(adapter.ip().toString());
    ipv4EditIPAddr->setEnabled(false);
    ipv4EditIPAddr->setFixedWidth(178);
    labelNetmask = new UserLabel(tr("子网掩码"));
    labelNetmask->setFixedWidth(64);
    ipv4EditNetmask = new UserIPv4Edit(adapter.netmask().toString());
    ipv4EditNetmask->setEnabled(false);
    ipv4EditNetmask->setFixedWidth(178);
    labelGateway = new UserLabel(tr("默认网关"));
    labelGateway->setFixedWidth(64);
    ipv4EditGateway = new UserIPv4Edit(adapter.broadcast().toString());
    ipv4EditGateway->setEnabled(false);
    ipv4EditGateway->setFixedWidth(178);
    QHBoxLayout *adapterLayout = new QHBoxLayout();
    adapterLayout->addWidget(labelIPAddr);
    adapterLayout->addWidget(ipv4EditIPAddr);
    adapterLayout->addWidget(labelNetmask);
    adapterLayout->addWidget(ipv4EditNetmask);
    adapterLayout->addWidget(labelGateway);
    adapterLayout->addWidget(ipv4EditGateway);
    adapterLayout->addSpacing(146);
    adapterLayout->setSpacing(4);

    checkBoxEnable[0] = new UserCheckBox(tr("服务器一"),true);
    checkBoxEnable[0]->setFixedWidth(80);
    serverEdit[0] = new UserServerEdit(8095);
    serverEdit[0]->setEnabled(true);
    serverEdit[0]->setFixedWidth(272);
    checkBoxEnable[1] = new UserCheckBox(tr("服务器二"),false);
    checkBoxEnable[1]->setFixedWidth(80);
    serverEdit[1] = new UserServerEdit(8096);
    serverEdit[1]->setEnabled(false);
    serverEdit[1]->setFixedWidth(272);
    checkBoxEnable[2] = new UserCheckBox(tr("服务器三"),false);
    checkBoxEnable[2]->setFixedWidth(80);
    serverEdit[2] = new UserServerEdit(8097);
    serverEdit[2]->setEnabled(false);
    serverEdit[2]->setFixedWidth(272);
    checkBoxEnable[3] = new UserCheckBox(tr("服务器四"),false);
    checkBoxEnable[3]->setFixedWidth(80);
    serverEdit[3] = new UserServerEdit(8098);
    serverEdit[3]->setEnabled(false);
    serverEdit[3]->setFixedWidth(272);
    QHBoxLayout *ser0Layout = new QHBoxLayout();
    ser0Layout->addWidget(checkBoxEnable[0]);
    ser0Layout->addWidget(serverEdit[0]);
    ser0Layout->addSpacing(184);
    ser0Layout->addWidget(checkBoxEnable[1]);
    ser0Layout->addWidget(serverEdit[1]);
    QHBoxLayout *ser1Layout = new QHBoxLayout();
    ser1Layout->addWidget(checkBoxEnable[2]);
    ser1Layout->addWidget(serverEdit[2]);
    ser1Layout->addSpacing(184);
    ser1Layout->addWidget(checkBoxEnable[3]);
    ser1Layout->addWidget(serverEdit[3]);
    QVBoxLayout *serverLayout = new QVBoxLayout();
    serverLayout->addLayout(ser0Layout);
    serverLayout->addLayout(ser1Layout);
    serverLayout->setSpacing(4);

    pollutantEdit = new UserPollutantEdit(UserPollutantEdit::CLIENT,version,systemType);
    buttonAccept = new UserButton(tr("确定"));
    buttonAccept->setFixedWidth(72);
    buttonReject = new UserButton(tr("取消"));
    buttonReject->setFixedWidth(72);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacing(748);
    buttonLayout->addWidget(buttonAccept);
    buttonLayout->addWidget(buttonReject);
    buttonLayout->setSpacing(4);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(baseInfoLayout);
    mainLayout->addLayout(adapterLayout);
    mainLayout->addLayout(serverLayout);
    mainLayout->addWidget(pollutantEdit);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setSpacing(12);
    mainLayout->setMargin(10);

    connect(comboBoxVersion,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxVersionCurrentIndexChangedHandle()));
    connect(comboBoxST,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxSTCurrentIndexChangedHandle()));
    connect(checkBoxEnable[0],SIGNAL(clicked(bool)),this,SLOT(checkBoxOneClickedHandle(bool)));
    connect(checkBoxEnable[1],SIGNAL(clicked(bool)),this,SLOT(checkBoxTwoClickedHandle(bool)));
    connect(checkBoxEnable[2],SIGNAL(clicked(bool)),this,SLOT(checkBoxThreeClickedHandle(bool)));
    connect(checkBoxEnable[3],SIGNAL(clicked(bool)),this,SLOT(checkBoxFourClickedHandle(bool)));
    connect(buttonAccept,SIGNAL(clicked()),this,SLOT(accept()));
    connect(buttonReject,SIGNAL(clicked()),this,SLOT(reject()));
}

UserClientConfig::~UserClientConfig()
{

}
//获取默认适配器信息
QNetworkAddressEntry UserClientConfig::defalutAdapterAddress()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    QNetworkAddressEntry adapter;
    QHostAddress address("");
    address.setAddress("192.168.0.100"); adapter.setIp(address);
    address.setAddress("225.225.225.0"); adapter.setNetmask(address);
    address.setAddress("192.168.0.1"); adapter.setBroadcast(address);
    for(int i = 0;i < list.first().addressEntries().count(); i++) {
        address = list.first().addressEntries().at(i).ip();
        if(address.protocol()==QAbstractSocket::IPv4Protocol) {
            adapter = list.first().addressEntries().at(i);
            break;
        }
    }
    return adapter;
}
//获取客户端设备基本信息
QStringList UserClientConfig::deviceBaseInfo()
{
    QStringList baseInfo;
    baseInfo.append(comboBoxVersion->currentData().toString());
    baseInfo.append(lineEditMN->text());
    baseInfo.append(lineEditPW->text());
    baseInfo.append(comboBoxST->currentData().toString());
    return baseInfo;
}
//获取客户端设备配置参数
QStringList UserClientConfig::deviceConfig()
{
    QStringList config;
    config.append(comboBoxVersion->currentData().toString());
    config.append(lineEditMN->text());
    config.append(lineEditPW->text());
    config.append(comboBoxST->currentData().toString());
    return config;
}
//设置客户端设备配置参数
void UserClientConfig::setDeviceConfig(const QStringList &config)
{
    if(config.count()>=4) {
        int version = config.at(0).toInt();
        comboBoxVersion->setCurrentIndex(comboBoxVersion->findData(version));
        lineEditMN->setText(config.at(1));
        lineEditPW->setText(config.at(2));
        QString systemType = config.at(3);
        comboBoxST->setCurrentIndex(comboBoxST->findData(systemType));
    }
}
//获取客户端服务器配置参数
QStringList UserClientConfig::serverConfig(int num)
{
    QStringList config;
    if(num<ServerCount) {
        config.append(QString::number(checkBoxEnable[num]->check()));
        config.append(serverEdit[num]->ipaddr());
        config.append(QString::number(serverEdit[num]->port()));
    }
    return config;
}

//设置客户端服务器配置参数
void UserClientConfig::setServerConfig(int num,const QStringList &config)
{
    if(num<ServerCount && config.count()>=3) {
        checkBoxEnable[num]->setCheck(config.at(0).toInt());
        if(config.at(0).toInt()==1) {
            serverEdit[num]->setEnabled(true);
        } else {
            serverEdit[num]->setEnabled(false);
        }
        serverEdit[num]->setIPAddr(config.at(1));
        serverEdit[num]->setPort(config.at(2).toInt());
    }
}

//获取客户端服务器配置参数列表
QList<QStringList> UserClientConfig::serverConfigList()
{
    QList<QStringList> list;
    for(int i=0;i<ServerCount;i++) {
        list.append(serverConfig(i));
    }
    return list;
}
//设置客户端服务器配置参数列表
void UserClientConfig::setServerConfigList(const QList<QStringList> &list)
{
    if(list.count()>=ServerCount) {
        for(int i=0;i<ServerCount;i++) {
            setServerConfig(i,list.at(i));
        }
    }
}
//获取客户端污染监测因子配置参数列表
QList<QStringList> UserClientConfig::pollutantConfigList()
{
    return pollutantEdit->pollutantList();
}
//设置客户端污染监测因子配置参数列表
void UserClientConfig::setPollutantConfigList(const QList<QStringList> &list)
{
    pollutantEdit->setPollutantList(list);
}

void UserClientConfig::comboBoxVersionCurrentIndexChangedHandle()
{
    int version = comboBoxVersion->currentData().toInt();
    lineEditMN->setVersion(version);
    lineEditPW->setVersion(version);
    comboBoxST->setItems(UserComboBox::CLIENT_ST,version);
    comboBoxST->setCurrentIndex(comboBoxST->findData("32"));
    pollutantEdit->setVersion(version);
}

void UserClientConfig::comboBoxSTCurrentIndexChangedHandle()
{
    pollutantEdit->setDeviceST(comboBoxST->currentData().toString());
}

void UserClientConfig::checkBoxOneClickedHandle(bool checked)
{
    serverEdit[0]->setEnabled(checked);
}

void UserClientConfig::checkBoxTwoClickedHandle(bool checked)
{
    serverEdit[1]->setEnabled(checked);
}

void UserClientConfig::checkBoxThreeClickedHandle(bool checked)
{
    serverEdit[2]->setEnabled(checked);
}

void UserClientConfig::checkBoxFourClickedHandle(bool checked)
{
    serverEdit[3]->setEnabled(checked);
}
