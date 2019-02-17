#include "userclientdatabasefile.h"
#include "userclienttable.h"
#include "userdatabase.h"
#include <QSqlDatabase>
#include <QDebug>

UserClientDatabaseFile::UserClientDatabaseFile()
{
}

UserClientDatabaseFile::~UserClientDatabaseFile()
{
}
//删除数据库
void UserClientDatabaseFile::removeDatabase(const QString &mn)
{
    UserDataBase::removeDatabase(UserDataBase::CLIENT,mn);
}
/*-------------------- 客户端监测设备的基本参数操作 --------------------*/
//获取客户端的基本信息，包括标准版本、设备编码、设备密码、系统类型
QStringList UserClientDatabaseFile::deviceBaseInfo(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    QStringList baseInfo  = table.deviceBaseInfo(UserClientTable::PARA_DEVICE);
    return baseInfo;
}
//获取客户端配置参数
QStringList UserClientDatabaseFile::deviceConfig(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    QStringList config = table.deviceConfig(UserClientTable::PARA_DEVICE,mn);
    return config;
}
//设置客户端配置参数
void UserClientDatabaseFile::setDeviceConfig(const QString &mn,const QStringList &config)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    if(!table.findDeviceConfig(UserClientTable::PARA_DEVICE,mn)) {
        table.addDeviceConfig(UserClientTable::PARA_DEVICE,config);
    } else {
        table.editDeviceConfig(UserClientTable::PARA_DEVICE,config);
    }
}
//删除客户端配置
void UserClientDatabaseFile::delDeviceConfig(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    table.delDeviceConfig(UserClientTable::PARA_DEVICE,mn);
}
/*-------------------- 客户端链接槽配置参数操作 --------------------*/
//设置客户端链接槽配置
void UserClientDatabaseFile::setSocketConfig(const QString &mn,const QStringList &config)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    if(config.count()>=3) {
        if(!table.findServerConfig(UserClientTable::PARA_SERVER,config.at(1),config.at(2).toInt())) {
            table.addServerConfig(UserClientTable::PARA_SERVER,config);
        } else {
            table.editServerConfig(UserClientTable::PARA_SERVER,config);
        }
    }
}
//删除客户端链接槽配置
void UserClientDatabaseFile::delSocketConfig(const QString &mn,const QString &ipaddr,int port)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    table.delServerConfig(UserClientTable::PARA_SERVER,ipaddr,port);
}
//获取客户端链接槽配置列表
QList<QStringList> UserClientDatabaseFile::socketConfigList(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    QList<QStringList> list = table.serverConfigList(UserClientTable::PARA_SERVER);
    return list;
}
//设置客户端链接槽配置列表
void UserClientDatabaseFile::setSocketConfigList(const QString &mn,const QList<QStringList> &list)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    for(int i=0;i<list.count();i++) {
        QStringList config = list.at(i);
        if(config.count()>=3) {
            if(!table.findServerConfig(UserClientTable::PARA_SERVER,config.at(1),config.at(2).toInt())) {
                table.addServerConfig(UserClientTable::PARA_SERVER,config);
            } else {
                table.editServerConfig(UserClientTable::PARA_SERVER,config);
            }
        }
    }
}
//删除客户端链接槽配置列表
void UserClientDatabaseFile::delSocketConfigList(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    table.delAllServerConfig(UserClientTable::PARA_SERVER);
}

/*-------------------- 客户端污染j监测因子配置操作 --------------------*/
//
QStringList UserClientDatabaseFile::pollutantConfig(const QString &mn,const QString &code)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    QStringList config = table.pollutantConfig(UserClientTable::PARA_POLLUTANT,code);
    return config;
}
//
void UserClientDatabaseFile::setPolutantConfig(const QString &mn,const QStringList &config)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    if(!table.findPollutantConfig(UserClientTable::PARA_POLLUTANT,config.first())) {
        table.addPollutantConfig(UserClientTable::PARA_POLLUTANT,config);
    } else {
        table.editPollutantConfig(UserClientTable::PARA_POLLUTANT,config);
    }
}
//
void UserClientDatabaseFile::delPollutantConfig(const QString &mn,const QString &code)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    table.delPollutantConfig(UserClientTable::PARA_POLLUTANT,code);
}
//
QStringList UserClientDatabaseFile::pollutantCodeList(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    QStringList list = table.pollutantCodeList(UserClientTable::PARA_POLLUTANT);
    return list;
}
//
QList<QStringList> UserClientDatabaseFile::pollutantConfigList(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    QList<QStringList> list = table.pollutantConfigList(UserClientTable::PARA_POLLUTANT);
    return list;
}
//
void UserClientDatabaseFile::setPollutantConfigList(const QString &mn,const QList<QStringList> &list)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    for(int i=0;i<list.count();i++) {
        QStringList config = list.at(i);
        if(config.count()>=1) {
            if(!table.findPollutantConfig(UserClientTable::PARA_POLLUTANT,config.first())) {
                table.addPollutantConfig(UserClientTable::PARA_POLLUTANT,config);
            } else {
                table.editPollutantConfig(UserClientTable::PARA_POLLUTANT,config);
            }
        }
    }
}
//
void UserClientDatabaseFile::delPollutantConfigList(const QString &mn)
{
    UserClientTable table(UserDataBase::connectDatabase(UserDataBase::CLIENT,mn));
    table.delAllPollutantConfig(UserClientTable::PARA_POLLUTANT);
}
