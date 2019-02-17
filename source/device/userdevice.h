#ifndef USERDEVICE_H
#define USERDEVICE_H

#include <QObject>
#include <QDateTime>
#include "userpollutant.h"
#include "usermanage.h"

class UserDevice : public QObject
{
    Q_OBJECT
public:
    enum Direction {Upper=0,Lower=1};
    explicit UserDevice(enum Direction dir,QObject *parent=0);
    explicit UserDevice(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent=0);
    ~UserDevice();
    void initialization(const QString &ipaddr,int port,const QString &mn); //数采仪初始化
    void initialization(const QString &mn); //数采仪初始化
    void start(); //数采仪开机
    void stop(); //数采仪关机
    bool state(); //数采仪状态

    enum Direction direction() {return DeviceDir;}
    int version() {return Version;}
    void setVersion(int version) {Version = version;}
    QString deviceMN() {return DeviceMN;}
    void setDeviceMN(const QString &mn) {DeviceMN = mn;}
    QString devicePW() {return DevicePW;}
    void setDevicePW(const QString &pw) {DevicePW = pw;}
    QString deviceST() {return DeviceST;}
    void setDeviceST(const QString &st) {DeviceST = st;}

    int command() {return Command;}
    void setCommand(int cn) {Command = cn;}
    int request() {return Request;} //请求应答标志获取
    void setRequest(int request) {Request = request;} //请求应答标志设置
    int result() {return Result;} //执行结果标志获取
    void setResult(int result) {Result = result;} //执行结果标志设置

    int overTime() {return OverTime;}
    void setOverTime(int time) {OverTime = time;}
    int reCount() {return ReCount;}
    void setReCount(int cnt) {ReCount = cnt;}
    int realCycle() {return RealCycle;}
    void setRealCycle(int cycle) {RealCycle = cycle;}
    bool realUpload() {return RealUpload;}
    void setRealUpload(bool upload) {RealUpload = upload;}
    int minCycle() {return MinCycle;}
    void setMinCycle(int cycle) {MinCycle = cycle;}
    bool minUpload() {return MinUpload;}
    void setMinUpload(bool upload) {MinUpload = upload;}
    bool hourUpload() {return HourUpload;}
    void setHourUpload(bool upload) {HourUpload = upload;}
    void setSystemTime(const QDateTime &time) {SystemTime = time;} //系统时间设置

    QDateTime realDataTime() {return RealDataTime;}
    QDateTime minuteDataTime() {return MinuteDataTime;}
    QDateTime hourDataTime() {return HourDataTime;}
    QDateTime dayDataTime() {return DayDataTime;}
    QList<UserPollutant*> pollutantList() {return PollutantList;}
    QList<UserManage*> manageList() {return ManageList;}

    void receiveMessage(const QString &msg);
    void receiveMessage(const QString &id,const QString &msg);
signals:
    void runningLog(const QString &log);
    void sendMsg(const QString &msg);
    void sendMsg(const QString &id,const QString &msg);
    void protocolUpdateQN();
    void protocolUnpack(const QString &msg);
    void protocolPack(QString *msg,int cn,bool reply,bool split);
private:
    enum Direction DeviceDir; //设备类型
    bool DeviceState; //数采仪状态

    int Version; //标准版本
    QString DeviceMN; //设备唯一标识
    QString DevicePW; //设备密码
    QString DeviceST; //系统类型

    int Command; //操作命令
    int Request; //请求应答标志
    int Result; //执行结果标志
    int OverTime; //超时时间
    int ReCount; //重发次数
    int RealCycle; //实时数据上报周期
    bool RealUpload; //实时数据上报标志
    int MinCycle; //分钟数据上报周期
    bool MinUpload; //分钟数据上报标志
    bool HourUpload; //小时数据上报标志

    QDateTime SystemTime; //系统时间
    QDateTime PowerOnTime; //开机时间
    QDateTime PowerOffTime; //关机时间
    QDateTime RealDataTime; //实时数据时间
    QDateTime MinuteDataTime; //分钟数据时间
    QDateTime HourDataTime; //小时数据时间
    QDateTime DayDataTime; //日数据时间
    QList<UserPollutant*> PollutantList; //污染因子列表
    QList<UserManage*> ManageList; //污染治理设施列表

    bool ReceiveCommandHandle(); //接收指令执行
};

#endif // USERDEVICE_H
