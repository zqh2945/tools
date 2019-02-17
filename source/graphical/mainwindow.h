#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QCloseEvent>
#include <QEvent>
#include "../source/graphical/useractions.h"
#include "../source/graphical/userpopupmenu.h"
#include "../source/graphical/userservertreewidget.h"
#include "../source/graphical/userclienttreewidget.h"
#include "../source/graphical/userstackedwidget.h"
#include "../source/graphical/userserverhandle.h"
#include "../source/graphical/userclienthandle.h"
#include "../source/graphical/userserverconfig.h"
#include "../source/graphical/userserverdeviceconfig.h"
#include "../source/graphical/userclientconfig.h"
#include "../source/graphical/usertrayicon.h"
#include "../source/files/userserverlistfile.h"
#include "../source/files/userserverdatabasefile.h"
#include "../source/files/userserverlogfile.h"
#include "../source/files/userclientlistfile.h"
#include "../source/files/userclientdatabasefile.h"
#include "../source/files/userclientlogfile.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();
    void createMenus();
    void createToolBars();
    void createWindow(QWidget *widget);

    virtual void closeEvent(QCloseEvent *event);
signals:
    void quit();
private:
    //菜单栏、弹出菜单、工具栏定义
    UserActions *Actions;
    QMenu *menuDevice;
    QMenu *menuHelp;
    UserPopupMenu *popupMenu;
    QToolBar *toolDevice;
    QToolBar *toolHelp;
    //主窗口对象定义
    UserServerTreeWidget *tabPageServer;
    UserClientTreeWidget *tabPageClient;
    QTabWidget *tabWidget;
    UserStackedWidget *stackWidget;
    UserServerHandle *pageServer;
    UserClientHandle *pageClient;
    UserTrayIcon *trayIcon;
    //动作对应对话框对象定义
    UserServerConfig *dialogCreateServer;
    UserServerConfig *dialogEditServer;
    UserServerDeviceConfig *dialogEditSerDevice;
    UserServerDeviceConfig *dialogAddSerDevice;
    UserClientConfig *dialogCreateClient;
    UserClientConfig *dialogEditClient;
private slots:
    void serverActionsTriggeredHandle(int index);
    void clientActionsTriggeredHandle(int index);
    void otherActionsTriggeredHandle(int index);

    void tabPageJump(int index);

    void tabPageServerMainItemClicked(int state);
    void tabPageServerSubItemClicked(int state);
    void tabPageServerMainItemRightClicked(int state);
    void tabPageServerSubItemRightClicked(int state);
    void pageServerLinkerBuildHandle(const QString &id,const QString &ipaddr,int port);
    void pageServerLinkerCloseHandle(const QString &id);

    void tabPageClientMainItemClicked(int state);
    void tabPageClientSubItemClicked(int state);
    void tabPageClientMainItemRightClicked(int state);
    void tabPageClientSubItemRightClicked(int state);
    void pageClientLinkerBuildHandle(const QString &id,const QString &ipaddr,int port);
    void pageClientLinkerCloseHandle(const QString &id);

    void trayIconActivatedHandle(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
