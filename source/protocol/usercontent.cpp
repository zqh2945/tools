#include "usercontent.h"
#include <QDebug>

UserContent::UserContent(enum Direction dir,QObject *parent) : QObject(parent)
{
    DeviceDir = dir;
    Device = NULL;

    DeviceMN = "00000000000152316J000000";
    DevicePW = "100000";
    DeviceST = "32";
    Version = 1;

	Request = 1;
	Result = 1;

    OverTime = 5;
    ReCount = 3;
    RealCycle = 60;
    MinuteCycle = 10;
    Password = "100000";
    SystemTime = QDateTime::currentDateTime();
	StartTime = QDateTime::currentDateTime();
    StopTime = QDateTime::currentDateTime();
    DataTime = QDateTime::currentDateTime();
	Analyzer = "w00000";
    SamplingBaseTime.setHMS(0,0,0);
    SamplingCycle = 2;
    SamplingStopCycle = 40;
    Identifier = "010000A8900016F000169DC1";
    InfoCode = "i21001";
    Information = "//运行正常//";
}

UserContent::UserContent(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent) : QObject(parent)
{
    DeviceDir = dir;
    Device = NULL;

    DeviceMN = mn;
    DeviceST = st;
    DevicePW = pw;
    Version = version;

    Request = 1;
    Result = 1;

    OverTime = 5;
    ReCount = 3;
    RealCycle = 60;
    MinuteCycle = 10;
    Password = "100000";
    SystemTime = QDateTime::currentDateTime();
    StartTime = QDateTime::currentDateTime();
    StopTime = QDateTime::currentDateTime();
    DataTime = QDateTime::currentDateTime();
    Analyzer = "w00000";
    SamplingBaseTime.setHMS(0,0,0);
    SamplingCycle = 2;
    SamplingStopCycle = 40;
    Identifier = "010000A8900016F000169DC1";
    InfoCode = "i21001";
    Information = "//运行正常//";
}

UserContent::~UserContent()
{

}

//报文内容解包
bool UserContent::contentUnpack(const QString &content,int cn)
{
    bool ok = false;
    if(DeviceDir==Upper) {
        switch(cn) {
            case 1011 : ok = timeSetAndQueryUnpack(content); break;
            case 1013 : ok = emptyContentUnpack(content); break;
            case 1061 : ok = realCycleSetAndQueryUnpack(content); break;
            case 1063 : ok = minCycleSetAndQueryUnpack(content); break;
            case 2011 : ok = realDataUploadUnpack(content); break;
            case 2021 : ok = manageFacilityStatusUploadUnpack(content); break;
            case 2031 : ok = dayDataUploadUnpack(content); break;
            case 2041 : ok = manageFacilityTimeUploadUnpack(content); break;
            case 2051 : ok = minuteDataUploadUnpack(content); break;
            case 2061 : ok = hourDataUploadUnpack(content); break;
            case 2081 : ok = restartTimeUploadUnpack(content); break;
            case 3019 : ok = analyzerSamplingCycleUnpack(content); break;
            case 3020 : ok = analyzerSamplingStopTimeRespondUnpack(content); break;
            case 3021 : ok = analyzerIdentifierUploadUnpack(content); break;
            case 3022 : ok = informationUploadUnpack(content); break;
            case 9011 : ok = requestRespondUnpack(content); break;
            case 9012 : ok = resultRespondUnpack(content); break;
        }
    } else if(DeviceDir==Lower) {
        switch(cn) {
            case 1000 : ok = overTimeAndReCountSetUnpack(content); break;
            case 1011 : ok = emptyContentUnpack(content); break;
            case 1012 : ok = timeSetAndQueryUnpack(content); break;
            case 1013 : ok = timeCalibrationRespondUnpack(content); break;
            case 1061 : ok = emptyContentUnpack(content); break;
            case 1062 : ok = realCycleSetAndQueryUnpack(content); break;
            case 1063 : ok = emptyContentUnpack(content); break;
            case 1064 : ok = minCycleSetAndQueryUnpack(content); break;
            case 1072 : ok = passwordSetUnpack(content); break;
            case 2011 : ok = emptyContentUnpack(content); break;
            case 2012 : ok = emptyContentUnpack(content); break;
            case 2021 : ok = emptyContentUnpack(content); break;
            case 2022 : ok = emptyContentUnpack(content); break;
            case 2031 : ok = historyRequestUnpack(content); break;
            case 2041 : ok = historyRequestUnpack(content); break;
            case 2051 : ok = historyRequestUnpack(content); break;
            case 2061 : ok = historyRequestUnpack(content); break;
            case 3011 : ok = analyzerRequestUnpack(content); break;
            case 3012 : ok = analyzerRequestUnpack(content); break;
            case 3013 : ok = analyzerRequestUnpack(content); break;
            case 3014 : ok = analyzerRequestUnpack(content); break;
            case 3015 : ok = analyzerRequestUnpack(content); break;
            case 3016 : ok = analyzerRequestUnpack(content); break;
            case 3017 : ok = analyzerTimeCalibrationRequestUnpack(content); break;
            case 3018 : ok = analyzerSamplingCycleUnpack(content); break;
            case 3019 : ok = analyzerRequestUnpack(content); break;
            case 3020 : ok = analyzerRequestUnpack(content); break;
            case 3021 : ok = analyzerRequestUnpack(content); break;
            case 3022 : ok = informationRequestUnpack(content); break;
            case 9014 : ok = emptyContentUnpack(content); break;
        }
    }
    return ok;
}

