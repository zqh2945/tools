#ifndef USERSERVERTABLE_H
#define USERSERVERTABLE_H

#include "usertablefield.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStringList>

class UserServerTable : public QSqlQuery
{
public:
    enum TableType
    {
        PARA_DEVICE = 0,PARA_POLLUTANT = 1,PARA_MANAGE = 2,PARA_ANALYZER = 3,
        POLL_REAL = 10,POLL_MINUTE = 11,POLL_HOUR = 12,POLL_DAY = 13,
        MANAGE_STATUS = 20,MANAGE_TIMMING = 21
    };
    UserServerTable(QSqlDatabase db);
    ~UserServerTable();
    void addTable(enum TableType type);
    //监测设备参数
    QStringList deviceCodeList(enum TableType type);
    QList<QStringList> deviceBaseInfoList(enum TableType type);
    void addDeviceBaseInfo(enum TableType type,const QStringList &baseInfo);
    void editDeviceBaseInfo(enum TableType type,const QStringList &baseInfo);
    QStringList deviceConfig(enum TableType type,const QString &mn);
    void addDeviceConfig(enum TableType type,const QStringList &config);
    void editDeviceConfig(enum TableType type,const QStringList &config);
    void delDeviceConfig(enum TableType type,const QString &mn);
    bool findDeviceConfig(enum TableType type,const QString &mn);
    void delAllDeviceConfig(enum TableType type);
    //污染因子参数
    QStringList pollutantCodeList(enum TableType type,const QString &mn);
    QList<QStringList> pollutantConfigList(enum TableType type,const QString &mn);
    QStringList pollutantConfig(enum TableType type,const QString &mn,const QString &code);
    void addPollutantConfig(enum TableType type,const QString &mn,const QStringList &config);
    void editPollutantConfig(enum TableType type,const QString &mn,const QStringList &config);
    void delPollutantConfig(enum TableType type,const QString &mn,const QString &code);
    bool findPollutantConfig(enum TableType type,const QString &mn,const QString &code);
    void delAllPollutantConfig(enum TableType type,const QString &mn);
    //污染治理设施参数

    //在线监控（监测）仪器仪表参数

    //污染监测因子实时数据

    //污染监测因子分钟数据

    //污染监测因子小时数据

    //污染监测因子日数据

    //污染治理设施运行状态

    //污染治理设备日运行时间

private:
    UserTableField TableField;

    QString getTableName(enum TableType type);
    bool setTableField(enum TableType type);
};

#endif // USERSERVERTABLE_H
