#include "userpollutant.h"

UserPollutant::UserPollutant(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,const QString &qUnit,int qDot,QObject *parent) : QObject(parent)
{
    setPollutantParameter(code,name,type,dUnit,dDot,qUnit,qDot);
}

UserPollutant::UserPollutant(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,QObject *parent) : QObject(parent)
{
    setPollutantParameter(code,name,type,dUnit,dDot);
}

UserPollutant::~UserPollutant()
{

}

void UserPollutant::setPollutantParameter(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,const QString &qUnit,int qDot)
{
    Parameter.Code = code;
    Parameter.Name = name;
    Parameter.Type = type;
    Parameter.DensityUnit = dUnit;
    Parameter.DensityDot = dDot;
    Parameter.QuantityUnit = qUnit;
    Parameter.QuantityDot = qDot;
}

void UserPollutant::setPollutantParameter(const QString &code,const QString &name,int type,const QString &dUnit,int dDot)
{
    Parameter.Code = code;
    Parameter.Name = name;
    Parameter.Type = type;
    Parameter.DensityUnit = dUnit;
    Parameter.DensityDot = dDot;
}

float UserPollutant::couData(enum TimmingType type)
{
    float data = -1;
    if(type==MINUTE)
    {
        data = MinuteData.Cou;
    } else if(type==HOUR) {
        data = HourData.Cou;
    } else if(type==DAY) {
        data = DayData.Cou;
    }
    return data;
}

float UserPollutant::minData(enum TimmingType type)
{
    float data = -1;
    if(type==MINUTE)
    {

    } else if(type==HOUR) {

    } else if(type==DAY) {

    }
    return data;
}

float UserPollutant::avgData(enum TimmingType type)
{
    float data = -1;
    if(type==MINUTE)
    {

    } else if(type==HOUR) {

    } else if(type==DAY) {

    }
    return data;
}

float UserPollutant::maxData(enum TimmingType type)
{
    float data = -1;
    if(type==MINUTE)
    {

    } else if(type==HOUR) {

    } else if(type==DAY) {

    }
    return data;
}

float UserPollutant::zsMinData(enum TimmingType type)
{
    float data = -1;
    if(type==MINUTE)
    {

    } else if(type==HOUR) {

    } else if(type==DAY) {

    }
    return data;
}

float UserPollutant::zsAvgData(enum TimmingType type)
{
    float data = -1;
    if(type==MINUTE)
    {

    } else if(type==HOUR) {

    } else if(type==DAY) {

    }
    return data;
}

float UserPollutant::zsMaxData(enum TimmingType type)
{
    float data = -1;
    if(type==MINUTE)
    {

    } else if(type==HOUR) {

    } else if(type==DAY) {

    }
    return data;
}

char UserPollutant::timmingFlag(enum TimmingType type)
{
    char flag = 'F';
    if(type==MINUTE)
    {
        flag = MinuteData.Flag;
    } else if(type==HOUR) {
        flag = HourData.Flag;
    } else if(type==DAY) {
        flag = DayData.Flag;
    }
    return flag;
}


