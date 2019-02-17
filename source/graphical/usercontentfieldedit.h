#ifndef USERCONTENTFIELDEDIT_H
#define USERCONTENTFIELDEDIT_H

#include <QWidget>
#include "userlabel.h"
#include "userlineedit.h"
#include "usercombobox.h"
#include "usertimeedit.h"
#include "userbutton.h"
#include "userdatetimeedit.h"

class UserContentFieldEdit : public QWidget
{
    Q_OBJECT
public:
    explicit UserContentFieldEdit(int version = 1,QWidget *parent = 0);
    ~UserContentFieldEdit();
	int overTime() {return OverTime;}
    int reCount() {return ReCount;}
    int realCycle() {return RealCycle;}
    int minuteCycle() {return MinCycle;}
    QString password() {return Password;}
    QDateTime systemTime() {return SystemTime;}
    QDateTime startTime() {return StartTime;}
    QDateTime stopTime() {return StopTime;}
    QString analyzer() {return Analyzer;}
    QTime samplingStart() {return SamplingStart;}
    int samplingCycle() {return SamplingCycle;}
    QString information() {return Information;}
    void setEnabled(int cn);
    void setVersion(int version);
    void setDeviceST(const QString &st);
    void setAnalyzerList(int version,const QString &st);
signals:
    void filedChanged(int num);
public slots:

private:
    UserLabel *labelOverTime; //超时时间
    UserComboBox *comboBoxOverTime;
    UserLabel *labelReCount; //重发次数
    UserComboBox *comboBoxReCount;
    UserLabel *labelRealCycle; //实时数据周期
    UserComboBox *comboBoxRealCycle;
    UserLabel *labelMinCycle; //分钟数据周期
    UserComboBox *comboBoxMinCycle;
    UserLabel *labelPassword; //新设备密码
    UserLineEdit *lineEditPassword;
    UserButton *buttonSystemTime; //系统时间
    UserDateTimeEdit *dateTimeEditSystemTime;
    UserLabel *labelStartTime; //历史数据请求起始时间
    UserDateTimeEdit *dateTimeEditStartTime;
    UserLabel *labelStopTime; //历史数据请求停止时间
    UserDateTimeEdit *dateTimeEditStopTime;
    UserLabel *labelAnalyzer; //在线监控监测仪器仪表
    UserComboBox *comboBoxAnalyzer;
    UserLabel *labelSamplingStart; //采样起始时间
    UserTimeEdit *timeEditSamplingStart;
    UserLabel *labelSamplingCycle; //采样周期
    UserComboBox *comboBoxSamplingCycle;
    UserLabel *labelInformation; //设备信息编码
    UserComboBox *comboBoxInformation;
	
    int Version;
    QString DeviceST;

	int OverTime;
    int ReCount;
    int RealCycle;
    int MinCycle;
    QString Password;
    QDateTime SystemTime;
    QDateTime StartTime;
    QDateTime StopTime;
    QString Analyzer;
    QTime SamplingStart;
    int SamplingCycle;
    QString Information;
private slots:
    void comboBoxOverTimeIndexChangedHandle();
    void comboBoxReCountIndexChangedHandle();
    void comboBoxRealCycleIndexChangedHandle();
    void comboBoxMinCycleIndexChangedHandle();
    void lineEditPasswordTextChangedHandle(const QString &text);
    void buttonSystemTimeClickedHandle();
    void dateTimeEditSystemTimeChangedHandle(const QDateTime &datetime);
    void dateTimeEditStartTimeChangedHandle(const QDateTime &datetime);
    void dateTimeEditStopTimeChangedHandle(const QDateTime &datetime);
    void comboBoxAnalyzerIndexChangedHandle();
    void timeEditSamplingStartChangedHandle(const QTime &time);
    void comboBoxSamplingCycleChangedHandle();
    void comboBoxInformationChangedHandle();
};

#endif // USERCONTENTFIELDEDIT_H
