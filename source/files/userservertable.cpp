#include "userservertable.h"
#include <QSqlRecord>
#include <QDebug>

UserServerTable::UserServerTable(QSqlDatabase db) : QSqlQuery (db)
{

}

UserServerTable::~UserServerTable()
{

}
//获取表名称
QString UserServerTable::getTableName(enum TableType type)
{
    QString tableName;
    if(type==PARA_DEVICE) {
        tableName = "ParameterDevice";
    } else if(type==PARA_POLLUTANT) {
        tableName = "ParameterPollutant";
    } else if(type==PARA_MANAGE) {
        tableName = "ParameterManage";
    } else if(type==PARA_ANALYZER) {
        tableName = "ParameterAnalyzer";
    } else if(type==POLL_REAL) {
        tableName = "PollutantRealData";
    } else if(type==POLL_MINUTE) {
        tableName = "PollutantMinuteData";
    } else if(type==POLL_HOUR) {
        tableName = "PollutantHourData";
    } else if(type==POLL_DAY) {
        tableName = "PollutantDayData";
    } else if(type==MANAGE_STATUS) {
        tableName = "ManageStatus";
    } else if(type==MANAGE_TIMMING) {
        tableName = "ManageDayTimming";
    }
    return tableName;
}
//初始化表字段
bool UserServerTable::setTableField(enum TableType type)
{
    bool ok = false;
    TableField.clear();
    if(type==PARA_DEVICE) {
        TableField.append("Version","int",true);
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("Password","char",6,true);
        TableField.append("SystemType","char",2,true);
        ok = true;
    } else if(type==PARA_POLLUTANT) {
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("PollCode","char",6,true,true);
        TableField.append("PollName","char",20,true);
        TableField.append("PollType","int",true);
        TableField.append("DensityUnit","char",10,true);
        TableField.append("DensityDot","char",2,true);
        TableField.append("QuantityUnit","char",10);
        TableField.append("QuantityDot","char",2);
        ok = true;
    } else if(type==PARA_MANAGE) { //客户端污染治理设施参数
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("ManageCode","char",6,true,true);
        TableField.append("ManageName","char",20,true);
        ok = true;
    } else if(type==PARA_ANALYZER) { //客户端在线监控（监测）仪器仪表参数
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("AnalyzerCode","char",6,true,true);
        TableField.append("AnalyzerName","char",20,true);
        ok = true;
    } else if(type==POLL_REAL) { //污染监测因子实时数据
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("PollCode","char",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("RealData","float",true);
        TableField.append("DataFlag","char",true);
        TableField.append("SamplingTime","datatime");
        TableField.append("SamplingFlag","char");
        ok = true;
    } else if(type==POLL_MINUTE) { //污染监测因子分钟数据
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("PollCode","varchar",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("CouData","float");
        TableField.append("MinData","float");
        TableField.append("AvgData","float");
        TableField.append("MaxData","float");
        TableField.append("ZsMinData","float");
        TableField.append("ZsAvgData","float");
        TableField.append("ZsMaxData","float");
        ok = true;
    } else if(type==POLL_HOUR) { //污染监测因子小时数据
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("PollCode","varchar",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("CouData","float");
        TableField.append("MinData","float");
        TableField.append("AvgData","float");
        TableField.append("MaxData","float");
        TableField.append("ZsMinData","float");
        TableField.append("ZsAvgData","float");
        TableField.append("ZsMaxData","float");
        ok = true;
    } else if(type==POLL_DAY) { //污染监测因子日数据
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("PollCode","varchar",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("CouData","float");
        TableField.append("MinData","float");
        TableField.append("AvgData","float");
        TableField.append("MaxData","float");
        TableField.append("ZsMinData","float");
        TableField.append("ZsAvgData","float");
        TableField.append("ZsMaxData","float");
        ok = true;
    } else if(type==MANAGE_STATUS) { //污染治理设施运行状态
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("ManageCode","varchar",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("Status","int",true);
        ok = true;
    } else if(type==MANAGE_TIMMING) { //污染治理设施日运行时间
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("ManageCode","varchar",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("Duration","int",true);
        ok = true;
    }
    return ok;
}

//表添加
void UserServerTable::addTable(enum TableType type)
{
    QString table = getTableName(type);
    if(setTableField(type)) {
        QString command = QString("create table %1 (%2)").arg(table).arg(TableField.command());
        exec(command);
        //qDebug() << command;
    }
}
/*-------------------- 监测设备基本配置参数操作 --------------------*/
QStringList UserServerTable::deviceCodeList(enum TableType type)
{
    QStringList list;
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("select DeviceCode from %1").arg(table);
        exec(command);
        //qDebug() << command;
        first();
        while(at()>=0) {
            list.append(record().value("DeviceCode").toString());
            next();
        }
    }
    return list;
}

QList<QStringList> UserServerTable::deviceBaseInfoList(enum TableType type)
{
    QList<QStringList> list;
    QStringList baseInfo;
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString fieldList = "Version,DeviceCode,Password,SystemType";
        QString command = QString("select %1 from %2").arg(fieldList).arg(table);
        exec(command);
        first();
        while(at()>=0) {
            baseInfo.clear();
            baseInfo.append(record().value("Version").toString());
            baseInfo.append(record().value("DeviceCode").toString());
            baseInfo.append(record().value("Password").toString());
            baseInfo.append(record().value("SystemType").toString());
            list.append(baseInfo);
            next();
        }
    }
    return list;
}

void UserServerTable::addDeviceBaseInfo(enum TableType type,const QStringList &baseInfo)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        if(baseInfo.count()>=4) {
            QString fieldList = "Version,DeviceCode,Password,SystemType";
            QString command = QString("insert into %1(%2) values").arg(table).arg(fieldList);
            command.append(QString("(%1,").arg(baseInfo.at(0).toInt()));
            command.append(QString("'%1',").arg(baseInfo.at(1)));
            command.append(QString("'%1',").arg(baseInfo.at(2)));
            command.append(QString("'%1')").arg(baseInfo.at(3)));
            exec(command);
            //qDebug() << command;
        }
    }
}

void UserServerTable::editDeviceBaseInfo(enum TableType type,const QStringList &baseInfo)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        if(baseInfo.count()>=4) {
            QString command = QString("update %1 set ").arg(table);
            command.append(QString("Version=%1,").arg(baseInfo.at(0).toInt()));
            command.append(QString("Password='%1'',").arg(baseInfo.at(2)));
            command.append(QString("SystemType='%1'").arg(baseInfo.at(3)));
            command.append(QString(" where DeviceCode='%1'").arg(baseInfo.at(1)));
            exec(command);
            //qDebug() << command;
        }
    }
}

