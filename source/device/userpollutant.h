#ifndef USERPOLLUTANT_H
#define USERPOLLUTANT_H

#include <QObject>
#include <QDateTime>

/* 污染监测因子参数类型定义 */
typedef struct
{
    QString Code; //污染监测因子编码
    QString Name; //污染监测因子名称
    int Type; //污染监测因子类型
    QString DensityUnit; //浓度单位
    int DensityDot; //浓度精度
    QString QuantityUnit; //累计值单位
    int QuantityDot; //累计值精度
}PollParaType;
/* 实时数据类型定义 */
typedef struct
{
    float Rtd;
    float ZsRtd;
    char Flag;
    QDateTime SamplingTime;
    char SamplingFlag;
}PollRealDataType;
/* 分钟、小时、日数据类型定义 */
typedef struct
{
    float Cou;
    float Avg;
    float Min;
    float Max;
    float ZsAvg;
    float ZsMin;
    float ZsMax;
    char Flag;
}PollTimmingDataType;

class UserPollutant : public QObject
{
    Q_OBJECT
public:
    enum TimmingType {MINUTE=0,HOUR=1,DAY=2};
    explicit UserPollutant(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,const QString &qUnit,int qDot,QObject *parent=0);
    explicit UserPollutant(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,QObject *parent=0);
    ~UserPollutant();
    QString code() {return Parameter.Code;}
    QString name() {return Parameter.Name;}
    int type() {return Parameter.Type;}
    QString densityUnit() {return Parameter.DensityUnit;}
    int densityDot() {return Parameter.DensityDot;}
    QString quantityUnit() {return Parameter.QuantityUnit;}
    int quantityDot() {return Parameter.QuantityDot;}
    void setPollutantParameter(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,const QString &qUnit,int qDot);
    void setPollutantParameter(const QString &code,const QString &name,int type,const QString &dUnit,int dDot);

    float realData() {return RealData.Rtd;}
    float zsRealData() {return RealData.ZsRtd;}
    char realFlag() {return RealData.Flag;}
    float couData(enum TimmingType type);
    float minData(enum TimmingType type);
    float avgData(enum TimmingType type);
    float maxData(enum TimmingType type);
    float zsMinData(enum TimmingType type);
    float zsAvgData(enum TimmingType type);
    float zsMaxData(enum TimmingType type);
    char timmingFlag(enum TimmingType type);

private:
    PollParaType Parameter; //污染监测因子参数
    PollRealDataType RealData; //污染监测因子实时数据
    PollTimmingDataType MinuteData; //污染监测因子分钟数据
    PollTimmingDataType HourData;  //污染监测因子小时数据
    PollTimmingDataType DayData; //污染监测因子日数据
  };

#endif // USERPOLLUTANT_H
