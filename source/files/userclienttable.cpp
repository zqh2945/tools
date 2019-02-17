#include "userclienttable.h"
#include <QSqlRecord>
#include <QDebug>

UserClientTable::UserClientTable(QSqlDatabase db) : QSqlQuery (db)
{

}

UserClientTable::~UserClientTable()
{

}
//获取表名称
QString UserClientTable::getTableName(enum TableType type)
{
    QString tableName;
    if(type==PARA_DEVICE) {
        tableName = "ParameterDevice";
    } else if(type==PARA_SERVER) {
        tableName = "ParameterServer";
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
bool UserClientTable::setTableField(enum TableType type)
{
    bool ok = false;
    TableField.clear();
    if(type==PARA_DEVICE) { //客户端基本参数
        TableField.append("Version","int",true);
        TableField.append("DeviceCode","char",24,true,true);
        TableField.append("Password","char",6,true);
        TableField.append("SystemType","char",2,true);
        ok = true;
    } else if(type==PARA_SERVER) { //客户端服务器参数
        TableField.append("Enable","int",0,true);
        TableField.append("IPAddress","char",15,true,true);
        TableField.append("Port","int",0,true,true);
        ok = true;
    } else if(type==PARA_POLLUTANT) { //客户端污染因子参数
        TableField.append("PollCode","char",6,true,true);
        TableField.append("PollName","char",20,true);
        TableField.append("PollType","int",true);
        TableField.append("DensityUnit","char",10,true);
        TableField.append("DensityDot","char",2,true);
        TableField.append("QuantityUnit","char",10);
        TableField.append("QuantityDot","char",2);
        ok = true;
    } else if(type==PARA_MANAGE) { //客户端污染治理设施参数
        TableField.append("ManageCode","char",6,true,true);
        TableField.append("ManageName","char",20,true);
        ok = true;
    } else if(type==PARA_ANALYZER) { //客户端在线监控（监测）仪器仪表参数
        TableField.append("AnalyzerCode","char",6,true,true);
        TableField.append("AnalyzerName","char",20,true);
        ok = true;
    } else if(type==POLL_REAL) { //污染监测因子实时数据
        TableField.append("PollCode","char",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("RealData","float",true);
        TableField.append("DataFlag","char",1,true);
        TableField.append("SamplingTime","datatime");
        TableField.append("SamplingFlag","char",1);
        ok = true;
    } else if(type==POLL_MINUTE) { //污染监测因子分钟数据
        TableField.append("PollCode","char",6,true,true);
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
        TableField.append("PollCode","char",6,true,true);
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
        TableField.append("ManageCode","varchar",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("Status","int",0,true);
        ok = true;
    } else if(type==MANAGE_TIMMING) { //污染治理设施日运行时间
        TableField.append("ManageCode","varchar",6,true,true);
        TableField.append("Datetime","datetime",true,true);
        TableField.append("DurationTime","int",true);
    }
    return ok;
}

//表添加
void UserClientTable::addTable(enum TableType type)
{
    QString table = getTableName(type);
    if(setTableField(type)) {
        QString command = QString("create table %1 (%2)").arg(table).arg(TableField.command());
        exec(command);
        //qDebug() << __FUNCTION__ << command;
    }
}
/*-------------------- 监测设备配置参数操作 --------------------*/
QStringList UserClientTable::deviceBaseInfo(enum TableType type)
{
    QStringList baseInfo;
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString fieldList = "Version,DeviceCode,Password,SystemType";
        QString command = QString("select %1 from %2").arg(fieldList).arg(table);
        if(exec(command)) {
            first();
            if(at()>=0) {
                baseInfo.append(record().value("Version").toString());
                baseInfo.append(record().value("DeviceCode").toString());
                baseInfo.append(record().value("Password").toString());
                baseInfo.append(record().value("SystemType").toString());
            }
        }
        //qDebug() << __FUNCTION__ << command;
    }
    return baseInfo;
}

void UserClientTable::addDeviceBaseInfo(enum TableType type,const QStringList &baseInfo)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        if(baseInfo.count()>=6) {
            QString fieldList = "Version,DeviceCode,Password,SystemType";
            QString command = QString("insert into %1(%2) values").arg(table).arg(fieldList);
            command.append(QString("(%1,").arg(baseInfo.at(0).toInt()));
            command.append(QString("'%1',").arg(baseInfo.at(1)));
            command.append(QString("'%1',").arg(baseInfo.at(2)));
            command.append(QString("'%1',").arg(baseInfo.at(3)));
            exec(command);
            //qDebug() << __FUNCTION__ << command;
        }
    }
}
void UserClientTable::editDeviceBaseInfo(enum TableType type,const QStringList &baseInfo)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        if(baseInfo.count()>=6) {
            QString command = QString("update %1 set ").arg(table);
            command.append(QString("Version=%1,").arg(baseInfo.at(0).toInt()));
            command.append(QString("DeviceCode='%1',").arg(baseInfo.at(1)));
            command.append(QString("Password='%1',").arg(baseInfo.at(2)));
            command.append(QString("SystemType='%1',").arg(baseInfo.at(3)));
            command.append(QString(" where DeviceCode='%1'").arg(baseInfo.at(1)));
            exec(command);
            //qDebug() << __FUNCTION__ << command;
        }
    }
}

