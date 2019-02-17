#ifndef USERSERVERLOGFILE_H
#define USERSERVERLOGFILE_H

#include <QString>

class UserServerLogFile
{
public:
    UserServerLogFile();
    ~UserServerLogFile();

    static void newLogFile(const QString &ipaddr,int port);
    static void newLogFile(const QString &ipaddr,int port,const QString &mn);
    static void newLogFile(const QString &ipaddr,int port,const QStringList &mnList);
    static void removeLogFile(const QString &ipaddr,int port);
    static void removeLogFile(const QString &ipaddr,int port,const QString &mn);
    static QString readLog(const QString &ipaddr,int port);
    static QString readLog(const QString &ipaddr,int port,const QString &mn);
    static void writeLog(const QString &ipaddr,int port,const QString &log);
    static void writeLog(const QString &ipaddr,int port,const QString &mn,const QString &log);
private:
    static QString toDirectory();
    static QString toDirectory(const QString &ipaddr,int port);
    static QString getPath(const QString &inaddr,int port);
    static QString getPath(const QString &ipaddr,int port,const QString &mn);
};

#endif // USERSERVERLOGFILE_H
