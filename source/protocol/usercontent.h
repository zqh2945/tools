#ifndef USERCONTENT_H
#define USERCONTENT_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QDebug>
#include "../source/device/userdevice.h"

class UserContent : public QObject
{
    Q_OBJECT
public:
    enum Direction {Upper=0,Lower=1};
    explicit UserContent(enum Direction dir,QObject *parent=0);
    explicit UserContent(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent=0);
    ~UserContent();
    bool contentUnpack(const QString &content,int cn); //报文内容解包
    QString contentPack(int cn); //报文内容打包
    enum Direction direction() {return DeviceDir;}

    int version() {return Version;} //标准版本获取
    void setVersion(int version) {Version = version;} //标准版本设置
    QString deviceMN() {return DeviceMN;} //设备唯一标识获取
    void setDeviceMN(const QString &mn) {DeviceMN = mn;} //设备唯一标识设置
    QString devicePW() {return DevicePW;} //设备密码获取
    void setDevicePW(const QString &pw) {DevicePW = pw;} //设备密码设置
    QString deviceST() {return DeviceST;} //系统类型获取
    void setDeviceST(const QString &st) {DeviceST = st;} //系统类型设置
    
	int request() {return Request;} //请求应答标志获取
    void setRequest(int request) {Request = request;} //请求应答标志设置
    int result() {return Result;} //执行结果标志获取
    void setResult(int result) {Result = result;} //执行结果标志设置
    
	void setOverTime(int time) {OverTime = time;} //超时时间设置
    void setReCount(int count) {ReCount = count;} //重发次数设置
    void setRealCycle(int cycle) {RealCycle = cycle;} //实时数据上报时间间隔设置
    void setMinuteCycle(int cycle) {MinuteCycle = cycle;} //分钟数据上报时间间隔设置
    void setPassword(const QString &password) {Password = password;} //数采仪密码设置
    void setSystemTime(const QDateTime &time) {SystemTime = time;} //系统时间设置
    void setStartTime(const QDateTime &time) {StartTime = time;} //历史数据请求起始时间设置
    void setStopTime(const QDateTime &time) {StopTime = time;}  //历史数据请求截止时间
    void setDataTime(const QDateTime &time) {DataTime = time;} //设置上报数据时间
    void setPowerOnTime(const QDateTime &time) {PowerOnTime = time;} //数采仪开机时间设置
    void setAnalyzer(const QString &code) {Analyzer = code;} //在线监控(监测)仪器仪表编码设置
    void setSamplingStart(const QTime &time) {SamplingBaseTime = time;} //采样基准时间设置
    void setSamplingCycle(int cycle) {SamplingCycle = cycle;} //采样时间间隔设置
    void setSamplingStopCycle(int cycle) {SamplingStopCycle = cycle;} //出样时间间隔设置
    void setInfoCode(QString &code) {InfoCode = code;} //现场设备信息编码设置
    void setInformation(QString &info) {Information = info;} //现场机信息设置

    UserDevice* device() {return Device;} //获取关联数采仪
    void setDevice(UserDevice *device) {Device = device;} //关联数采仪设置
private:
    enum Direction DeviceDir; //设备类型，Upper表示上位机，Lower表示数采仪
    UserDevice *Device; //数采仪

    int Version; //标准版本
    QString DeviceMN; //设备唯一标识
    QString DevicePW; //设备密码
    QString DeviceST; //系统类型

    int Request; //请求应答标志
    int Result; //执行结果标志
    int OverTime; //超时时间
    int ReCount; //重发次数
    int RealCycle; //实时数据上报时间间隔
    int MinuteCycle; //分钟数据上报时间间隔
    QString Password; //数采仪密码
    QDateTime SystemTime; //系统时间，用于时间校准
    QDateTime StartTime; //历史数据请求起始时间
    QDateTime StopTime; //历史数据请求截止时间
    QDateTime DataTime; //上报数据时间
    QDateTime PowerOnTime; //数采仪开机时间
    QString Analyzer; //在线监控(监测)仪器仪表编码
    QTime SamplingBaseTime; //采样基准时间
    int SamplingCycle; //采样时间间隔
    int SamplingStopCycle; //出样时间间隔
    QString  Identifier; //设备唯一标识
    QString InfoCode; //现场设备信息编码
    QString Information; //现场机信息