QStringList UserServerTable::deviceConfig(enum TableType type,const QString &mn)
{
    QStringList config;
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("select * from %1 where DeviceCode='%2'").arg(table).arg(mn);
        exec(command);
        //qDebug() << command;
        first();
        if(at()>=0) {
            config.append(record().value("Version").toString());
            config.append(record().value("DeviceCode").toString());
            config.append(record().value("Password").toString());
            config.append(record().value("SystemType").toString());
            next();
        }
    }
    return config;
}

void UserServerTable::addDeviceConfig(enum TableType type,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        if(config.count()>=4) {
            QString command = QString("insert into %1 values").arg(table);
            command.append(QString("(%1,").arg(config.at(0).toInt()));
            command.append(QString("'%1',").arg(config.at(1)));
            command.append(QString("'%1',").arg(config.at(2)));
            command.append(QString("'%1')").arg(config.at(3)));
            exec(command);
            //qDebug() << command;
        }
    }
}

void UserServerTable::editDeviceConfig(enum TableType type,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        if(config.count()>=4) {
            QString command = QString("update %1 set ").arg(table);
            command.append(QString("Version=%1,").arg(config.at(0).toInt()));
            command.append(QString("Password='%1'',").arg(config.at(2)));
            command.append(QString("SystemType='%1'").arg(config.at(3)));
            command.append(QString(" where DeviceCode='%1'").arg(config.at(1)));
            exec(command);
            //qDebug() << command;
        }
    }
}

void UserServerTable::delDeviceConfig(enum TableType type,const QString &mn)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("delete from %1 where DeviceCode='%2'").arg(table).arg(mn);
        exec(command);
    }
}


bool UserServerTable::findDeviceConfig(enum TableType type,const QString &mn)
{
    bool ok = false;
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("select DeviceCode from %1 where DeviceCode='%2'").arg(table).arg(mn);
        exec(command);
        first();
        if(at()>=0) {ok = true;}
        //qDebug() << command << ok;
    }
    return ok;
}

void UserServerTable::delAllDeviceConfig(enum TableType type)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("delete from %1").arg(table);
        exec(command);
    }
}