//报文内容打包
QString UserContent::contentPack(int cn)
{
    QString content;
    content.clear();
    if(DeviceDir==Upper) {
        switch(cn) {
            case 1000 : content = overTimeAndReCountSetPack(); break;
            case 1011 : content = emptyContentPack(); break;
            case 1012 : content = timeSetAndQueryPack(); break;
            case 1013 : content = timeCalibrationRespondPack(); break;
            case 1061 : content = emptyContentPack(); break;
            case 1062 : content = realCycleSetQndQueryPack(); break;
            case 1063 : content = emptyContentPack(); break;
            case 1064 : content = minCycleSetAndQueryPack(); break;
            case 1072 : content = passwordSetPack(); break;
            case 2011 : content = emptyContentPack(); break;
            case 2012 : content = emptyContentPack(); break;
            case 2021 : content = emptyContentPack(); break;
            case 2022 : content = emptyContentPack(); break;
            case 2031 : content = historyRequestPack(); break;
            case 2041 : content = historyRequestPack(); break;
            case 2051 : content = historyRequestPack(); break;
            case 2061 : content = historyRequestPack(); break;
            case 3011 : content = analyzerRequestPack(); break;
            case 3012 : content = analyzerRequestPack(); break;
            case 3013 : content = analyzerRequestPack(); break;
            case 3014 : content = analyzerRequestPack(); break;
            case 3015 : content = analyzerRequestPack(); break;
            case 3016 : content = analyzerRequestPack(); break;
            case 3017 : content = analyzerTimeCalibrationRequestPack(); break;
            case 3018 : content = analyzerSamplingCyclePack(); break;
            case 3019 : content = analyzerRequestPack(); break;
            case 3020 : content = analyzerRequestPack(); break;
            case 3021 : content = analyzerRequestPack(); break;
            case 3022 : content = informationRequestPack(); break;
            case 9014 : content = emptyContentPack(); break;
        }
    } else if(DeviceDir==Lower) {
        switch(cn) {
            case 1011 : content = timeSetAndQueryPack(); break;
            case 1013 : content = emptyContentPack(); break;
            case 1061 : content = realCycleSetQndQueryPack(); break;
            case 1063 : content = minCycleSetAndQueryPack(); break;
            case 2011 : content = realDataUploadPack(); break;
            case 2021 : content = manageFacilityStatusUploadPack(); break;
            case 2031 : content = dayDataUploadPack(); break;
            case 2041 : content = manageFacilityTimeUploadPack(); break;
            case 2051 : content = minuteDataUploadPack(); break;
            case 2061 : content = hourDataUploadPack(); break;
            case 2081 : content = restartTimeUploadPack(); break;
            case 3019 : content = analyzerSamplingCyclePack(); break;
            case 3020 : content = analyzerSamplingStopTimeRespondPack(); break;
            case 3021 : content = analyzerIdentifierUploadPack(); break;
            case 3022 : content = informationUploadPack(); break;
            case 9011 : content = requestRespondPack(); break;
            case 9012 : content = resultRespondPack(); break;
        }
    }
    return content;
}
//字段解析
QString UserContent::fieldExtract(const QString &content,const QString &field,bool *ok)
{
    QString value;
    *ok = false;
    int length = field.length() + 1;
    int ps = content.indexOf(field+"=",0);
    int pe = content.indexOf(QRegExp("(;|,|&)"),ps+length);
    if((ps != -1) && (pe != -1)) {
        ps += length;
        value = content.mid(ps,pe-ps);
        *ok = true;
    }
    return value;
}
//日期时间字符串解析
QDateTime UserContent::datetimeExtract(const QString &datetime)
{
    int year = datetime.mid(0,4).toInt();
    int month = datetime.mid(4,2).toInt();
    int day = datetime.mid(6,2).toInt();
    int hour = datetime.mid(8,2).toInt();
    int minute = datetime.mid(10,2).toInt();
    int second = datetime.mid(12,2).toInt();
    QDate date(year,month,day);
    QTime time(hour,minute,second);
    return QDateTime(date,time);
}
//时间字符串解析
QTime UserContent::timeExtract(const QString &time)
{
    int hour = time.mid(0,2).toInt();
    int minute = time.mid(2,2).toInt();
    int second = time.mid(4,2).toInt();
    return QTime(hour,minute,second);
}

