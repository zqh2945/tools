#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QObject>

class UserManage : public QObject
{
public:
    UserManage(QObject *parent);
    ~UserManage();
};

#endif // USERMANAGE_H
