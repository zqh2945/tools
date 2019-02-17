#ifndef USERPOPUPMENU_H
#define USERPOPUPMENU_H

#include <QObject>
#include <QMenu>
#include "useractions.h"

class UserPopupMenu : public QMenu
{
public:
    UserPopupMenu(UserActions *actions);
    ~UserPopupMenu();
    void popupServerMainMenu(int state);
    void setServerMainEnabled(int state);

    void popupServerSubMenu(int state);
    void setServerSubEnabled(int state);

    void popupClientMainMenu(int state);
    void setClientMainEnabled(int state);

    void popupClientSubMenu(int state);
    void setClientSubEnabled(int state);
private:
    UserActions *Actions;
};

#endif // USERPOPUPMENU_H
