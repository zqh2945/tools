#include "userserverlistfile.h"
#include <QTextStream>
#include <QDebug>

UserServerListFile::UserServerListFile()
{

}

UserServerListFile::~UserServerListFile()
{

}
//获取服务器列表文件存放路径
QString UserServerListFile::toDirectory()
{
    QDir dir = QDir::current();
    if(!dir.exists("server")) {
        dir.mkdir("server");
    }
    dir.setPath(QDir::currentPath()+"/server");
    return dir.path();
}
//读取文件
QList<QStringList> UserServerListFile::readFile()
{
    QList<QStringList> list;
    QFile file(toDirectory() + "/ServerList.ini");
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QStringList textList = stream.readAll().split("\n",QString::SkipEmptyParts);
        for(int i=0;i<textList.count();i++) {
            list.append(textList.at(i).split(",",QString::SkipEmptyParts));
        }
        file.close();
    }
    return list;
}
//写入文件
void UserServerListFile::writeFile(const QList<QStringList> &list)
{
    QFile file(toDirectory() + "/ServerList.ini");
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);
        for(int i=0;i<list.count();i++) {
            QStringList info = list.at(i);
            if(info.count()>=2) {
                stream << info.at(0) << "," << info.at(1) << endl;
            }
        }
        file.close();
    }
}
//获取服务器信息列表
QList<QStringList> UserServerListFile::serverList()
{
    return readFile();
}
//增加一个服务器
void UserServerListFile::appendServer(const QString &ipaddr,int port)
{
    QList<QStringList> list = readFile();
    bool ok = true;
    for(int i=0;i<list.count();i++) {
        QStringList info = list.at(i);
        if(info.count()>=2 && info.at(0)==ipaddr && info.at(1).toInt()==port) {
            ok = false;
            break;
        }
    }
    if(ok) {
        QStringList info;
        info << ipaddr << QString::number(port);
        list.append(info);
    }
    writeFile(list);
}
//删除一个服务器
void UserServerListFile::deleteServer(const QString &ipaddr,int port)
{
    QList<QStringList> list = readFile();
    //删除服务器信息
    for(int i=0;i<list.count();i++) {
        QStringList info = list.at(i);
        if(info.count()>=2 && info.at(0)==ipaddr && info.at(1).toInt()==port) {
            list.removeAt(i);
            break;
        }
    }
    writeFile(list);
}

