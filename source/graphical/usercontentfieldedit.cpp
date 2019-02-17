#include "usercontentfieldedit.h"
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>

UserContentFieldEdit::UserContentFieldEdit(int version,QWidget *parent) : QWidget(parent)
{
    Version = version;
    DeviceST = "32";

    labelOverTime = new UserLabel(tr("超时时间"));
    labelOverTime->setFixedWidth(64);
    comboBoxOverTime = new UserComboBox(UserComboBox::DEVICE_OVERTIME,Version);
    comboBoxOverTime->setFixedWidth(64);
    comboBoxOverTime->setCurrentIndex(1);
    comboBoxOverTime->setEnabled(false);

    labelReCount = new UserLabel(tr("重发次数"));
    labelReCount->setFixedWidth(64);
    comboBoxReCount = new UserComboBox(UserComboBox::DEVICE_RECOUNT,Version);
    comboBoxReCount->setFixedWidth(48);
    comboBoxReCount->setCurrentIndex(2);
    comboBoxReCount->setEnabled(false);

    labelRealCycle = new UserLabel(tr("实时数据周期"));
    labelRealCycle->setFixedWidth(96);
    comboBoxRealCycle = new UserComboBox(UserComboBox::DEVICE_REALCYCLE,Version);
    comboBoxRealCycle->setFixedWidth(96);
    comboBoxRealCycle->setCurrentIndex(1);
    comboBoxRealCycle->setEnabled(false);

    labelMinCycle = new UserLabel(tr("分钟数据周期"));
    labelMinCycle->setFixedWidth(96);
    comboBoxMinCycle = new UserComboBox(UserComboBox::DEVICE_MINCYCLE,Version);
    comboBoxMinCycle->setFixedWidth(80);
    comboBoxMinCycle->setCurrentIndex(6);
    comboBoxMinCycle->setEnabled(false);

    labelPassword = new UserLabel(tr("设备新密码"));
    labelPassword->setFixedWidth(80);
    lineEditPassword = new UserLineEdit(UserLineEdit::PW,Version);
    lineEditPassword->setFixedWidth(64);
    lineEditPassword->setEnabled(false);

    QHBoxLayout *row0Layout = new QHBoxLayout();
    row0Layout->addWidget(labelOverTime);
    row0Layout->addWidget(comboBoxOverTime);
    row0Layout->addWidget(labelReCount);
    row0Layout->addWidget(comboBoxReCount);
    row0Layout->addWidget(labelRealCycle);
    row0Layout->addWidget(comboBoxRealCycle);
    row0Layout->addWidget(labelMinCycle);
    row0Layout->addWidget(comboBoxMinCycle);
    row0Layout->addWidget(labelPassword);
    row0Layout->addWidget(lineEditPassword);

    buttonSystemTime = new UserButton(tr("系统时间"));
    buttonSystemTime->setFlat(true);
    buttonSystemTime->setFixedWidth(64);
    buttonSystemTime->setEnabled(false);
    dateTimeEditSystemTime = new UserDateTimeEdit();
    dateTimeEditSystemTime->setFixedWidth(192);
    dateTimeEditSystemTime->setEnabled(false);

    labelStartTime = new UserLabel(tr("起始时间"));
    labelStartTime->setFixedWidth(64);
    dateTimeEditStartTime = new UserDateTimeEdit();
    dateTimeEditStartTime->setFixedWidth(192);
    dateTimeEditStartTime->setEnabled(false);

    labelStopTime = new UserLabel(tr("停止时间"));
    labelStopTime->setFixedWidth(64);
    dateTimeEditStopTime = new UserDateTimeEdit();
    dateTimeEditStopTime->setFixedWidth(192);
    dateTimeEditStopTime->setEnabled(false);

    QHBoxLayout *row1Layout = new QHBoxLayout();
    row1Layout->addWidget(buttonSystemTime);
    row1Layout->addWidget(dateTimeEditSystemTime);
    row1Layout->addWidget(labelStartTime);
    row1Layout->addWidget(dateTimeEditStartTime);
    row1Layout->addWidget(labelStopTime);
    row1Layout->addWidget(dateTimeEditStopTime);

    labelAnalyzer = new UserLabel(tr("污染物分析仪"));
    labelAnalyzer->setFixedWidth(94);
    comboBoxAnalyzer = new UserComboBox(UserComboBox::DEVICE_POLLUTANT,Version,DeviceST);
    comboBoxAnalyzer->setMaxVisibleItems(20);
    comboBoxAnalyzer->setCurrentIndex(0);
    comboBoxAnalyzer->setFixedWidth(320);
    comboBoxAnalyzer->setEnabled(false);

    labelSamplingStart = new UserLabel(tr("采样起始时间"));
    labelSamplingStart->setFixedWidth(94);
    timeEditSamplingStart = new UserTimeEdit(QTime(0,0,0));
    timeEditSamplingStart->setFixedWidth(96);
    timeEditSamplingStart->setEnabled(false);

    labelSamplingCycle = new UserLabel(tr("采样周期"));
    labelSamplingCycle->setFixedWidth(64);
    comboBoxSamplingCycle = new UserComboBox(UserComboBox::DEVICE_SAMPLING_CYCLE,Version);
    comboBoxSamplingCycle->setCurrentIndex(1);
    comboBoxSamplingCycle->setFixedWidth(64);
    comboBoxSamplingCycle->setEnabled(false);

    QHBoxLayout *row2Layout = new QHBoxLayout();
    row2Layout->addWidget(labelAnalyzer);
    row2Layout->addWidget(comboBoxAnalyzer);
    row2Layout->addSpacing(36);
    row2Layout->addWidget(labelSamplingStart);
    row2Layout->addWidget(timeEditSamplingStart);
    row2Layout->addWidget(labelSamplingCycle);
    row2Layout->addWidget(comboBoxSamplingCycle);

    labelInformation = new UserLabel(tr("设备信息编码"));
    labelInformation->setFixedWidth(94);
    comboBoxInformation = new UserComboBox(UserComboBox::DEVICE_INFORMATION,Version);
    comboBoxInformation->setCurrentIndex(0);
    comboBoxInformation->setFixedWidth(320);
    comboBoxInformation->setEnabled(false);

    QHBoxLayout *row3Layout = new QHBoxLayout();
    row3Layout->addWidget(labelInformation);
    row3Layout->addWidget(comboBoxInformation);
    row3Layout->addSpacing(370);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(row0Layout);
    mainLayout->addLayout(row1Layout);
    mainLayout->addLayout(row2Layout);
    mainLayout->addLayout(row3Layout);
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);

    connect(comboBoxOverTime,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxOverTimeIndexChangedHandle()));
    connect(comboBoxReCount,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxReCountIndexChangedHandle()));
    connect(comboBoxRealCycle,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxRealCycleIndexChangedHandle()));
    connect(comboBoxMinCycle,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxMinCycleIndexChangedHandle()));
    connect(lineEditPassword,SIGNAL(textChanged(const QString)),this,SLOT(lineEditPasswordTextChangedHandle(const QString)));
    connect(buttonSystemTime,SIGNAL(clicked()),this,SLOT(buttonSystemTimeClickedHandle()));
    connect(dateTimeEditSystemTime,SIGNAL(dateTimeChanged(const QDateTime)),this,SLOT(dateTimeEditSystemTimeChangedHandle(const QDateTime)));
    connect(dateTimeEditStartTime,SIGNAL(dateTimeChanged(const QDateTime)),this,SLOT(dateTimeEditStartTimeChangedHandle(const QDateTime)));
    connect(dateTimeEditStopTime,SIGNAL(dateTimeChanged(const QDateTime)),this,SLOT(dateTimeEditStopTimeChangedHandle(const QDateTime)));
    connect(comboBoxAnalyzer,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxAnalyzerIndexChangedHandle()));
    connect(timeEditSamplingStart,SIGNAL(timeChanged(const QTime)),this,SLOT(timeEditSamplingStartChangedHandle(const QTime)));
    connect(comboBoxSamplingCycle,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxSamplingCycleChangedHandle()));

    OverTime = comboBoxOverTime->currentData().toInt();
    ReCount = comboBoxReCount->currentData().toInt();
    RealCycle = comboBoxRealCycle->currentData().toInt();
    MinCycle = comboBoxMinCycle->currentData().toInt();
    Password = lineEditPassword->text();
    StartTime = dateTimeEditStartTime->dateTime();
    StopTime = dateTimeEditStopTime->dateTime();
    Analyzer = comboBoxAnalyzer->currentData().toString();
    SamplingStart = timeEditSamplingStart->time();
    SamplingCycle = comboBoxSamplingCycle->currentData().toInt();
    Information = comboBoxInformation->currentData().toString();
}

