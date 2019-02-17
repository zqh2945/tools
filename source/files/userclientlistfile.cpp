#include "userclientlistfile.h"
#include <QTextStream>
#include <QDebug>

UserClientListFile::UserClientListFile()
{

}

UserClientListFile::~UserClientListFile()
{

}
//获取客户端列表文件存放路径
QString UserClientListFile::toDirectory()
{
    QDir dir = QDir::current();
    if(!dir.exists("client")) {
        dir.mkdir("client");
    }
    dir.setPath(QDir::currentPath()+"/client");
    return dir.path();
}
//读取文件
QList<QStringList> UserClientListFile::readFile()
{
    QList<QStringList> list;
    QFile file(toDirectory() + "/ClientList.ini");
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
void UserClientListFile::writeFile(const QList<QStringList> &list)
{
    QFile file(toDirectory() + "/ClientList.ini");
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);
        for(int i=0;i<list.count();i++) {
            QStringList info = list.at(i);
            if(info.count()>=4) {
                stream << info.at(0) << "," << info.at(1) << "," << info.at(2) << "," << info.at(3) << endl;
            }
        }
        file.close();
    }
}
//获取客户端信息列表
QList<QStringList> UserClientListFile::clientList()
{
    return readFile();
}
//增加一个客户端
void UserClientListFile::appendClient(const QStringList &baseInfo)
{
    QList<QStringList> list = readFile();
    bool ok = true;
    for(int i=0;i<list.count();i++) {
        if(list.at(i).count()>=2 && list.at(i).at(1)==baseInfo.at(1)) {
            ok = false;
            break;
        }
    }
    if(ok) {
        list.append(baseInfo);
    }
    writeFile(list);
}
//删除一个客户端
void UserClientListFile::deleteClient(const QString &mn)
{
    QList<QStringList> list = readFile();
    for(int i=0;i<list.count();i++) {
        if(list.at(i).count()>=2 && list.at(i).at(1)==mn) {
            list.removeAt(i);
            break;
        }
    }
    writeFile(list);
}
