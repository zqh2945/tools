#include "userdevice.h"
#include "../source/files/userserverdatabasefile.h"
#include "../source/files/userclientdatabasefile.h"
#include <QDebug>

UserDevice::UserDevice(enum Direction dir,QObject *parent) : QObject(parent)
{
    DeviceDir = dir;
    DeviceState = false;

    DeviceMN = "00000000000152316J000000";
    DevicePW = "100000";
    DeviceST = "32";
    Version = 1;
    OverTime = 5;
    ReCount = 3;
    RealCycle = 60;
    MinCycle = 10;
    RealUpload = true;
    MinUpload = true;
    HourUpload = true;
    Request = 0;
    Result = 0;
}

UserDevice::UserDevice(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent) : QObject(parent)
{
    DeviceDir = dir;
    DeviceState = false;

    DeviceMN = mn;
    DevicePW = pw;
    DeviceST = st;
    Version = version;
    OverTime = 5;
    ReCount = 3;
    RealCycle = 60;
    MinCycle = 10;
    RealUpload = true;
    MinUpload = true;
    HourUpload = true;
    Request = 0;
    Result = 0;
}

UserDevice::~UserDevice()
{
    DeviceState = false;
}
//
void UserDevice::initialization(const QString &ipaddr,int port,const QString &mn)
{
    if(DeviceDir==Upper) {
        //初始化监测点数采仪
        QStringList config = UserServerDatabaseFile::deviceConfig(ipaddr,port,mn);

        //初始化污染监测因子
        QList<QStringList> pollutantList = UserServerDatabaseFile::pollutantConfigList(ipaddr,port,mn);
        for(int i=0;i<pollutantList.count();i++) {
            QStringList pollutant = pollutantList.at(i);
            if(pollutant.count()>=5) {
                QString code = pollutant.at(0);
                QString name = pollutant.at(1);
                int type = pollutant.at(2).toInt();
                QString dUnit = pollutant.at(3);
                int dDot = pollutant.at(4).toInt();
                if(type>=3 && pollutant.count()>=7) {
                    QString qUnit = pollutant.at(5);
                    int qDot = pollutant.at(6).toInt();
                    PollutantList.append(new UserPollutant(code,name,type,dUnit,dDot,qUnit,qDot));
                } else {
                    PollutantList.append(new UserPollutant(code,name,type,dUnit,dDot));
                }
            }
        }
        //初始化污染治理设施
    }
}
//
void UserDevice::initialization(const QString &mn)
{
    if(DeviceDir==Lower) {
        //初始化监测点数采仪
        QStringList config = UserClientDatabaseFile::deviceConfig(mn);

        //初始化污染监测因子
        QList<QStringList> pollutantList = UserClientDatabaseFile::pollutantConfigList(mn);
        for(int i=0;i<pollutantList.count();i++) {
            QStringList pollutant = pollutantList.at(i);
            if(pollutant.count()>=5) {
                QString code = pollutant.at(0);
                QString name = pollutant.at(1);
                int type = pollutant.at(2).toInt();
                QString dUnit = pollutant.at(3);
                int dDot = pollutant.at(4).toInt();
                if(type>=3 && pollutant.count()>=7) {
                    QString qUnit = pollutant.at(5);
                    int qDot = pollutant.at(6).toInt();
                    PollutantList.append(new UserPollutant(code,name,type,dUnit,dDot,qUnit,qDot));
                } else {
                    PollutantList.append(new UserPollutant(code,name,type,dUnit,dDot));
                }
            }
        }
        //初始化污染治理设施
    }
}
//数采仪开机
void UserDevice::start()
{
    DeviceState = true;
}
//数采仪关机
void UserDevice::stop()
{
    DeviceState = false;
}
//数采仪状态
bool UserDevice::state()
{
    return DeviceState;
}
//数采仪接收消息
void UserDevice::receiveMessage(const QString &msg)
{
    if(DeviceDir==Upper) {
        emit protocolUnpack(msg);
        //请求指令执行
        qDebug() << __FUNCTION__ << Command << Result;
        if(Result==0) {
            if(ReceiveCommandHandle()) {
                QString frame;
                emit protocolPack(&frame,Command,false,false);
                if(!frame.isEmpty()) {emit sendMsg(frame);}
            }
        } else {
            emit runningLog(QString("接收帧错误，ErrorCode=%1").arg(Result));
        }
    }
}
//数采仪接收消息
void UserDevice::receiveMessage(const QString &id,const QString &msg)
{
    if(DeviceDir==Lower) {
        emit protocolUnpack(msg);
        //发送请求响应
        if(Request>0) {
            QString frame;
            emit protocolPack(&frame,9011,false,false);
            if(!frame.isEmpty()) {emit sendMsg(id,frame);}
        }
        //请求指令执行
        if(Result==0) {
            if(ReceiveCommandHandle()) {
                QString frame;
                emit protocolPack(&frame,Command,false,false);
                if(!frame.isEmpty()) {emit sendMsg(id,frame);}
            }
        }
        //发送执行结果
        if(Result>0) {
            QString frame;
            emit protocolPack(&frame,9012,false,false);
            if(!frame.isEmpty()) {emit sendMsg(id,frame);}
        }
    }
}
//接收指令执行
bool UserDevice::ReceiveCommandHandle()
{
    bool ok = false;
    if(DeviceDir==Upper) {
        switch(Command) {
            case 1011 : /* ok = timeSetAndQueryUnpack(content); */ break;
            case 1013 : /* ok = emptyContentUnpack(content); */ break;
            case 1061 : /* ok = realCycleSetAndQueryUnpack(content); */ break;
            case 1063 : /* ok = minCycleSetAndQueryUnpack(content); */ break;
            case 2011 : /* ok = realDataUploadUnpack(content); */ break;
            case 2021 : /* ok = manageFacilityStatusUploadUnpack(content); */ break;
            case 2031 : /* ok = dayDataUploadUnpack(content); */ break;
            case 2041 : /* ok = manageFacilityTimeUploadUnpack(content); */ break;
            case 2051 : /* ok = minuteDataUploadUnpack(content); */ break;
            case 2061 : /* ok = hourDataUploadUnpack(content); */ break;
            case 2081 : /* ok = restartTimeUploadUnpack(content); */ break;
            case 3019 : /* ok = analyzerSamplingCycleUnpack(content); */ break;
            case 3020 : /* ok = analyzerSamplingStopTimeRespondUnpack(content); */ break;
            case 3021 : /* ok = analyzerIdentifierUploadUnpack(content); */ break;
            case 3022 : /* ok = informationUploadUnpack(content); */ break;
            case 9011 : /* ok = requestRespondUnpack(content); */ break;
            case 9012 : /* ok = resultRespondUnpack(content); */ break;
        }
    } else if(DeviceDir==Lower) {
        switch(Command) {
            case 1000 : /* overTimeAndReCountSetUnpack(content); */ break;
            case 1011 : /* emptyContentUnpack(content); */ Result = 1; ok = true; break;
            case 1012 : /* timeSetAndQueryUnpack(content); */ break;
            case 1013 : /* timeCalibrationRespondUnpack(content); */ break;
            case 1061 : /* emptyContentUnpack(content); */ break;
            case 1062 : /* realCycleSetAndQueryUnpack(content); */ break;
            case 1063 : /* emptyContentUnpack(content); */ break;
            case 1064 : /* minCycleSetAndQueryUnpack(content); */ break;
            case 1072 : /* passwordSetUnpack(content); */ break;
            case 2011 : /* emptyContentUnpack(content); */ break;
            case 2012 : /* emptyContentUnpack(content); */ break;
            case 2021 : /* emptyContentUnpack(content); */ break;
            case 2022 : /* emptyContentUnpack(content); */ break;
            case 2031 : /* historyRequestUnpack(content); */ break;
            case 2041 : /* historyRequestUnpack(content); */ break;
            case 2051 : /* historyRequestUnpack(content); */ break;
            case 2061 : /* historyRequestUnpack(content); */ break;
            case 3011 : /* analyzerRequestUnpack(content); */ break;
            case 3012 : /* analyzerRequestUnpack(content); */ break;
            case 3013 : /* analyzerRequestUnpack(content); */ break;
            case 3014 : /* analyzerRequestUnpack(content); */ break;
            case 3015 : /* analyzerRequestUnpack(content); */ break;
            case 3016 : /* analyzerRequestUnpack(content); */ break;
            case 3017 : /* analyzerTimeCalibrationRequestUnpack(content); */ break;
            case 3018 : /* analyzerSamplingCycleUnpack(content); */ break;
            case 3019 : /* analyzerRequestUnpack(content); */ break;
            case 3020 : /* analyzerRequestUnpack(content); */ break;
            case 3021 : /* analyzerRequestUnpack(content); */ break;
            case 3022 : /* informationRequestUnpack(content); */ break;
            case 9014 : /* emptyContentUnpack(content); */ break;
        }
    }
    return ok;
}