QStringList UserClientTable::deviceConfig(enum TableType type,const QString &mn)
{
    QStringList list;
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("select * from %1 where DeviceCode='%2'").arg(table).arg(mn);
        if(exec(command)) {
            first();
            if(at()>=0) {
                list.append(record().value("Version").toString());
                list.append(record().value("DeviceCode").toString());
                list.append(record().value("Password").toString());
                list.append(record().value("SystemType").toString());
            }
        }
        //qDebug() << __FUNCTION__ << command;
    }
    return list;
}

void UserClientTable::addDeviceConfig(enum TableType type,const QStringList &config)
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
            //qDebug() << __FUNCTION__ << command;
        }
    }
}

void UserClientTable::editDeviceConfig(enum TableType type,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        if(config.count()>=4) {
            QString command = QString("update %1 set ").arg(table);
            command.append(QString("Version=%1,").arg(config.at(0).toInt()));
            command.append(QString("Password='%1',").arg(config.at(2)));
            command.append(QString("SystemType='%1',").arg(config.at(3)));
            command.append(QString(" where DeviceCode='%1'").arg(config.at(1)));
            exec(command);
            //qDebug() << __FUNCTION__ << command;
        }
    }
}

void UserClientTable::delDeviceConfig(enum TableType type,const QString &mn)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("delete from %1 where DeviceCode='%2'").arg(table).arg(mn);
        exec(command);
    }
}


bool UserClientTable::findDeviceConfig(enum TableType type,const QString &mn)
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

void UserClientTable::delAllDeviceConfig(enum TableType type)
{
    QString table = getTableName(type);
    if(type==PARA_DEVICE) {
        QString command = QString("delete from %1").arg(table);
        exec(command);
    }
}

/*-------------------- 监测设备服务器参数操作 ---------------------*/
QList<QStringList> UserClientTable::serverConfigList(enum TableType type)
{
    QList<QStringList> list;
    QString table = getTableName(type);
    if(type==PARA_SERVER) {
        QString command = QString("select * from %1").arg(table);
        if(exec(command)) {
            first();
            while(at()>=0) {
                QStringList server;
                server.append(record().value("Enable").toString());
                server.append(record().value("IPAddress").toString());
                server.append(record().value("Port").toString());
                list.append(server);
                next();
            }
        }
    }
    return list;
}

