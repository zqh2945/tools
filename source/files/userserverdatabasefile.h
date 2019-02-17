#ifndef USERSERVERDATABASEFILE_H
#define USERSERVERDATABASEFILE_H

#include <QStringList>
#include <QString>

class UserServerDatabaseFile
{
public:
    UserServerDatabaseFile();
    ~UserServerDatabaseFile();
    static void removeDatabase(const QString &ipaddr,int port);
    //监测设备基本参数
    static void setDeviceBaseInfo(const QString &ipaddr,int port,const QStringList &baseInfo);
    static QStringList deviceConfig(const QString &ipaddr,int port,const QString &mn);
    static void setDeviceConfig(const QString &ipaddr,int port,const QStringList &config);
    static void delDeviceConfig(const QString &ipaddr,int port,const QString &mn);
    static QStringList deviceCodeList(const QString &ipaddr,int port);
    static QList<QStringList> deviceBaseInfoList(const QString &ipaddr,int port);
    static void setDeviceBaseInfoList(const QString &ipaddr,int port,const QList<QStringList> &list);
    static void delDeviceConfigList(const QString &ipaddr,int port);
    //监测设备污染因子参数
    static QStringList pollutantConfig(const QString ipaddr,int port,const QString &mn,const QString &code);
    static void setPolutantConfig(const QString ipaddr,int port,const QString &mn,const QStringList &config);
    static void delPollutantConfig(const QString ipaddr,int port,const QString &mn,const QString &code);
    static QStringList pollutantCodeList(const QString ipaddr,int port,const QString &mn);
    static QList<QStringList> pollutantConfigList(const QString ipaddr,int port,const QString &mn);
    static void setPollutantConfigList(const QString ipaddr,int port,const QString &mn,QList<QStringList> &listist);
    static void delPollutantConfigList(const QString ipaddr,int port,const QString &mn);
};

#endif // USERSERVERDATABASEFILE_H
