#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QSqlDatabase>
#include <QString>

class UserDataBase
{
public:
    enum PlatformType {SERVER = 0,CLIENT = 1};
    UserDataBase();
    ~UserDataBase();
    static QSqlDatabase connectDatabase(enum PlatformType type,const QString &dbName);
    static void removeDatabase(enum PlatformType type,const QString &dbName);
private:
    static QString toDirectory(enum PlatformType type);
    static QString getPath(enum PlatformType type,const QString &dbName);
    static void createTables(enum PlatformType type,const QSqlDatabase &database);
 };

#endif // USERDATABASE_H
