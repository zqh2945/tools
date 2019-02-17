#include "userserverlogfile.h"
#include <QDebug>
#include <QFile>
#include <QDir>

UserServerLogFile::UserServerLogFile()
{

}

UserServerLogFile::~UserServerLogFile()
{

}
//跳转到服务器日志文件存放路径
QString UserServerLogFile::toDirectory()
{
    QDir dir = QDir::current();
    if(!dir.exists("server")) {
        dir.mkdir("server");
    }
    dir.setPath(QDir::currentPath() + "/server");
    if(!dir.exists("log")) {
        dir.mkdir("log");
    }
    dir.setPath(QDir::currentPath() + "/server/log");
    return dir.path();
}
//跳转到服务器监测点日志文件存放路径
QString UserServerLogFile::toDirectory(const QString &ipaddr,int port)
{
    QString folder = QString("%1(%2)").arg(ipaddr).arg(port);
    QDir dir = QDir::current();
    if(!dir.exists("server")) {
        dir.mkdir("server");
    }
    dir.setPath(QDir::currentPath() + "/server");
    if(!dir.exists("log")) {
        dir.mkdir("log");
    }
    dir.setPath(QDir::currentPath() + "/server/log");
    if(!dir.exists(folder)) {
        dir.mkdir(folder);
    }
    dir.setPath(QDir::currentPath() + "/server/log/" + folder);
    return dir.path();
}
//获取服务器存放路径
QString UserServerLogFile::getPath(const QString &ipaddr,int port)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    QString path = toDirectory() + "/" + filename;
    if(path.indexOf(".txt",0) == -1) {
        path.append(".txt");
    }
    return path;
}
//获取服务器监测点存放路径
QString UserServerLogFile::getPath(const QString &ipaddr,int port,const QString &mn)
{
    QString path = toDirectory(ipaddr,port) + "/" + mn;
    if(path.indexOf(".txt",0) == -1) {
        path.append(".txt");
    }
    return path;
}
//创建服务器日志文件
void UserServerLogFile::newLogFile(const QString &ipaddr,int port)
{
    QFile file(getPath(ipaddr,port));
    if(!file.exists()) {
        file.open(QFile::ReadWrite | QFile::Truncate);
        file.close();
    }
}
//创建服务器监测点日志文件
void UserServerLogFile::newLogFile(const QString &ipaddr,int port,const QString &mn)
{
    QFile file(getPath(ipaddr,port,mn));
    if(!file.exists()) {
        file.open(QFile::ReadWrite | QFile::Truncate);
        file.close();
    }
}
//创建服务器监测点日志文件
void UserServerLogFile::newLogFile(const QString &ipaddr,int port,const QStringList &mnList)
{
    newLogFile(ipaddr,port);
    for(int i=0;i<mnList.count();i++) {
        newLogFile(ipaddr,port,mnList.at(i));
    }
}
//删除服务器日志文件
void UserServerLogFile::removeLogFile(const QString &ipaddr,int port)
{
    //删除日志文件
    QFile file(getPath(ipaddr,port));
    if(file.exists()) {
        file.remove();
    }
    //删除日志目录
    QString folder = QString("%1(%2)").arg(ipaddr).arg(port);
    QDir dir(toDirectory()+"/"+folder);
    if(dir.exists()) {
        dir.removeRecursively();
    }
}
//删除服务器监测点日志文件
void UserServerLogFile::removeLogFile(const QString &ipaddr,int port,const QString &mn)
{
    //删除日志文件
    QFile file(getPath(ipaddr,port,mn));
    if(file.exists()) {
        file.remove();
    }
}
//读服务器日志文件
QString UserServerLogFile::readLog(const QString &ipaddr,int port)
{
    QString log;
    QFile file(getPath(ipaddr,port));
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        log = stream.readAll();
        file.close();
    }
    return log;
}
//读服务器监测点日志文件
QString UserServerLogFile::readLog(const QString &ipaddr,int port,const QString &mn)
{
    QString log;
    QFile file(getPath(ipaddr,port,mn));
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        log = stream.readAll();
        file.close();
    }
    return log;
}
//写服务器日志文件
void UserServerLogFile::writeLog(const QString &ipaddr,int port,const QString &log)
{
    QFile file(getPath(ipaddr,port));
    if(file.open(QFile::Append | QFile::Text)) {
        QTextStream stream(&file);
        stream << log << endl;
        file.close();
    }
}
//写服务器监测点日志文件
void UserServerLogFile::writeLog(const QString &ipaddr,int port,const QString &mn,const QString &log)
{
    QFile file(getPath(ipaddr,port,mn));
    if(file.open(QFile::Append | QFile::Text)) {
        QTextStream stream(&file);
        stream << log << endl;
        file.close();
    }
}