//请求响应解包(9011)
bool UserContent::requestRespondUnpack(const QString &content)
{
    int version,request;
    if(Device==NULL) {
        version = Version;
    } else {
        version = Device->version();
    }
    bool state = false;
    if(!content.isEmpty()) {
        if(version==0 || version==1) { //HJ/212-2005或HJ/212-2016标准
            bool ok;
            QString requestString = fieldExtract(content,"QnRtn",&ok);
            if(ok) {

                request = requestString.toInt();
                state = true;
            }
        }
    }
    if(Device==NULL) {
        Request = request;
    } else {
        Device->setRequest(request);
    }
    return state;
}
//请求响应打包(9011)
QString UserContent::requestRespondPack()
{
    int version,request;
    if(Device==NULL) {
        version = Version;
        request = Request;
    } else {
        version = Device->version();
        request = Device->request();
    }
    QString content;
    if(version==0 || version==1) { //HJ/212-2005或HJ/212-2016标准
        content = QString("QnRtn=%1").arg(request);
    }
    return content;
}
//执行结果解包(9012)
bool UserContent::resultRespondUnpack(const QString &content)
{
    int version,result;
    if(Device==NULL) {
        version = Version;
    } else {
        version = Device->version();
    }
    bool state = false;
    if(!content.isEmpty()) {
        if(version==0 || version==1) { //HJ/212-2005或HJ/212-2016标准
            bool ok;
            QString resultString = fieldExtract(content,"QnRtn",&ok);
            if(ok) {
                result = resultString.toInt();
                state = true;
            }
        }
    }
    if(Device==NULL) {
        Result = result;
    } else {
        Device->setResult(result);
    }
    return state;
}
//执行结果打包(9012)
QString UserContent::resultRespondPack()
{
    int version,result;
    if(Device==NULL) {
        version = Version;
        result = Result;
    } else {
        version = Device->version();
        result = Device->result();
    }
    QString content;
    if(version==0 || version==1) { //HJ/212-2005或HJ/212-2016标准
        content = QString("ExeRtn=%1").arg(result);
    }
    return content;
}

