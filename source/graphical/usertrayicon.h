#ifndef USERTRAYICON_H
#define USERTRAYICON_H

#include <QSystemTrayIcon>
#include "useractions.h"

class UserTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    UserTrayIcon(UserActions *actions,QObject *parent = 0);
    ~UserTrayIcon();
};

#endif // USERTRAYICON_H