/*-------------------- 监测设备污染因子参数操作 --------------------*/
QStringList UserServerTable::pollutantCodeList(enum TableType type,const QString &mn)
{
    QStringList list;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select PollCode from %1 where DeviceCode='%2'").arg(table).arg(mn);
        if(exec(command)) {
            first();
            while(at()>=0) {
                list.append(record().value("PollCode").toString());
                next();
            }
        }
    }
    return list;
}

QList<QStringList> UserServerTable::pollutantConfigList(enum TableType type,const QString &mn)
{
    QList<QStringList> list;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select * from %1 where DeviceCode='%2'").arg(table).arg(mn);
        if(exec(command)) {
            first();
            while(at()>=0) {
                QStringList config;
                config.append(record().value("PollCode").toString());
                config.append(record().value("PollName").toString());
                config.append(record().value("PollType").toString());
                config.append(record().value("DensityUnit").toString());
                config.append(record().value("DensityDot").toString());
                config.append(record().value("QuantityUnit").toString());
                config.append(record().value("QuantityDot").toString());
                list.append(config);
                next();
            }
        }
    }
    return list;
}

QStringList UserServerTable::pollutantConfig(enum TableType type,const QString &mn,const QString &code)
{
    QStringList config;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select * from %1 where DeviceCode='%2' and PollCode='%2'").arg(table).arg(mn).arg(code);
        if(exec(command)) {
            first();
            if(at()>=0) {
                config.append(record().value("PollCode").toString());
                config.append(record().value("PollName").toString());
                config.append(record().value("PollType").toString());
                config.append(record().value("DensityUnit").toString());
                config.append(record().value("DensityDot").toString());
                config.append(record().value("QuantityUnit").toString());
                config.append(record().value("QuantityDot").toString());
            }
        }

    }
    return config;
}

void UserServerTable::addPollutantConfig(enum TableType type,const QString &mn,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        if(config.count()>=7) {
            QString command = QString("insert into %1 values").arg(table);
            command.append(QString("('%1',").arg(mn));
            command.append(QString("'%1',").arg(config.at(0)));
            command.append(QString("'%1',").arg(config.at(1)));
            command.append(QString("%1,").arg(config.at(2).toInt()));
            command.append(QString("'%1',").arg(config.at(3)));
            command.append(QString("'%1',").arg(config.at(4)));
            command.append(QString("'%1',").arg(config.at(5)));
            command.append(QString("'%1')").arg(config.at(6)));
            exec(command);
        }
    }
}

void UserServerTable::editPollutantConfig(enum TableType type,const QString &mn,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        if(config.count()>=7) {
            QString command = QString("update %1 set ").arg(table);
            command.append(QString("PollName='%1',").arg(config.at(1)));
            command.append(QString("PollType=%1,").arg(config.at(2).toInt()));
            command.append(QString("DensityUnit='%1',").arg(config.at(3)));
            command.append(QString("DensityDot='%1',").arg(config.at(4)));
            command.append(QString("QuantityUnit='%1',").arg(config.at(5)));
            command.append(QString("QuantityDot='%1'").arg(config.at(6)));
            command.append(QString(" where DeviceCode='%1' and PollCode='%2'").arg(mn).arg(config.at(0)));
            exec(command);
        }
    }
}

void UserServerTable::delPollutantConfig(enum TableType type,const QString &mn,const QString &code)
{
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("delete from %1 where DeviceCode='%2' and PollCode='%3'").arg(table).arg(mn).arg(code);
        exec(command);
    }
}

bool UserServerTable::findPollutantConfig(enum TableType type,const QString &mn,const QString &code)
{
    bool ok = false;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select * from %1 where DeviceCode='%2' and PollCode='%3'").arg(table).arg(mn).arg(code);
        if(exec(command)) {
            first();
            if(at()>=0) {ok = true;}
        }
    }
    return ok;
}

void UserServerTable::delAllPollutantConfig(enum TableType type,const QString &mn)
{
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("delete from %1 where DeviceCode='%2'").arg(table).arg(mn);
        exec(command);
    }
}
/*-------------------- 监测设备污染治理设施参数操作 --------------------*/

/*-------------------- 监测设备在线监控（监测）仪器仪表参数操作 --------------------*/

/*-------------------- 监测设备污染监测因子实时数据操作 --------------------*/

/*-------------------- 监测设备污染监测因子分钟数据操作 --------------------*/

/*-------------------- 监测设备污染监测因子小时数据操作 --------------------*/

/*-------------------- 监测设备污染监测因子日数据操作 --------------------*/

/*-------------------- 监测设备污染治理设施运行状态操作 --------------------*/

/*-------------------- 监测设备污染治理设备日运行时间操作 --------------------*/