UserContentFieldEdit::~UserContentFieldEdit()
{

}

void UserContentFieldEdit::comboBoxOverTimeIndexChangedHandle()
{
    OverTime = comboBoxOverTime->currentData().toInt();
    emit filedChanged(0);
}

void UserContentFieldEdit::comboBoxReCountIndexChangedHandle()
{
    ReCount = comboBoxReCount->currentData().toInt();
    emit filedChanged(1);
}

void UserContentFieldEdit::comboBoxRealCycleIndexChangedHandle()
{
    RealCycle = comboBoxRealCycle->currentData().toInt();
    emit filedChanged(2);
}

void UserContentFieldEdit::comboBoxMinCycleIndexChangedHandle()
{
    MinCycle = comboBoxMinCycle->currentData().toInt();
    emit filedChanged(3);
}

void UserContentFieldEdit::lineEditPasswordTextChangedHandle(const QString &text)
{
    Password = text;
    emit filedChanged(4);
}

void UserContentFieldEdit::buttonSystemTimeClickedHandle()
{
    QDateTime datetime = QDateTime::currentDateTime();
    dateTimeEditSystemTime->setDateTime(datetime);
}

void UserContentFieldEdit::dateTimeEditSystemTimeChangedHandle(const QDateTime &datetime)
{
    SystemTime = datetime;
    emit filedChanged(5);
}

