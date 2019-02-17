#include "userdefaultparameter.h"
#include "userserverdatabasefile.h"
#include "userservertable.h"
#include "userdatabase.h"
#include <QSqlDatabase>
#include <QDebug>

UserServerDatabaseFile::UserServerDatabaseFile()
{
}

UserServerDatabaseFile::~UserServerDatabaseFile()
{
}
//删除服务器数据库
void UserServerDatabaseFile::removeDatabase(const QString &ipaddr,int port)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserDataBase::removeDatabase(UserDataBase::SERVER,filename);
}
/*--------------------- 服务器监测设备的基本参数操作 --------------------*/
//设置服务器监测点基本信息
void UserServerDatabaseFile::setDeviceBaseInfo(const QString &ipaddr,int port,const QStringList &baseInfo)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    if(baseInfo.count()>=4) {
        if(!table.findDeviceConfig(UserServerTable::PARA_DEVICE,baseInfo.at(1))) {
            table.addDeviceBaseInfo(UserServerTable::PARA_DEVICE,baseInfo);
            QString mn = baseInfo.at(1);
            int version = baseInfo.at(0).toInt();
            QString st = baseInfo.at(3);
            //获取默认污染监测因子配置信息列表
            QList<QStringList> pollList = UserDefaultParameter::pollutantConfigList(version,st);
            for(int j=0;j<pollList.count();j++) {
                table.addPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,pollList.at(j));
            }
        } else {
            table.editDeviceBaseInfo(UserServerTable::PARA_DEVICE,baseInfo);
        }
    }
}
//获取服务器监测点配置信息
QStringList UserServerDatabaseFile::deviceConfig(const QString &ipaddr,int port,const QString &mn)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    QStringList config = table.deviceConfig(UserServerTable::PARA_DEVICE,mn);
    return config;
}
//设置服务器监测点配置信息
void UserServerDatabaseFile::setDeviceConfig(const QString &ipaddr,int port,const QStringList &config)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    if(!table.findDeviceConfig(UserServerTable::PARA_DEVICE,config.at(1))) {
        table.addDeviceConfig(UserServerTable::PARA_DEVICE,config);
    } else {
        table.editDeviceConfig(UserServerTable::PARA_DEVICE,config);
    }
}
//删除服务器监测点配置信息
void UserServerDatabaseFile::delDeviceConfig(const QString &ipaddr,int port,const QString &mn)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    table.delDeviceConfig(UserServerTable::PARA_DEVICE,mn);
}
//获取服务器监测点编码列表
QStringList UserServerDatabaseFile::deviceCodeList(const QString &ipaddr,int port)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    return table.deviceCodeList(UserServerTable::PARA_DEVICE);
}
//获取服务器监测点基本信息列表
QList<QStringList> UserServerDatabaseFile::deviceBaseInfoList(const QString &ipaddr,int port)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    return table.deviceBaseInfoList(UserServerTable::PARA_DEVICE);
}
//设置服务器监测点基本信息列表
void UserServerDatabaseFile::setDeviceBaseInfoList(const QString &ipaddr,int port,const QList<QStringList> &list)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    for(int i=0;i<list.count();i++) {
        QStringList baseInfo = list.at(i);
        if(baseInfo.count()>=4) {
            if(!table.findDeviceConfig(UserServerTable::PARA_DEVICE,baseInfo.at(1))) {
                table.addDeviceBaseInfo(UserServerTable::PARA_DEVICE,baseInfo);
                QString mn = baseInfo.at(1);
                int version = baseInfo.at(0).toInt();
                QString st = baseInfo.at(3);
                QList<QStringList> pollList = UserDefaultParameter::pollutantConfigList(version,st);
                for(int j=0;j<pollList.count();j++) {
                    table.addPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,pollList.at(j));
                }
            } else {
                table.editDeviceBaseInfo(UserServerTable::PARA_DEVICE,baseInfo);
            }
        }
    }
}
//删除服务器监测点配置列表
void UserServerDatabaseFile::delDeviceConfigList(const QString &ipaddr,int port)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    table.delAllDeviceConfig(UserServerTable::PARA_DEVICE);
}
/*----- 服务器监测设备的污染因子参数操作 -----*/
//
QStringList UserServerDatabaseFile::pollutantConfig(const QString ipaddr,int port,const QString &mn,const QString &code)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    return table.pollutantConfig(UserServerTable::PARA_POLLUTANT,mn,code);
}
//添加污染监测因子配置
void UserServerDatabaseFile::setPolutantConfig(const QString ipaddr,int port,const QString &mn,const QStringList &config)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    if(!table.findPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,config.first())) {
        table.addPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,config);
    } else {
        table.editPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,config);
    }
}
//
void UserServerDatabaseFile::delPollutantConfig(const QString ipaddr,int port,const QString &mn,const QString &code)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    table.delPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,code);
}
//获取服务器监测点污染监测因子编码列表
QStringList UserServerDatabaseFile::pollutantCodeList(const QString ipaddr,int port,const QString &mn)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    QStringList list = table.pollutantCodeList(UserServerTable::PARA_POLLUTANT,mn);
    return list;
}
//获取度武器监测点污染监测因子配置列表
QList<QStringList> UserServerDatabaseFile::pollutantConfigList(const QString ipaddr,int port,const QString &mn)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    QList<QStringList> list = table.pollutantConfigList(UserServerTable::PARA_POLLUTANT,mn);
    return list;
}
//设置服务器监测点污染监测因子配置列表
void UserServerDatabaseFile::setPollutantConfigList(const QString ipaddr,int port,const QString &mn,QList<QStringList> &list)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    for(int i=0;i<list.count();i++) {
        QStringList config = list.at(i);
        if(!table.findPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,config.first())) {
            table.addPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,config);
        } else {
            table.editPollutantConfig(UserServerTable::PARA_POLLUTANT,mn,config);
        }
    }
}
//删除服务器监测点监测污染因子配置列表
void UserServerDatabaseFile::delPollutantConfigList(const QString ipaddr,int port,const QString &mn)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    UserServerTable table(UserDataBase::connectDatabase(UserDataBase::SERVER,filename));
    table.delAllPollutantConfig(UserServerTable::PARA_POLLUTANT,mn);
}

