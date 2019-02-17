#include "useractions.h"

UserActions::UserActions()
{
    /* 服务器动作 */
    createServerAction = new QAction(tr("创建服务器"));
    createServerAction->setIcon(QIcon(":/menu/Icons/menus/SerCreate.png"));

    editServerAction= new QAction(tr("编辑服务器"));
    editServerAction->setIcon(QIcon(":/menu/Icons/menus/SerEdit.png"));

    startServerAction = new QAction(tr("启动服务器"));
    startServerAction->setIcon(QIcon(":/menu/Icons/menus/SerStart.png"));

    suspendServerAction = new QAction(tr("暂停服务器"));
    suspendServerAction->setIcon(QIcon(":/menu/Icons/menus/SerSuspend.png"));

    deleteServerAction = new QAction(tr("删除服务器"));
    deleteServerAction->setIcon(QIcon(":/menu/Icons/menus/SerDelete.png"));

    editSerDeviceAction = new QAction(tr("编辑监测点"));
    editSerDeviceAction->setIcon(QIcon(":/menu/Icons/menus/DevEdit.png"));

    addSerDeviceAction = new QAction(tr("添加监测点"));
    addSerDeviceAction->setIcon(QIcon(":/menu/Icons/menus/DevAddition.png"));

    delSerDeviceAction = new QAction(tr("删除监测点"));
    delSerDeviceAction->setIcon(QIcon(":/menu/Icons/menus/DevDelete.png"));

    /* 客户端动作 */
    createClientAction = new QAction(tr("创建客户端"));
    createClientAction->setIcon(QIcon(":/menu/Icons/menus/CliCreate.png"));

    editClientAction = new QAction(tr("编辑客户端"));
    editClientAction->setIcon(QIcon(":/menu/Icons/menus/CliEdit.png"));

    startClientAction = new QAction(tr("启动客户端"));
    startClientAction->setIcon(QIcon(":/menu/Icons/menus/CliStart.png"));

    suspendClientAction = new QAction(tr("暂停客户端"));
    suspendClientAction->setIcon(QIcon(":/menu/Icons/menus/CliSuspend.png"));

    deleteClientAction = new QAction(tr("删除客户端"));
    deleteClientAction->setIcon(QIcon(":/menu/Icons/menus/CliDelete.png"));

    /* 其他动作 */
    restoreAction = new QAction(tr("还原"));


    quitAction = new QAction(tr("退出"));
    quitAction->setIcon(QIcon(":/menu/Icons/menus/Quit.png"));

    aboutAction = new QAction(tr("关于..."));
    aboutAction->setIcon(QIcon(":/menu/Icons/menus/About.png"));

    connect(createServerAction,SIGNAL(triggered()),this,SLOT(createServer()));
    connect(editServerAction,SIGNAL(triggered()),this,SLOT(editServer()));
    connect(startServerAction,SIGNAL(triggered()),this,SLOT(startServer()));
    connect(suspendServerAction,SIGNAL(triggered()),this,SLOT(suspendServer()));
    connect(deleteServerAction,SIGNAL(triggered()),this,SLOT(deleteServer()));
    connect(addSerDeviceAction,SIGNAL(triggered()),this,SLOT(addSerDevice()));
    connect(editSerDeviceAction,SIGNAL(triggered()),this,SLOT(editSerDevice()));
    connect(delSerDeviceAction,SIGNAL(triggered()),this,SLOT(delSerDevice()));

    connect(createClientAction,SIGNAL(triggered()),this,SLOT(createClient()));
    connect(editClientAction,SIGNAL(triggered()),this,SLOT(editClient()));
    connect(startClientAction,SIGNAL(triggered()),this,SLOT(startClient()));
    connect(suspendClientAction,SIGNAL(triggered()),this,SLOT(suspendClient()));
    connect(deleteClientAction,SIGNAL(triggered()),this,SLOT(deleteClient()));

    connect(restoreAction,SIGNAL(triggered()),this,SLOT(restore()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(quit()));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));
}

UserActions::~UserActions()
{
}
//设置服务器动作使能
void UserActions::setServerEnabled(bool ok)
{
    createServerAction->setEnabled(ok);
    startServerAction->setEnabled(ok);
    suspendServerAction->setEnabled(ok);
    deleteServerAction->setEnabled(ok);
}
//设置客户端动作使能
void UserActions::setClientEnabled(bool ok)
{
    createClientAction->setEnabled(ok);
    startClientAction->setEnabled(ok);
    suspendClientAction->setEnabled(ok);
    deleteClientAction->setEnabled(ok);
}

void UserActions::createServer()
{
    emit serverActionsTriggered(0);
}

void UserActions::editServer()
{
    emit serverActionsTriggered(1);
}

void UserActions::startServer()
{
    emit serverActionsTriggered(2);
}

void UserActions::suspendServer()
{
    emit serverActionsTriggered(3);
}

void UserActions::deleteServer()
{
    emit serverActionsTriggered(4);
}

void UserActions::addSerDevice()
{
    emit serverActionsTriggered(5);
}

void UserActions::editSerDevice()
{
    emit serverActionsTriggered(6);
}

void UserActions::delSerDevice()
{
    emit serverActionsTriggered(7);
}

void UserActions::createClient()
{
    emit clientActionsTriggered(0);
}

void UserActions::editClient()
{
    emit clientActionsTriggered(1);
}

void UserActions::startClient()
{
    emit clientActionsTriggered(2);
}

void UserActions::suspendClient()
{
    emit clientActionsTriggered(3);
}

void UserActions::deleteClient()
{
    emit clientActionsTriggered(4);
}

void UserActions::restore()
{
    emit otherActionsTriggered(0);
}

void UserActions::quit()
{
    emit otherActionsTriggered(1);
}

void UserActions::about()
{
    emit otherActionsTriggered(2);
}

