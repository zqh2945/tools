#ifndef USERCLIENTDATABASEFILE_H
#define USERCLIENTDATABASEFILE_H

#include <QStringList>
#include <QString>

class UserClientDatabaseFile
{
public:
    UserClientDatabaseFile();
    ~UserClientDatabaseFile();

    static void removeDatabase(const QString &mn);
    //客户端基本配置参数
    static QStringList deviceBaseInfo(const QString &mn);
    static QStringList deviceConfig(const QString &mn);
    static void setDeviceConfig(const QString &mn,const QStringList &config);
    static void delDeviceConfig(const QString &mn);
    static bool findDeviceConfig(const QString &mn);
    //客户端链接槽配置参数
    static void setSocketConfig(const QString &mn,const QStringList &config);
    static void delSocketConfig(const QString &mn,const QString &ipaddr,int port);
    static QList<QStringList> socketConfigList(const QString &mn);
    static void setSocketConfigList(const QString &mn,const QList<QStringList> &list);
    static void delSocketConfigList(const QString &mn);
    //客户端污染监测因子参数
    static QStringList pollutantConfig(const QString &mn,const QString &code);
    static void setPolutantConfig(const QString &mn,const QStringList &config);
    static void delPollutantConfig(const QString &mn,const QString &code);
    static QStringList pollutantCodeList(const QString &mn);
    static QList<QStringList> pollutantConfigList(const QString &mn);
    static void setPollutantConfigList(const QString &mn,const QList<QStringList> &list);
    static void delPollutantConfigList(const QString &mn);
};

#endif // USERCLIENTDATABASEFILE_H
