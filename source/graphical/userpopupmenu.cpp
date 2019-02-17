#include "userpopupmenu.h"

UserPopupMenu::UserPopupMenu(UserActions *actions)
{
    Actions = actions;
}

UserPopupMenu::~UserPopupMenu()
{

}
//
void UserPopupMenu::popupServerMainMenu(int state)
{
    setServerMainEnabled(state);
    clear();
    addAction(Actions->actionEditServer());
    addAction(Actions->actionStartServer());
    addAction(Actions->actionSuspendServer());
    addAction(Actions->actionDeleteServer());
    exec(QCursor::pos());
}
//
void UserPopupMenu::setServerMainEnabled(int state)
{
    if(state==0) { //暂停状态
        Actions->setEditServerEnabled(true);
        Actions->setStartServerEnabled(true);
        Actions->setSuspendServerEnabled(false);
        Actions->setDeleteServerEnabled(true);
    } else if(state==1) { //启用状态
        Actions->setEditServerEnabled(false);
        Actions->setStartServerEnabled(false);
        Actions->setSuspendServerEnabled(true);
        Actions->setDeleteServerEnabled(false);
    }
}
//
void UserPopupMenu::popupServerSubMenu(int state)
{
    setServerSubEnabled(state);
    clear();
    addAction(Actions->actionEditSerDevice());
    addAction(Actions->actionAddSerDevice());
    addAction(Actions->actionDelSerDevice());
    exec(QCursor::pos());
}
//
void UserPopupMenu::setServerSubEnabled(int state)
{
    if(state==0) { //暂停状态
        Actions->setEditSerDeviceEnabled(true);
        Actions->setAddSerDeviceEnabled(true);
        Actions->setDelSerDeviceEnabled(true);
    } else if(state==1) { //启用状态
        Actions->setEditSerDeviceEnabled(false);
        Actions->setAddSerDeviceEnabled(false);
        Actions->setDelSerDeviceEnabled(false);
    }
}
//
void UserPopupMenu::popupClientMainMenu(int state)
{
    setClientMainEnabled(state);
    clear();
    addAction(Actions->actionEditClient());
    addAction(Actions->actionStartClient());
    addAction(Actions->actionSuspendClient());
    addAction(Actions->actionDeleteClient());
    exec(QCursor::pos());
}
//
void UserPopupMenu::setClientMainEnabled(int state)
{
    if(state==0) { //暂停状态
        Actions->setEditClientEnabled(true);
        Actions->setStartClientEnabled(true);
        Actions->setSuspendClientEnabled(false);
        Actions->setDeleteClientEnabled(true);
    } else if(state==1) { //启用状态
        Actions->setEditClientEnabled(false);
        Actions->setStartClientEnabled(false);
        Actions->setSuspendClientEnabled(true);
        Actions->setDeleteClientEnabled(false);
    }
}

//
void UserPopupMenu::popupClientSubMenu(int state)
{
    setClientSubEnabled(state);
    clear();
    exec(QCursor::pos());
}
//
void UserPopupMenu::setClientSubEnabled(int state)
{
    if(state==0) { //暂停状态

    } else if(state==1) { //启用状态

    }
}