void UserContentFieldEdit::dateTimeEditStartTimeChangedHandle(const QDateTime &datetime)
{
    StartTime = datetime;
    emit filedChanged(6);
}

void UserContentFieldEdit::dateTimeEditStopTimeChangedHandle(const QDateTime &datetime)
{
    StopTime = datetime;
    emit filedChanged(7);
}

void UserContentFieldEdit::comboBoxAnalyzerIndexChangedHandle()
{
    Analyzer = comboBoxAnalyzer->currentData().toString();
    emit filedChanged(8);
}

void UserContentFieldEdit::timeEditSamplingStartChangedHandle(const QTime &time)
{
    SamplingStart = time;
    emit filedChanged(9);
}

void UserContentFieldEdit::comboBoxSamplingCycleChangedHandle()
{
    SamplingCycle = comboBoxSamplingCycle->currentData().toInt();
    emit filedChanged(10);
}

void UserContentFieldEdit::comboBoxInformationChangedHandle()
{
    Information = comboBoxInformation->currentData().toString();
    emit filedChanged(11);
}

void UserContentFieldEdit::setEnabled(int cn)
{
    comboBoxOverTime->setEnabled(false);
    comboBoxReCount->setEnabled(false);
    comboBoxRealCycle->setEnabled(false);
    comboBoxMinCycle->setEnabled(false);
    lineEditPassword->setEnabled(false);
    buttonSystemTime->setEnabled(false);
    dateTimeEditSystemTime->setEnabled(false);
    dateTimeEditStartTime->setEnabled(false);
    dateTimeEditStopTime->setEnabled(false);
    comboBoxAnalyzer->setEnabled(false);
    timeEditSamplingStart->setEnabled(false);
    comboBoxSamplingCycle->setEnabled(false);
    comboBoxInformation->setEnabled(false);
    if(Version==0) {
        if(cn==1000) {
            comboBoxOverTime->setEnabled(true);
            comboBoxReCount->setEnabled(true);
        } else if(cn==1012) {
            buttonSystemTime->setEnabled(true);
            dateTimeEditSystemTime->setEnabled(true);
        } else if(cn==1062) {
            comboBoxRealCycle->setEnabled(true);
        } else if(cn==1072) {
            lineEditPassword->setEnabled(true);
        } else if(cn==2031 || cn==2041 || cn==2051 || cn==2061 || cn==2071) {
            dateTimeEditStartTime->setEnabled(true);
            dateTimeEditStopTime->setEnabled(true);
        } else if(cn>=3011 && cn<=3014) {
            comboBoxAnalyzer->setEnabled(true);
        }
    } else if(Version==1) {
        if(cn==1000) {
            comboBoxOverTime->setEnabled(true);
            comboBoxReCount->setEnabled(true);
        } else if(cn==1012) {
            buttonSystemTime->setEnabled(true);
            dateTimeEditSystemTime->setEnabled(true);
        } else if(cn==1062) {
            comboBoxRealCycle->setEnabled(true);
        } else if(cn==1064) {
            comboBoxMinCycle->setEnabled(true);
        } else if(cn==1072) {
            lineEditPassword->setEnabled(true);
        } else if(cn==2031 || cn==2041 || cn==2051 || cn==2061) {
            dateTimeEditStartTime->setEnabled(true);
            dateTimeEditStopTime->setEnabled(true);
        } else if(cn>=3011 && cn<=3017) {
            comboBoxAnalyzer->setEnabled(true);
        } else if(cn==3018) {
            comboBoxAnalyzer->setEnabled(true);
            timeEditSamplingStart->setEnabled(true);
            comboBoxSamplingCycle->setEnabled(true);
        } else if(cn>=3019 && cn<=3021) {
            comboBoxAnalyzer->setEnabled(true);
        } else if(cn==3022) {
            comboBoxAnalyzer->setEnabled(true);
            comboBoxInformation->setEnabled(true);
            dateTimeEditStartTime->setEnabled(true);
            dateTimeEditStopTime->setEnabled(true);
        }
    }
}

