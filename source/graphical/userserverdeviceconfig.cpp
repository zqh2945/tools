#include "userserverdeviceconfig.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

UserServerDeviceConfig::UserServerDeviceConfig(enum ActionType type,QWidget *parent) : QDialog(parent)
{
    Action = type;

    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    if(Action==NEW) {
        setWindowTitle(tr("创建监测点"));
    } else {
        setWindowTitle(tr("编辑监测点"));
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

    labelST = new UserLabel(tr("系统编码"));
    labelST->setFixedWidth(64);
    comboBoxST = new UserComboBox(UserComboBox::SERVER_ST,version);
    comboBoxST->setCurrentIndex(comboBoxST->findData("32"));
    comboBoxST->setMaxVisibleItems(20);
    comboBoxST->setFixedWidth(192);
    QString systemType = comboBoxST->currentData().toString();

    QHBoxLayout *baseLayout = new QHBoxLayout();
    baseLayout->addWidget(labelVersion);
    baseLayout->addWidget(comboBoxVersion);
    baseLayout->addWidget(labelMN);
    baseLayout->addWidget(lineEditMN);
    baseLayout->addWidget(labelPW);
    baseLayout->addWidget(lineEditPW);
    baseLayout->addWidget(labelST);
    baseLayout->addWidget(comboBoxST);
    baseLayout->setSpacing(4);

    pollutantEdit = new UserPollutantEdit(UserPollutantEdit::SERVER,version,systemType);

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
    mainLayout->addLayout(baseLayout);
    mainLayout->addWidget(pollutantEdit);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setSpacing(12);
    mainLayout->setMargin(10);

    connect(comboBoxVersion,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxVersionCurrentIndexChangedHandle()));
    connect(comboBoxST,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxSTCurrentIndexChangedHandle()));
    connect(buttonAccept,SIGNAL(clicked()),this,SLOT(accept()));
    connect(buttonReject,SIGNAL(clicked()),this,SLOT(reject()));
}

UserServerDeviceConfig::~UserServerDeviceConfig()
{

}
//监测设备基本配置信息
QStringList UserServerDeviceConfig::deviceBaseInfo()
{
    QStringList baseInfo;
    baseInfo.append(comboBoxVersion->currentData().toString());
    baseInfo.append(lineEditMN->text());
    baseInfo.append(lineEditPW->text());
    baseInfo.append(comboBoxST->currentData().toString());
    return baseInfo;
}

//获取监测设备配置信息
QStringList UserServerDeviceConfig::deviceConfig()
{
    QStringList config;
    config.append(comboBoxVersion->currentData().toString());
    config.append(lineEditMN->text());
    config.append(lineEditPW->text());
    config.append(comboBoxST->currentData().toString());
    return config;
}
//设置服务器监测点配置信息
void UserServerDeviceConfig::setDeviceConfig(const QStringList &config)
{
    if(config.count()>=4) {
        comboBoxVersion->setCurrentIndex(comboBoxVersion->findData(config.at(0).toInt()));
        lineEditMN->setText(config.at(1));
        lineEditPW->setText(config.at(2));
        comboBoxST->setCurrentIndex(comboBoxST->findData(config.at(3)));
        pollutantEdit->setVersion(comboBoxVersion->currentData().toInt());
        pollutantEdit->setDeviceST(comboBoxST->currentData().toString());
    }
}
//获取服务器监测点污染监测因子配置参数列表
QList<QStringList> UserServerDeviceConfig::pollutantConfigList()
{
    return pollutantEdit->pollutantList();
}
//设置服务器监测点污染监测因子配置参数列表
void UserServerDeviceConfig::setPollutantConfigList(const QList<QStringList> &list)
{
    pollutantEdit->setPollutantList(list);
}

void UserServerDeviceConfig::comboBoxVersionCurrentIndexChangedHandle()
{
    int version = comboBoxVersion->currentData().toInt();
    lineEditMN->setVersion(version);
    lineEditPW->setVersion(version);
    comboBoxST->setItems(UserComboBox::CLIENT_ST,version);
    comboBoxST->setCurrentIndex(7);
    pollutantEdit->setVersion(version);
}

void UserServerDeviceConfig::comboBoxSTCurrentIndexChangedHandle()
{
    pollutantEdit->setDeviceST(comboBoxST->currentData().toString());
}