void UserClientTable::addServerConfig(enum TableType type,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_SERVER) {
        if(config.count()>=3) {
            QString command = QString("insert into %1 values").arg(table);
            command.append(QString("(%1,").arg(config.at(0).toInt()));
            command.append(QString("'%1',").arg(config.at(1)));
            command.append(QString("%1)").arg(config.at(2).toInt()));
            exec(command);
            //qDebug() << command;
        }
    }

}

void UserClientTable::editServerConfig(enum TableType type,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_SERVER) {
        if(config.count()>=3) {
            QString command = QString("update %1 set ").arg(table);
            command.append(QString("Enable=%1,").arg(config.at(0).toInt()));
            command.append(QString(" where IPAddress='%1' and Port=%2").arg(config.at(1)).arg(config.at(2).toInt()));
            exec(command);
            //qDebug() << command;
        }
    }
}

void UserClientTable::delServerConfig(enum TableType type,const QString &ipaddr,int port)
{
    QString table = getTableName(type);
    if(type==PARA_SERVER) {
        QString command = QString("delete from %1 where IPAddress='%1' and Port=%2").arg(table).arg(ipaddr).arg(port);
        exec(command);
    }
}

bool UserClientTable::findServerConfig(enum TableType type,const QString &ipaddr,int port)
{
    bool ok = false;
    QString table = getTableName(type);
    if(type==PARA_SERVER) {
        QString command = QString("select DeviceCode from %1 where IPAddress='%2' and Port=%3").arg(table).arg(ipaddr).arg(port);
        exec(command);
        first();
        if(at()>=0) {ok = true;}
        //qDebug() << command << ok;
    }
    return ok;
}

void UserClientTable::delAllServerConfig(enum TableType type)
{
    QString table = getTableName(type);
    if(type==PARA_SERVER) {
        QString command = QString("delete from %1").arg(table);
        exec(command);
    }
}
/*-------------------- 监测设备污染因子参数操作 --------------------*/
QStringList UserClientTable::pollutantCodeList(enum TableType type)
{
    QStringList list;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select PollCode from %1").arg(table);
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

QList<QStringList> UserClientTable::pollutantConfigList(enum TableType type)
{
    QList<QStringList> list;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select * from %1").arg(table);
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

QStringList UserClientTable::pollutantConfig(enum TableType type,const QString &code)
{
    QStringList config;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select * from %1 where PollCode='%2'").arg(table).arg(code);
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

void UserClientTable::addPollutantConfig(enum TableType type,const QStringList &config)
{
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        if(config.count()>=7) {
            QString command = QString("insert into %1 values").arg(table);
            command.append(QString("('%1',").arg(config.at(0)));
            command.append(QString("'%1',").arg(config.at(1)));
            command.append(QString("%1,").arg(config.at(2).toInt()));
            command.append(QString("'%1',").arg(config.at(3)));
            command.append(QString("'%1',").arg(config.at(4)));
            command.append(QString("'%1',").arg(config.at(5)));
            command.append(QString("'%1')").arg(config.at(6)));
            exec(command);
            //qDebug() << command;
        }
    }
}

void UserClientTable::editPollutantConfig(enum TableType type,const QStringList &config)
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
            command.append(QString(" where PollCode='%1'").arg(config.at(0)));
            exec(command);
            //qDebug() << command;
        }
    }
}

void UserClientTable::delPollutantConfig(enum TableType type,const QString &code)
{
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("delete from %1 where PollCode='%2'").arg(table).arg(code);
        exec(command);
    }
}

bool UserClientTable::findPollutantConfig(enum TableType type,const QString &code)
{
    bool ok = false;
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("select * from %1 where PollCode='%2'").arg(table).arg(code);
        if(exec(command)) {
            first();
            if(at()>=0) {ok = true;}
        }
    }
    return ok;
}

void UserClientTable::delAllPollutantConfig(enum TableType type)
{
    QString table = getTableName(type);
    if(type==PARA_POLLUTANT) {
        QString command = QString("delete from %1").arg(table);
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