void UserContentFieldEdit::setVersion(int version)
{
    Version = version;
    comboBoxOverTime->setItems(UserComboBox::DEVICE_OVERTIME,Version);
    comboBoxReCount->setItems(UserComboBox::DEVICE_RECOUNT,Version);
    comboBoxRealCycle->setItems(UserComboBox::DEVICE_REALCYCLE,Version);
    comboBoxMinCycle->setItems(UserComboBox::DEVICE_MINCYCLE,Version);
    lineEditPassword->setVersion(version);
    comboBoxAnalyzer->setItems(UserComboBox::DEVICE_POLLUTANT,Version,DeviceST);
    comboBoxSamplingCycle->setItems(UserComboBox::DEVICE_SAMPLING_CYCLE,Version);
    comboBoxInformation->setItems(UserComboBox::DEVICE_INFORMATION,Version);
    if(Version==0) {
        comboBoxOverTime->setCurrentIndex(1);
        comboBoxReCount->setCurrentIndex(2);
        comboBoxRealCycle->setCurrentIndex(1);
        comboBoxMinCycle->setCurrentIndex(6);
        comboBoxAnalyzer->setCurrentIndex(0);
        comboBoxSamplingCycle->setCurrentIndex(1);
        comboBoxInformation->setCurrentIndex(0);
    } else if(Version==1) {
        comboBoxOverTime->setCurrentIndex(1);
        comboBoxReCount->setCurrentIndex(2);
        comboBoxRealCycle->setCurrentIndex(1);
        comboBoxMinCycle->setCurrentIndex(6);
        comboBoxAnalyzer->setCurrentIndex(0);
        comboBoxSamplingCycle->setCurrentIndex(1);
        comboBoxInformation->setCurrentIndex(0);
    }
}

void UserContentFieldEdit::setDeviceST(const QString &st)
{
    DeviceST = st;
    comboBoxAnalyzer->setItems(UserComboBox::DEVICE_POLLUTANT,Version,DeviceST);
    comboBoxAnalyzer->setCurrentIndex(0);
}
