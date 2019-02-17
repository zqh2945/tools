#ifndef USERCLIENTLISTFILE_H
#define USERCLIENTLISTFILE_H

#include <QDir>
#include <QFile>
#include <QString>

class UserClientListFile
{
public:
    UserClientListFile();
    ~UserClientListFile();
    static QList<QStringList> clientList();
    static void appendClient(const QStringList &baseInfo);
    static void deleteClient(const QString &mn);
private:
    static QString toDirectory();
    static QList<QStringList> readFile();
    static void writeFile(const QList<QStringList> &list);
};

#endif // USERCLIENTLISTFILE_H
