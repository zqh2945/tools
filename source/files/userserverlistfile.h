#ifndef USERSERVERLISTFILE_H
#define USERSERVERLISTFILE_H

#include <QDir>
#include <QFile>
#include <QString>

class UserServerListFile
{
public:
    UserServerListFile();
    ~UserServerListFile();
    static QList<QStringList> serverList();
    static void appendServer(const QString &ipaddr,int port);
    static void deleteServer(const QString &ipaddr,int port);
private:
    static QString toDirectory();
    static QList<QStringList> readFile();
    static void writeFile(const QList<QStringList> &list);
};

#endif // USERSERVERLISTFILE_H
