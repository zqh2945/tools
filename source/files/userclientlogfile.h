#ifndef USERCLIENTLOGFILE_H
#define USERCLIENTLOGFILE_H

#include <QString>

class UserClientLogFile
{
public:
    UserClientLogFile();
    ~UserClientLogFile();

    static void newLogFile(const QString &mn);
    static void newLogFile(const QString &mn,const QString &ipaddr,int port);
    static void newLogFile(const QString &mn,const QList<QStringList> &serList);
    static void removeLogFile(const QString &mn);
    static void removeLogFile(const QString &mn,const QString &ipaddr,int port);
    static QString readLog(const QString &mn);
    static QString readLog(const QString &mn,const QString &ipaddr,int port);
    static void writeLog(const QString &mn,const QString &log);
    static void writeLog(const QString &mn,const QString &ipaddr,int port,const QString &log);
private:
    static QString toDirectory();
    static QString toDirectory(const QString &mn);
    static QString getPath(const QString &mn);
    static QString getPath(const QString &mn,const QString &ipaddr,int port);
};

#endif // USERCLIENTLOGFILE_H
