#include "userpacketfieldedit.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

UserPacketFieldEdit::UserPacketFieldEdit(enum PlatformType type,int version,QWidget *parent) : QWidget(parent)
{
    Platform = type;

    labelMN = new UserLabel(tr("设备编码"));
    labelMN->setFixedWidth(64);
    lineEditMN = new UserLineEdit(UserLineEdit::MN,version);
    lineEditMN->setFixedWidth(248);

    labelPW = new UserLabel(tr("设备密码"));
    labelPW->setFixedWidth(64);
    lineEditPW = new UserLineEdit(UserLineEdit::PW,version);
    lineEditPW->setFixedWidth(96);

    labelST = new UserLabel(tr("系统编号"));
    labelST->setFixedWidth(64);
    if(Platform==SERVER) {
        comboBoxST = new UserComboBox(UserComboBox::SERVER_ST,version);
    } else if(Platform==CLIENT) {
        comboBoxST = new UserComboBox(UserComboBox::CLIENT_ST,version);
    }
    comboBoxST->setCurrentIndex(comboBoxST->findData("32"));
    comboBoxST->setMaxVisibleItems(20);
    comboBoxST->setFixedWidth(232);

    labelCN = new UserLabel(tr("命令编号"));
    labelCN->setFixedWidth(64);
    if(Platform==SERVER) {
        comboBoxCN = new UserComboBox(UserComboBox::SERVER_CN,version);
        comboBoxCN->setCurrentIndex(1);
    } else if(Platform==CLIENT) {
        comboBoxCN = new UserComboBox(UserComboBox::CLIENT_CN,version);
        comboBoxCN->setCurrentIndex(0);
    }
    comboBoxCN->setCurrentIndex(comboBoxCN->findData(1011));
    comboBoxCN->setMaxVisibleItems(20);
    comboBoxCN->setFixedWidth(416);

    labelFlag = new UserLabel(tr("帧标志位"));
    labelFlag->setFixedWidth(64);
    if(Platform==SERVER) {
        comboBoxFlag = new UserComboBox(UserComboBox::SERVER_FLAG,version);
        comboBoxFlag->setCurrentIndex(1);
    } else if(Platform==CLIENT) {
        comboBoxFlag = new UserComboBox(UserComboBox::CLIENT_FLAG,version);
        comboBoxFlag->setCurrentIndex(0);
    }
    comboBoxFlag->setFixedWidth(232);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(labelMN,0,0,1,1);
    mainLayout->addWidget(lineEditMN,0,1,1,1);
    mainLayout->addWidget(labelPW,0,2,1,1);
    mainLayout->addWidget(lineEditPW,0,3,1,1);
    mainLayout->addWidget(labelST,0,4,1,1);
    mainLayout->addWidget(comboBoxST,0,5,1,1);
    mainLayout->addWidget(labelCN,1,0,1,1);
    mainLayout->addWidget(comboBoxCN,1,1,1,3);
    mainLayout->addWidget(labelFlag,1,4,1,1);
    mainLayout->addWidget(comboBoxFlag,1,5,1,1);
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);

    connect(lineEditMN,SIGNAL(textChanged(const QString)),this,SLOT(lineEditMNTextChangedHandle(const QString)));
    connect(lineEditPW,SIGNAL(textChanged(const QString)),this,SLOT(lineEditPWTextChangedHandle(const QString)));
    connect(comboBoxST,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxSTIndexChangedHandle()));
    connect(comboBoxCN,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxCNIndexChangedHandle()));
    connect(comboBoxFlag,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxFlagIndexChangedHandle()));

    FieldMN = lineEditMN->text();
    FieldPW = lineEditPW->text();
    FieldST = comboBoxST->currentData().toString();
    FieldCN = comboBoxCN->currentData().toInt();
    FieldFlag = comboBoxFlag->currentData().toInt();
}

UserPacketFieldEdit::~UserPacketFieldEdit()
{

}

void UserPacketFieldEdit::lineEditMNTextChangedHandle(const QString &text)
{
    FieldMN = text;
    emit filedChanged(0);
}

void UserPacketFieldEdit::lineEditPWTextChangedHandle(const QString &text)
{
    FieldPW = text;
    emit filedChanged(1);
}

void UserPacketFieldEdit::comboBoxSTIndexChangedHandle()
{
    FieldST = comboBoxST->currentData().toString();
    emit filedChanged(2);
}

void UserPacketFieldEdit::comboBoxCNIndexChangedHandle()
{
    FieldCN = comboBoxCN->currentData().toInt();
    emit filedChanged(3);
}

void UserPacketFieldEdit::comboBoxFlagIndexChangedHandle()
{
    FieldFlag = comboBoxFlag->currentData().toInt();
    emit filedChanged(4);
}

void UserPacketFieldEdit::setVersion(int version)
{
    lineEditMN->setVersion(version);
    lineEditPW->setVersion(version);
    if(Platform==SERVER) {
        comboBoxST->setItems(UserComboBox::SERVER_ST,version);
        comboBoxCN->setItems(UserComboBox::SERVER_CN,version);
        comboBoxFlag->setItems(UserComboBox::SERVER_FLAG,version);
        if(version==0) {
            comboBoxST->setCurrentIndex(7);
            comboBoxCN->setCurrentIndex(1);
            comboBoxFlag->setCurrentIndex(1);
        } else if(version==1){
            comboBoxST->setCurrentIndex(7);
            comboBoxCN->setCurrentIndex(1);
            comboBoxFlag->setCurrentIndex(1);
        }
    } else if(Platform==CLIENT) {
        comboBoxST->setItems(UserComboBox::CLIENT_ST,version);
        comboBoxCN->setItems(UserComboBox::CLIENT_CN,version);
        comboBoxFlag->setItems(UserComboBox::CLIENT_FLAG,version);
        if(version==0) {
            comboBoxST->setCurrentIndex(7);
            comboBoxCN->setCurrentIndex(0);
            comboBoxFlag->setCurrentIndex(0);
        } else if(version==1){
            comboBoxST->setCurrentIndex(7);
            comboBoxCN->setCurrentIndex(0);
            comboBoxFlag->setCurrentIndex(0);
        }
    }
}

void UserPacketFieldEdit::setFiledST(const QString &st)
{
    comboBoxST->setCurrentIndex(comboBoxST->findData(st));
}