//空报文内容解包
bool UserContent::emptyContentUnpack(const QString &content)
{
    int result = -1;
    if(content.isEmpty()) {
        result = 0;
    } else {
        result = 3;
    }
    if(Device==NULL) {
        Result = result;
    } else {
        Device->setResult(result);
    }
    return true;
}
//空报文内容打包
QString UserContent::emptyContentPack()
{
    return QString("");
}

//超时时间及重发次数设置解包(1000)
bool UserContent::overTimeAndReCountSetUnpack(const QString &content)
{
    int version,result,overTime,reCount;
    if(Device==NULL) {
        version = Version;
    } else {
        version = Device->version();
    }
    bool state = false;
    if(!content.isEmpty()) {
        if(version==0 || version==1) { //HJ/212-2005或HJ/212-2016标准
            result = 0;
            bool ok;
            //超时时间解析
            if(Result==0) {
                QString overtime = fieldExtract(content,"OverTime",&ok);
                if(ok) {
                    overTime = overtime.toInt();
                } else {
                    result = 3;
                }
            }
            //重发次数解析
            if(result==0) {
                QString recount = fieldExtract(content,"ReCount",&ok);
                if(ok) {
                    reCount = recount.toInt();
                } else {
                    result = 3;
                }
            }
            state = true;
        }
    }
    if(Device==NULL) {
        Result = result;
        OverTime = overTime;
        ReCount = reCount;
    } else {
        Device->setResult(result);
        Device->setOverTime(overTime);
        Device->setReCount(reCount);
    }
    return state;
}
//超时时间及重发次数设置打包(1000)
QString UserContent::overTimeAndReCountSetPack()
{
    int version,overTime,reCount;
    if(Device==NULL) {
        version = Version;
        overTime = OverTime;
        reCount = ReCount;
    } else {
        version = Device->version();
        overTime = Device->overTime();
        reCount = Device->reCount();
    }
    QString content;
    if(version==0 || version==1) { //HJ/212-2005或HJ/212-2016标准
        content = QString("OverTime=%1;ReCount=%2").arg(overTime).arg(reCount);
    }
    return content;
}
//数采仪时间设置/查询解包(1012/1011)
bool UserContent::timeSetAndQueryUnpack(const QString &content)
{
    int version,result;
    QDateTime systemTime;
    if(Device==NULL) {
        version = Version;
    } else {
        version = Device->version();
    }
    bool state = false;
    if(!content.isEmpty()) {
        if(version==0 || version==1) { //HJ/212-2005或HJ/212-2016标准
            result = 0;
            bool ok;
            QString time = fieldExtract(content,"SystemTime",&ok);
            if(ok) {
                systemTime = datetimeExtract(time);
            } else {
                result = 3;
            }
            state = true;
        }
    }
    if(Device==NULL) {
        Result = result;
        SystemTime = systemTime;
    } else {
        Device->setResult(result);
        Device->setSystemTime(systemTime);
    }
    return state;
}
//数采仪时间设置/查询打包(1012/1011)
QString UserContent::timeSetAndQueryPack()
{
    QString content;
    if(Version==0 || Version==1) { //HJ/212-2005或HJ/212-2016标准
        QString timestamp = SystemTime.toString("yyyyMMddhhmmss");
        content = QString("SystemTime=%1").arg(timestamp);
    }
    return content;
}
//数采仪时间校准请求解包(1013)
bool UserContent::timeCalibrationRespondUnpack(const QString &content)
{
    bool state = false;
    if(!content.isEmpty()) {
        if(Version==1) { //HJ/212-2016标准
            Result = 0;
            bool ok;
            QString time = fieldExtract(content,"SystemTime",&ok);
            if(ok) {
                SystemTime = datetimeExtract(time);
            }
            state = true;
        }
    }
    return state;
}
//数采仪时间校准请求打包(1013)
QString UserContent::timeCalibrationRespondPack()
{
    QString content;
    if(Version==1) { //HJ/212-2016标准
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        content = QString("SystemTime=%1").arg(timestamp);
    }
    return content;
}
//实时数据上报时间间隔设置/查询解包(1062/1061)
bool UserContent::realCycleSetAndQueryUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        QString cycle = fieldExtract(content,"RtdInterval",&ok);
        if(ok) {
            RealCycle = cycle.toInt();
        } else {
            Result = 3;
        }
        return true;
    } else {
        return false;
    }
}
//实时数据上报时间间隔设置/查询打包(1062/1061)
QString UserContent::realCycleSetQndQueryPack()
{
	return QString("RtdInterval=%1").arg(RealCycle);
}
//分钟数据上报时间间隔设置/查询解包(1064/1063)
bool UserContent::minCycleSetAndQueryUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        QString cycle = fieldExtract(content,"MinInterval",&ok);
        if(ok) {
            RealCycle = cycle.toInt();
        } else {
            Result = 3;
        }
        return true;
    } else {
        return false;
    }
}
//分钟数据上报时间间隔设置/查询打包(1064/1063)
QString UserContent::minCycleSetAndQueryPack()
{
    return QString("MinInterval=%1").arg(MinuteCycle);
}
//数采仪密码设置解包(1072)
bool UserContent::passwordSetUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        QString cycle = fieldExtract(content,"NewPW",&ok);
        if(ok) {
            RealCycle = cycle.toInt();
        } else {
            Result = 3;
        }
        return true;
    } else {
        return false;
    }
}
//数采仪密码设置打包(1072)
QString UserContent::passwordSetPack()
{
    return QString("NewPW=%1").arg(Password);
}

