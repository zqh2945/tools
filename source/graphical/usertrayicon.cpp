#include "usertrayicon.h"
#include <QMenu>

UserTrayIcon::UserTrayIcon(UserActions *actions,QObject *parent) : QSystemTrayIcon(parent)
{
    setIcon(QIcon(":/title/Icons/titles/title.png"));
    setToolTip(tr("《环境在线监控(监测)系统数据传输标准》调试工具"));
    show();
    //showMessage(tr("提示"),tr("《环境在线监控(监测)系统数据传输标准》调试工具"),QSystemTrayIcon::Information,1000);
    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addAction(actions->actionRestore());
    trayIconMenu->addAction(actions->actionQuit());
    setContextMenu(trayIconMenu);
}

UserTrayIcon::~UserTrayIcon()
{
}