    QString fieldExtract(const QString &content,const QString &field,bool *ok);
    QDateTime datetimeExtract(const QString &datetime);
    QTime timeExtract(const QString &time);
    //请求应答解包/打包
    bool requestRespondUnpack(const QString &content);
    QString requestRespondPack();
    //执行结果解包/打包
    bool resultRespondUnpack(const QString &content);
    QString resultRespondPack();
    //数据内容为空的包解包打包
    bool emptyContentUnpack(const QString &content);
    QString emptyContentPack();
    //超时时间及重发次数解包/打包
    bool overTimeAndReCountSetUnpack(const QString &content);
    QString overTimeAndReCountSetPack();
    //数采仪时间校准解包/打包
    bool timeSetAndQueryUnpack(const QString &content);
    QString timeSetAndQueryPack();
    bool timeCalibrationRespondUnpack(const QString &content);
    QString timeCalibrationRespondPack();
    //实时数据上报时间间隔解包/打包
    bool realCycleSetAndQueryUnpack(const QString &content);
    QString realCycleSetQndQueryPack();
    //分钟数据上报时间间隔解包/打包
    bool minCycleSetAndQueryUnpack(const QString &content);
    QString minCycleSetAndQueryPack();
    //数采仪密码修改解包/打包
    bool passwordSetUnpack(const QString &content);
    QString passwordSetPack();
    //实时数据上报解包/打包
    bool realDataUploadUnpack(const QString &content);
    QString realDataUploadPack();
    //分钟数据上报解包/打包
    bool minuteDataUploadUnpack(const QString &content);
    QString minuteDataUploadPack();
    //小时数据上报解包/打包
    bool hourDataUploadUnpack(const QString &content);
    QString hourDataUploadPack();
    //日数据上报解包/打包
    bool dayDataUploadUnpack(const QString &content);
    QString dayDataUploadPack();
    //污染治理设施状态解包/打包
    bool manageFacilityStatusUploadUnpack(const QString &content);
    QString manageFacilityStatusUploadPack();
    //污染治理日运行时间解包/打包
    bool manageFacilityTimeUploadUnpack(const QString &content);
    QString manageFacilityTimeUploadPack();
    //历史数据请求解包/打包
    bool historyRequestUnpack(const QString &content);
    QString historyRequestPack();
    //数采仪开机时间上报解包/打包
    bool restartTimeUploadUnpack(const QString &content);
    QString restartTimeUploadPack();
    //在线监控（监测）仪器仪表控制指令解包/打包
    bool analyzerRequestUnpack(const QString &content);
    QString analyzerRequestPack();
    //在线监控（监测）仪器仪表时间校准解包/打包
    bool analyzerTimeCalibrationRequestUnpack(const QString &content);
    QString analyzerTimeCalibrationRequestPack();
    //在线监控（监测）仪器仪表采样时间间隔解包/打包
    bool analyzerSamplingCycleUnpack(const QString &content);
    QString analyzerSamplingCyclePack();
    //在线监控（监测）仪器仪表出样时间间隔解包/打包
    bool analyzerSamplingStopTimeRespondUnpack(const QString &content);
    QString analyzerSamplingStopTimeRespondPack();
    //在线监控（监测）仪器仪表设备唯一标识解包/打包
    bool analyzerIdentifierUploadUnpack(const QString &content);
    QString analyzerIdentifierUploadPack();
    //现场机信息解包/打包
    bool informationRequestUnpack(const QString &content);
    QString informationRequestPack();
    bool informationUploadUnpack(const QString &content);
    QString informationUploadPack();
};

#endif // USERCONTENT_H