//实时数据上报解包(2011)
bool UserContent::realDataUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //数据时间解析
        QString time = fieldExtract(content,"DataTime",&ok);
        if(ok) {
            DataTime = datetimeExtract(time);
        } else {
            Result = 3;
        }
        //
        if(Result==1) {

        }
        return true;
    } else {
        return false;
    }
}
//实时数据上报打包(2011)
QString UserContent::realDataUploadPack()
{
	QString content;
	content.clear();
    if(Device!=NULL) {
        QString timestamp = Device->realDataTime().toString("yyyyMMddhhmmss");
        content = QString("DataTime=%1").arg(timestamp);
        for(int i=0;i<Device->pollutantList().count();i++) {
            UserPollutant *pollutant = Device->pollutantList().at(i);
            content.append(QString("%1=%2").arg(pollutant->code()).arg(pollutant->realData()));
        }
    }
	return content;
}
//分钟数据上报解包(2051)
bool UserContent::minuteDataUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //数据时间解析
        QString time = fieldExtract(content,"DataTime",&ok);
        if(ok) {
            DataTime = datetimeExtract(time);
        } else {
            Result = 3;
        }
        //
        if(Result==1) {

        }
        return true;
    } else {
        return false;
    }
}
//分钟数据上报打包(2051)
QString UserContent::minuteDataUploadPack()
{
	QString content;
	content.clear();
	
	return content;
}
//小时数据上报解包(2061)
bool UserContent::hourDataUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //数据时间解析
        QString time = fieldExtract(content,"DataTime",&ok);
        if(ok) {
            DataTime = datetimeExtract(time);
        } else {
            Result = 3;
        }
        //
        if(Result==1) {

        }
        return true;
    } else {
        return false;
    }
}
//小时数据上报打包(2061)
QString UserContent::hourDataUploadPack()
{
	QString content;
	content.clear();
	
	return content;
}
//日数据上报解包(2031)
bool UserContent::dayDataUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //数据时间解析
        QString time = fieldExtract(content,"DataTime",&ok);
        if(ok) {
            DataTime = datetimeExtract(time);
        } else {
            Result = 3;
        }
        //
        if(Result==1) {

        }
        return true;
    } else {
        return false;
    }
}
//日数据上报打包(2031)
QString UserContent::dayDataUploadPack()
{
    QString content;
    content.clear();

    return content;
}
//污染治理设施运行状态上报解包(2021)
bool UserContent::manageFacilityStatusUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //数据时间解析
        QString time = fieldExtract(content,"DataTime",&ok);
        if(ok) {
            DataTime = datetimeExtract(time);
        } else {
            Result = 3;
        }
        //
        if(Result==1) {

        }
        return true;
    } else {
        return false;
    }
}
//污染治理设施运行状态上报打包(2021)
QString UserContent::manageFacilityStatusUploadPack()
{
	QString content;
	content.clear();
	
	return content;
}
//污染治理设施日运行时间解包(2041)
bool UserContent::manageFacilityTimeUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //数据时间解析
        QString time = fieldExtract(content,"DataTime",&ok);
        if(ok) {
            DataTime = datetimeExtract(time);
        } else {
            Result = 3;
        }
        //
        if(Result==1) {

        }
        return true;
    } else {
        return false;
    }
}
//污染治理设备日运行时间打包(2041)
QString UserContent::manageFacilityTimeUploadPack()
{
	QString content;
	content.clear();
	
	return content;
}

