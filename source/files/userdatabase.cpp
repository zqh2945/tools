#include "userdatabase.h"
#include "userservertable.h"
#include "userclienttable.h"
#include <QDebug>
#include <QFile>
#include <QDir>

UserDataBase::UserDataBase()
{

}

UserDataBase::~UserDataBase()
{

}
//跳转到数据库存放路径
QString UserDataBase::toDirectory(enum PlatformType type)
{
    QDir dir = QDir::current();
    if(type==SERVER) {
        if(!dir.exists("server")) {
            dir.mkdir("server");
        }
        dir.setPath(QDir::currentPath()+"/server");
        if(!dir.exists("database")) {
            dir.mkdir("database");
        }
        dir.setPath(QDir::currentPath()+"/server/database");
    } else {
        if(!dir.exists("client")) {
            dir.mkdir("client");
        }
        dir.setPath(QDir::currentPath()+"/client");
        if(!dir.exists("database")) {
            dir.mkdir("database");
        }
        dir.setPath(QDir::currentPath()+"/client/database");
    }
    return dir.path();
}
//获取数据库文件路径
QString UserDataBase::getPath(enum PlatformType type,const QString &dbName)
{
    QString path = toDirectory(type) + "/" +dbName;
    if(path.indexOf(".db",0) == -1) {
        path.append(".db");
    }
    return path;
}
//数据库创建表
void UserDataBase::createTables(enum PlatformType type,const QSqlDatabase &database)
{
    if(type==SERVER) {
        UserServerTable table(database);
        table.addTable(UserServerTable::PARA_DEVICE);
        table.addTable(UserServerTable::PARA_POLLUTANT);
        table.addTable(UserServerTable::PARA_MANAGE);
        table.addTable(UserServerTable::PARA_ANALYZER);
        table.addTable(UserServerTable::POLL_REAL);
        table.addTable(UserServerTable::POLL_MINUTE);
        table.addTable(UserServerTable::POLL_HOUR);
        table.addTable(UserServerTable::POLL_DAY);
        table.addTable(UserServerTable::MANAGE_STATUS);
        table.addTable(UserServerTable::MANAGE_TIMMING);
    } else if(type==CLIENT) {
        UserClientTable table(database);
        table.addTable(UserClientTable::PARA_DEVICE);
        table.addTable(UserClientTable::PARA_SERVER);
        table.addTable(UserClientTable::PARA_POLLUTANT);
        table.addTable(UserClientTable::PARA_MANAGE);
        table.addTable(UserClientTable::PARA_ANALYZER);
        table.addTable(UserClientTable::POLL_REAL);
        table.addTable(UserClientTable::POLL_MINUTE);
        table.addTable(UserClientTable::POLL_HOUR);
        table.addTable(UserClientTable::POLL_DAY);
        table.addTable(UserClientTable::MANAGE_STATUS);
        table.addTable(UserClientTable::MANAGE_TIMMING);
    }
}
//链接数据库
QSqlDatabase UserDataBase::connectDatabase(enum PlatformType type,const QString &dbName)
{
    QSqlDatabase database;
    QString path = getPath(type,dbName);
    //判断数据库连接是否存在
    if(QSqlDatabase::contains(path)) {
        database = QSqlDatabase::database(path);
        if(!database.isOpen()) {
            database.open();
        }
    } else {
        //新增数据库连接
        database = QSqlDatabase::addDatabase("QSQLITE",path);
        database.setDatabaseName(path);
        //新增数据库文件并打开数据库
        if(!QFile::exists(path)) {
            database.open();
            createTables(type,database);
        } else {
            if(!database.isOpen()) {
                database.open();
            }
        }
    }
    return database;
}
//删除数据库
void UserDataBase::removeDatabase(enum PlatformType type,const QString &dbName)
{
    QString path = getPath(type,dbName);
    //删除数据库连接
    if(QSqlDatabase::contains(path)) {
        QSqlDatabase::removeDatabase(path);
    }
    //删除数据库文件
    if(QFile::exists(path)) {
        QFile::remove(path);
    }
}



