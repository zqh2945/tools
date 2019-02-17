#include "userclientlogfile.h"
#include <QDebug>
#include <QDir>
#include <QFile>

UserClientLogFile::UserClientLogFile()
{

}

UserClientLogFile::~UserClientLogFile()
{

}
//跳转到客户端日志文件存放路径
QString UserClientLogFile::toDirectory()
{
    QDir dir = QDir::current();
    if(!dir.exists("client")) {
        dir.mkdir("client");
    }
    dir.setPath(QDir::currentPath() + "/client");
    if(!dir.exists("log")) {
        dir.mkdir("log");
    }
    dir.setPath(QDir::currentPath() + "/client/log");
    return dir.path();
}
//跳转到客户端日志文件存放路径
QString UserClientLogFile::toDirectory(const QString &mn)
{
    QDir dir = QDir::current();
    if(!dir.exists("client")) {
        dir.mkdir("client");
    }
    dir.setPath(QDir::currentPath() + "/client");
    if(!dir.exists("log")) {
        dir.mkdir("log");
    }
    dir.setPath(QDir::currentPath() + "/client/log");
    if(!dir.exists(mn)) {
        dir.mkdir(mn);
    }
    dir.setPath(QDir::currentPath() + "/client/log/" + mn);
    return dir.path();
}
//获取客户端存放路径
QString UserClientLogFile::getPath(const QString &mn)
{
    QString path = toDirectory() + "/" + mn;
    if(path.indexOf(".txt",0) == -1) {
        path.append(".txt");
    }
    return path;
}
//获取客户端存放路径
QString UserClientLogFile::getPath(const QString &mn,const QString &ipaddr,int port)
{
    QString filename = QString("%1(%2)").arg(ipaddr).arg(port);
    QString path = toDirectory(mn) + "/" + filename;
    if(path.indexOf(".txt",0) == -1) {
        path.append(".txt");
    }
    return path;
}
//创建客户端日志文件
void UserClientLogFile::newLogFile(const QString &mn)
{
    QFile file(getPath(mn));
    if(!file.exists()) {
        file.open(QFile::ReadWrite | QFile::Truncate);
        file.close();
    }
}
//创建客户端日志文件
void UserClientLogFile::newLogFile(const QString &mn,const QString &ipaddr,int port)
{
    QFile file(getPath(mn,ipaddr,port));
    if(!file.exists()) {
        file.open(QFile::ReadWrite | QFile::Truncate);
        file.close();
    }
}
//创建客户端日志文件
void UserClientLogFile::newLogFile(const QString &mn,const QList<QStringList> &serList)
{
    newLogFile(mn);
    for(int i=0;i<serList.count();i++) {
        if(serList.at(i).count()>=3 && serList.at(i).first().toInt()==1) {
            newLogFile(mn,serList.at(i).at(1),serList.at(i).at(2).toInt());
        }
    }
}

//删除客户端日志文件
void UserClientLogFile::removeLogFile(const QString &filename)
{
    //删除日志文件
    QFile file(getPath(filename));
    if(file.exists()) {
        file.remove();
    }
    //删除日志目录
    QDir dir(toDirectory()+"/"+filename);
    if(dir.exists()) {
        dir.removeRecursively();
    }
}
//删除客户端日志文件
void UserClientLogFile::removeLogFile(const QString &mn,const QString &ipaddr,int port)
{
    //删除日志文件
    QFile file(getPath(mn,ipaddr,port));
    if(file.exists()) {
        file.remove();
    }
}
//读客户端日志文件
QString UserClientLogFile::readLog(const QString &filename)
{
    QString log;
    QFile file(getPath(filename));
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        log = stream.readAll();
        file.close();
    }
    return log;
}
//读客户端日志文件
QString UserClientLogFile::readLog(const QString &mn,const QString &ipaddr,int port)
{
    QString log;
    QFile file(getPath(mn,ipaddr,port));
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        log = stream.readAll();
        file.close();
    }
    return log;
}
//写客户端日志文件
void UserClientLogFile::writeLog(const QString &filename,const QString &log)
{
    QFile file(getPath(filename));
    if(file.open(QFile::Append | QFile::Text)) {
        QTextStream stream(&file);
        stream << log << endl;
        file.close();
    }
}
//写客户端日志文件
void UserClientLogFile::writeLog(const QString &mn,const QString &ipaddr,int port,const QString &log)
{
    QFile file(getPath(mn,ipaddr,port));
    if(file.open(QFile::Append | QFile::Text)) {
        QTextStream stream(&file);
        stream << log << endl;
        file.close();
    }
}