//历史数据请求解包(2031/2041/2051/2061)
bool UserContent::historyRequestUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //请求起始时间解析
        if(Result==1) {
            QString time = fieldExtract(content,"BeginTime",&ok);
            if(ok) {
                StartTime = datetimeExtract(time);
            } else {
                Result = 3;
            }
        }
        //请求结束时间解析
        if(Result==1) {
            QString time = fieldExtract(content,"EndTime",&ok);
            if(ok) {
                StopTime = datetimeExtract(time);
            } else {
                Result = 3;
            }
        }
        if(Result==1) {
            if(StartTime>StopTime) {Result = 3;}
        }
        return true;
    } else {
        return false;
    }
}
//历史数据请求打包(2031/2041/2051/2061)
QString UserContent::historyRequestPack()
{
	if(StartTime > QDateTime::currentDateTime()) {
        StartTime = QDateTime::currentDateTime();
    }
    if(StopTime > QDateTime::currentDateTime()) {
        StopTime = QDateTime::currentDateTime();
    }
    QString start = StartTime.toString("yyyyMMddhhmmss");
    QString stop = StopTime.toString("yyyyMMddhhmmss");
    return QString("BeginTime=%1;EndTime=%2").arg(start).arg(stop);
}

//数采仪开机时间上报解包(2081)
bool UserContent::restartTimeUploadUnpack(const QString &content)
{
    bool state = false;
    if(!content.isEmpty()) {
        if(Version==1) { //HJ/212-2016标准
            Result = 1;
            bool ok;
            //数据时间解析
            if(Result==1) {
                QString time = fieldExtract(content,"DataTime",&ok);
                if(ok) {
                    DataTime = datetimeExtract(time);
                } else {
                    Result = 3;
                }
            }
            //数采仪重启时间解析
            if(Result==1) {
                QString time = fieldExtract(content,"RestartTime",&ok);
                if(ok) {
                    PowerOnTime = datetimeExtract(time);
                } else {
                    Result = 3;
                }
            }
            if(Result==1) {
                if(PowerOnTime>DataTime) {Result = 3;}
            }
            state = true;
        }
    }
    return state;
}
//数采仪开机时间上报打包(2081)
QString UserContent::restartTimeUploadPack()
{
    QString content;
    if(Version==1) { //HJ/212-2016标准
        QString time = DataTime.toString("yyyyMMddhhmmss");
        QString restart = PowerOnTime.toString("yyyyMMddhhmmss");
        content = QString("DataTime=%1;RestartTime=%2").arg(time).arg(restart);
    }
    return content;
}

//在线监控（监测）仪器仪表控制指令请求解包
bool UserContent::analyzerRequestUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //在线监控（监测）仪器仪表编码解析
        if(Result==1) {
            Analyzer = fieldExtract(content,"PolId",&ok);
            if(!ok) {Result = 3;}
        }
        return true;
    } else {
        return false;
    }
}
//在线监控（监测）仪器仪表控制指令请求打包
QString UserContent::analyzerRequestPack()
{
    return QString("PolId=%1").arg(Analyzer);
}
//在线监控（监测）仪器仪表时间校准请求解包
bool UserContent::analyzerTimeCalibrationRequestUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //在线监控（监测）仪器仪表编码解析
        if(Result==1) {
            Analyzer = fieldExtract(content,"PolId",&ok);
            if(!ok) {Result = 3;}
        }
        //上位机时间解析
        if(Request==1) {
            QString time = fieldExtract(content,"SystemTime",&ok);
            if(ok) {
                SystemTime = datetimeExtract(time);
            } else {
                Result = 3;
            }
        }
        return true;
    } else {
        return false;
    }
}
//在线监控（监测）仪器仪表时间校准请求打包
QString UserContent::analyzerTimeCalibrationRequestPack()
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    return QString("PolId=%1;SystemTime=%2").arg(Analyzer).arg(timestamp);
}
//在线监控（监测）仪器仪表采样时间间隔解包
bool UserContent::analyzerSamplingCycleUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //在线监控（监测）仪器仪表编码解析
        if(Result==1) {
            Analyzer = fieldExtract(content,"PolId",&ok);
            if(!ok) {Result = 3;}
        }
        //在线监控（监测）仪器仪表采样起始时间
        if(Request==1) {
            QString time = fieldExtract(content,"CstartTime",&ok);
            if(ok) {

            } else {
                Result = 3;
            }
        }
        //在线监控（监测）仪器仪表采样时间间隔
        if(Request==1) {
            QString cycle = fieldExtract(content,"CTime",&ok);
            if(ok) {
                SamplingCycle = cycle.toInt();
            } else {
                Result = 3;
            }
        }
        return true;
    } else {
        return false;
    }
}
//在线监控（监测）仪器仪表采样时间间隔打包
QString UserContent::analyzerSamplingCyclePack()
{
    QString base = SamplingBaseTime.toString("hhmmss");
    return QString("PolId=%1;CstatTime=%2;CTime=%3").arg(Analyzer).arg(base).arg(SamplingCycle);
}
//在线监控（监测）仪器仪表出样时间间隔响应解包
bool UserContent::analyzerSamplingStopTimeRespondUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        Result = 1;
        bool ok;
        //在线监控（监测）仪器仪表编码解析
        if(Result==1) {
            Analyzer = fieldExtract(content,"PolId",&ok);
            if(!ok) {Result = 3;}
        }
        //在线监控（监测）仪器仪表采样起始时间
        if(Request==1) {
            QString time = fieldExtract(content,"CstartTime",&ok);
            if(ok) {
                SamplingBaseTime = timeExtract(time);
            } else {
                Result = 3;
            }
        }
        return true;
    } else {
        return false;
    }
}
//在线监控（监测）仪器仪表出样时间间隔响应打包
QString UserContent::analyzerSamplingStopTimeRespondPack()
{
    return QString("PolId=%1;STime=%2").arg(Analyzer).arg(SamplingStopCycle);
}
//在线监控（监测）仪器仪表设备唯一标识上报解包
bool UserContent::analyzerIdentifierUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        Result = 1;
        bool ok;
        //在线监控（监测）仪器仪表编码解析
        if(Result==1) {
            Analyzer = fieldExtract(content,"PolId",&ok);
            if(!ok) {Result = 3;}
        }
        //在线监控（监测）仪器仪表设备唯一标识解析
        if(Request==1) {
            QString field = QString("%1-SN").arg(Analyzer);
            Identifier = fieldExtract(content,field,&ok);
            if(!ok) {Result = 3;}
        }
        return true;
    } else {
        return false;
    }
}
//在线监控（监测）仪器仪表设备唯一标识上报打包
QString UserContent::analyzerIdentifierUploadPack()
{
    return QString("%1-SN=%2").arg(Analyzer).arg(Identifier);
}

//现场机信息请求解包
bool UserContent::informationRequestUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        InfoCode = fieldExtract(content,"InfoId",&ok);
        if(!ok) {Result = 3;}
        if(Result==1) {
            QString device = InfoCode.mid(1,1);
            QString infoType = InfoCode.mid(2,1);
            if(device=="1" && Result==1) {
                Analyzer = fieldExtract(content,"PolId",&ok);
                if(!ok) {Result = 3;}
            }
            if(infoType=="1" && Result==1) {
                QString start = fieldExtract(content,"BeginTime",&ok);
                if(!ok) {Result = 3;}
                if(Result==1) {
                    StartTime = datetimeExtract(start);
                }
            }
            if(infoType=="1" && Result==1) {
                QString stop = fieldExtract(content,"EndTime",&ok);
                if(!ok) {Result = 3;}
                if(Result==1) {
                    StopTime = datetimeExtract(stop);
                }
            }
            if(Result==1) {
                if(StartTime > StopTime) {Result = 3;}
                if(StartTime > QDateTime::currentDateTime()) {
                    StartTime = QDateTime::currentDateTime();
                }
                if(StopTime > QDateTime::currentDateTime()) {
                    StopTime = QDateTime::currentDateTime();
                }
            }

        }
        return true;
    } else {
        return false;
    }
}
//现场机信息请求打包
QString UserContent::informationRequestPack()
{
    QString content;
    QString device = InfoCode.mid(1,1);
    QString infoType = InfoCode.mid(2,1);
    content.clear();
    if(device=="1") {
        content.append(QString("PolId=%1;InfoId=%2").arg(Analyzer).arg(InfoCode));
    } else {
        content.append(QString("InfoId=%1").arg(InfoCode));
    }
    if(infoType=="1") {
        if(StartTime > QDateTime::currentDateTime()) {
            StartTime = QDateTime::currentDateTime();
        }
        if(StopTime > QDateTime::currentDateTime()) {
            StopTime = QDateTime::currentDateTime();
        }
        QString start = StartTime.toString("yyyyMMddhhmmss");
        QString stop = StopTime.toString("yyyyMMddhhmmss");
        content.append(QString(";BeginTime=%3;EndTime=%4").arg(start).arg(stop));
    }
    return content;
}
//现场机信息上报解包
bool UserContent::informationUploadUnpack(const QString &content)
{
    if(!content.isEmpty()) {
        Result = 1;
        bool ok;
        //数据时间解析
        if(Result==1) {
            QString time = fieldExtract(content,"DataTime",&ok);
            if(ok) {
                DataTime = datetimeExtract(time);
            } else {
                Result = 1;
            }
        }
        //在线监控（监测）仪器仪表编码解析
        if(Result==1) {
            Analyzer = fieldExtract(content,"PolId",&ok);
            if(ok) { //数采仪和辅助设备信息

            } else { //在线监控（监测）仪器仪表信息

            }
        }
        return true;
    } else {
        return false;
    }
}

//现场机信息上报打包
QString UserContent::informationUploadPack()
{
    QString content;
    QString device = InfoCode.mid(1,1);
    content.clear();
    content.append(QString("DataTime=%1").arg(DataTime.toString("yyyyMMddhhmmss")));
    if(device=="1") {
        content.append(QString(";PolId=%1").arg(Analyzer));
    }
    content.append(QString(";%1-Info=%2").arg(InfoCode).arg(Information));
    return content;
}
