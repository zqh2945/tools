#include "mainwindow.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowTitle(tr("《环境在线监控(监测)系统数据传输标准》调试工具"));
    setWindowIcon(QIcon(":/title/Icons/title.png"));
    setCentralWidget(new QWidget());
    resize(1080,720);
    //菜单栏、工具栏、主窗口创建
    createActions();
    createMenus();
    createToolBars();
    createWindow(centralWidget());
    //弹出菜单和后台运行(最小化到系统托盘)
    popupMenu = new UserPopupMenu(Actions);
    trayIcon = new UserTrayIcon(Actions,this);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)), \
            this,SLOT(trayIconActivatedHandle(QSystemTrayIcon::ActivationReason)));
    //动作对应对话框对象创建
    dialogCreateServer = new UserServerConfig(UserServerConfig::NEW,this);
    dialogEditServer = new UserServerConfig(UserServerConfig::EDIT,this);
    dialogAddSerDevice = new UserServerDeviceConfig(UserServerDeviceConfig::NEW,this);
    dialogEditSerDevice = new UserServerDeviceConfig(UserServerDeviceConfig::EDIT,this);
    //dialogCreateClient = new UserClientConfig(UserClientConfig::NEW,this);
    dialogEditClient = new UserClientConfig(UserClientConfig::EDIT,this);
}

MainWindow::~MainWindow()
{

}
//关闭到托盘
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}
//创建菜单栏和工具栏的动作
void MainWindow::createActions()
{
    Actions = new UserActions();
    Actions->setServerEnabled(true);
    Actions->setClientEnabled(false);
    //信号与槽链接
    connect(Actions,SIGNAL(serverActionsTriggered(int)),this,SLOT(serverActionsTriggeredHandle(int)));
    connect(Actions,SIGNAL(clientActionsTriggered(int)),this,SLOT(clientActionsTriggeredHandle(int)));
    connect(Actions,SIGNAL(otherActionsTriggered(int)),this,SLOT(otherActionsTriggeredHandle(int)));
}
//创建菜单栏
void MainWindow::createMenus()
{
    menuDevice = menuBar()->addMenu(tr("设备管理"));
    menuDevice->addAction(Actions->actionCreateServer());
    menuDevice->addAction(Actions->actionStartServer());
    menuDevice->addAction(Actions->actionSuspendServer());
    menuDevice->addAction(Actions->actionDeleteServer());
    menuDevice->addSeparator();
    menuDevice->addAction(Actions->actionCreateClient());
    menuDevice->addAction(Actions->actionStartClient());
    menuDevice->addAction(Actions->actionSuspendClient());
    menuDevice->addAction(Actions->actionDeleteClient());
    menuDevice->addSeparator();
    menuDevice->addAction(Actions->actionQuit());
    menuHelp = menuBar()->addMenu(tr("帮助"));
    menuHelp->addAction(Actions->actionAbout());
}
//创建工具栏
void MainWindow::createToolBars()
{
    toolDevice = addToolBar(tr("设备管理"));
    toolDevice->clear();
    toolDevice->addAction(Actions->actionCreateServer());
    toolDevice->addAction(Actions->actionStartServer());
    toolDevice->addAction(Actions->actionSuspendServer());
    toolDevice->addAction(Actions->actionDeleteServer());
    toolHelp = addToolBar(tr("关于"));
    toolHelp->clear();
    toolHelp->addAction(Actions->actionAbout());
}
//创建主窗口
void MainWindow::createWindow(QWidget *widget)
{
    //服务器和客户端树形组件
    tabPageServer = new UserServerTreeWidget();
    tabPageServer->initialization();
    tabPageClient = new UserClientTreeWidget();
    tabPageClient->initialization();
    tabWidget = new QTabWidget();
    tabWidget->setFixedWidth(290);
    tabWidget->addTab(tabPageServer,tr("服务器列表"));
    tabWidget->addTab(tabPageClient,tr("数采仪列表"));
    tabWidget->setCurrentWidget(tabPageServer);
    //服务器和客户端堆叠组件
    pageServer = new UserServerHandle();
    pageServer->initialization();
    pageClient = new UserClientHandle();
    pageClient->initialization();
    stackWidget = new UserStackedWidget();
    stackWidget->setFixedWidth(800);
    stackWidget->addWidget(pageServer);
    stackWidget->addWidget(pageClient);
    stackWidget->setCurrentWidget(pageServer);
    //组件布局
    QHBoxLayout *mainLayout = new QHBoxLayout(widget);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(stackWidget);
    mainLayout->setSpacing(4);
    mainLayout->setMargin(4);
    //树形组件信号与槽链接
    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabPageJump(int)));
    //服务器组件信号与槽链接
    connect(tabPageServer,SIGNAL(mainItemClicked(int)),this,SLOT(tabPageServerMainItemClicked(int)));
    connect(tabPageServer,SIGNAL(subItemClicked(int)),this,SLOT(tabPageServerSubItemClicked(int)));
    connect(tabPageServer,SIGNAL(mainItemRightClicked(int)),this,SLOT(tabPageServerMainItemRightClicked(int)));
    connect(tabPageServer,SIGNAL(subItemRightClicked(int)),this,SLOT(tabPageServerSubItemRightClicked(int)));
    connect(pageServer,SIGNAL(linkerBuild(QString,QString,int)),this,SLOT(pageServerLinkerBuildHandle(QString,QString,int)));
    connect(pageServer,SIGNAL(linkerClose(QString)),this,SLOT(pageServerLinkerCloseHandle(QString)));
    //客户端组件信号与槽链接
    connect(tabPageClient,SIGNAL(mainItemClicked(int)),this,SLOT(tabPageClientMainItemClicked(int)));
    connect(tabPageClient,SIGNAL(subItemClicked(int)),this,SLOT(tabPageClientSubItemClicked(int)));
    connect(tabPageClient,SIGNAL(mainItemRightClicked(int)),this,SLOT(tabPageClientMainItemRightClicked(int)));
    connect(tabPageClient,SIGNAL(subItemRightClicked(int)),this,SLOT(tabPageClientSubItemRightClicked(int)));
    connect(pageClient,SIGNAL(linkerBuild(QString,QString,int)),this,SLOT(pageClientLinkerBuildHandle(QString,QString,int)));
    connect(pageClient,SIGNAL(linkerClose(QString)),this,SLOT(pageClientLinkerCloseHandle(QString)));
}

//服务器动作触发槽函数
void MainWindow::serverActionsTriggeredHandle(int index)
{
    if(index==0) { //创建服务器
        if(dialogCreateServer->exec()==QDialog::Accepted) {
            QString ipaddr = dialogCreateServer->ipaddr();
            int port = dialogCreateServer->port();
            if(!tabPageServer->findMainItem(ipaddr,port)) {
                qDebug() << "server create start";
                UserServerListFile::appendServer(ipaddr,port); //添加服务器到服务器列表文件
                qDebug() << 1;
                tabPageServer->addMainItem(ipaddr,port); //添加服务器到树型列表
                qDebug() << 2;
                pageServer->createServer(ipaddr,port); //创建服务器
                qDebug() << 3;
                QList<QStringList> baseInfoList = dialogCreateServer->devicesList();
                UserServerDatabaseFile::setDeviceBaseInfoList(ipaddr,port,baseInfoList); //添加服务器监测点基本信息到数据库
                qDebug() << 4;
                tabPageServer->addMainAllSubItem(ipaddr,port,baseInfoList); //添加服务器监测点到树型列表
                qDebug() << 5;
                pageServer->createServerAllDevice(ipaddr,port,baseInfoList); //创建服务器监测点
                qDebug() << 6;
                QStringList mnList = dialogCreateServer->deviceCodeList();
                UserServerLogFile::newLogFile(ipaddr,port,mnList); //创建服务器日志文件
                qDebug() << "server create end";
            } else {
                QString address = dialogCreateServer->address();
                QMessageBox::information(this,tr("提示"),tr("服务器(%1)已存在!").arg(address));
            }
        }
    } else if(index==1) { //编辑服务器
        QTreeWidgetItem *item = tabPageServer->currentItem();
        if(tabPageServer->isMainItem(item)) {
            if(tabPageServer->serverState()==0) { //暂停状态
                QString ipaddr = tabPageServer->serverIPAddr();
                int port = tabPageServer->serverPort();
                QString address = tabPageServer->address();

                dialogEditServer->setWindowTitle(QString("服务器(%1)编辑").arg(address));
                dialogEditServer->setServer(ipaddr,port);
                dialogEditServer->setDeviceList(UserServerDatabaseFile::deviceBaseInfoList(ipaddr,port));
                if(dialogEditServer->exec()==QDialog::Accepted) {
                    qDebug() << "server edit start";
                    QList<QStringList> baseInfoList = dialogEditServer->devicesList();
                    UserServerDatabaseFile::delDeviceConfigList(ipaddr,port);
                    UserServerDatabaseFile::setDeviceBaseInfoList(ipaddr,port,baseInfoList); //添加服务器监测点基本信息到数据库
                    qDebug() << 1;
                    tabPageServer->deleteMainAllSubItem(item); //删除服务器的所有监测点
                    tabPageServer->addMainAllSubItem(ipaddr,port,baseInfoList); //添加服务器监测点到树型列表
                    qDebug() << 2;
                    pageServer->deleteServerAllDevice(ipaddr,port);
                    pageServer->createServerAllDevice(ipaddr,port,baseInfoList); //创建服务器监测点
                    qDebug() << 3;
                    QStringList mnList = dialogEditServer->deviceCodeList();
                    UserServerLogFile::removeLogFile(ipaddr,port);
                    UserServerLogFile::newLogFile(ipaddr,port,mnList); //创建服务器监测点日志文件
                    qDebug() << "server edit end";
                }
            } else {
                QString address = tabPageServer->address();
                QMessageBox::information(this,tr("提示"),tr("服务器(%1)正在使用，不允许编辑！").arg(address));
            }
        }
    } else if(index==2) { //启动服务器
        QTreeWidgetItem *item = tabPageServer->currentItem();
        if(tabPageServer->isMainItem(item)) {
            if(tabPageServer->serverState()==0) { //暂停状态
                QString ipaddr = tabPageServer->serverIPAddr();
                int port = tabPageServer->serverPort();

                tabPageServer->startMainItem(item);
                QStringList mnList = tabPageServer->serverDeviceList();
                pageServer->startServer(ipaddr,port,mnList);
            } else {
                QString address = tabPageServer->address();
                QMessageBox::information(this,tr("提示"),tr("服务器(%1)已启用！").arg(address));
            }
        }
    } else if(index==3) { //暂停服务器
        QTreeWidgetItem *item = tabPageServer->currentItem();
        if(tabPageServer->isMainItem(item)) {
            if(tabPageServer->serverState()==1) { //启用状态
                QString ipaddr = tabPageServer->serverIPAddr();
                int port = tabPageServer->serverPort();

                tabPageServer->stopMainItem(item);
                pageServer->stopServer(ipaddr,port);
            } else {
                QString address = tabPageServer->address();
                QMessageBox::information(this,tr("提示"),tr("服务器(%1)已暂停！").arg(address));
            }
        }
    } else if(index==4) { //删除服务器
        QTreeWidgetItem *item = tabPageServer->currentItem();
        if(tabPageServer->isMainItem(item)) {
            if(tabPageServer->serverState()==0) { //暂停状态
                QString ipaddr = tabPageServer->serverIPAddr();
                int port = tabPageServer->serverPort();

                tabPageServer->deleteMainItem(item); //删除服务器从树型列表
                pageServer->deleteServerAllDevice(ipaddr,port); //删除服务器监测点
                pageServer->deleteServer(ipaddr,port); //删除服务器
                UserServerListFile::deleteServer(ipaddr,port); //删除服务器从服务器列表文件
                UserServerDatabaseFile::removeDatabase(ipaddr,port); //删除服务器数据库
                UserServerLogFile::removeLogFile(ipaddr,port); //删除服务器日志文件
            } else {
                QString address = tabPageServer->address();
                QMessageBox::information(this,tr("提示"),tr("服务器(%1)正在使用，不能被删除！").arg(address));
            }

        }
    } else if(index==5) { //增加服务器监测点
        if(tabPageServer->serverState()==0) { //暂停状态
            QString ipaddr = tabPageServer->serverIPAddr();
            int port = tabPageServer->serverPort();
            if(dialogAddSerDevice->exec()==QDialog::Accepted) {
                QString mn = dialogAddSerDevice->deviceCode();
                if(!tabPageServer->findSubItem(ipaddr,port,mn)) {
                    QStringList baseInfo = dialogAddSerDevice->deviceBaseInfo();
                    tabPageServer->addSubItem(ipaddr,port,baseInfo); //添加服务器监测点到树型列表
                    pageServer->createDevice(ipaddr,port,baseInfo); //创建服务器监测点

                    QStringList config = dialogAddSerDevice->deviceConfig();
                    UserServerDatabaseFile::setDeviceConfig(ipaddr,port,config); //添加服务器监测点配置信息到数据库

                    QList<QStringList> pollList = dialogAddSerDevice->pollutantConfigList();
                    UserServerDatabaseFile::setPollutantConfigList(ipaddr,port,mn,pollList); //添加污染监测因子配置列表到数据库

                    UserServerLogFile::newLogFile(ipaddr,port,mn); //创建服务器监测点日志文件
                } else {
                    QMessageBox::information(this,tr("提示"),tr("监测点(%1)已存在!").arg(mn));
                }
            }
        } else {
            QString address = tabPageServer->address();
            QMessageBox::information(this,tr("提示"),tr("服务器(%1)正在使用，不允许添加监测点！").arg(address));
        }
    } else if(index==6) { //编辑服务器监测点
        QTreeWidgetItem *item = tabPageClient->currentItem();
        if(tabPageServer->isSubItem(item)) {
            if(tabPageServer->serverState()==0) { //暂停状态
                QString ipaddr = tabPageServer->serverIPAddr();
                int port = tabPageServer->serverPort();
                QString mn = tabPageServer->deviceCode();

                dialogEditSerDevice->setDeviceConfig(UserServerDatabaseFile::deviceConfig(ipaddr,port,mn));
                dialogEditSerDevice->setPollutantConfigList(UserServerDatabaseFile::pollutantConfigList(ipaddr,port,mn));
                dialogEditSerDevice->setWindowTitle(QString("监测点(%1)编辑").arg(mn));
                if(dialogEditSerDevice->exec()==QDialog::Accepted) {
                    QStringList baseInfo = dialogEditSerDevice->deviceBaseInfo();
                    tabPageServer->editSubItem(ipaddr,port,baseInfo); //更新服务器监测点

                    QStringList config = dialogEditSerDevice->deviceConfig();
                    UserServerDatabaseFile::setDeviceConfig(ipaddr,port,config); //更新服务器配置信息到数据库

                    QList<QStringList> pollList = dialogEditSerDevice->pollutantConfigList();
                    UserServerDatabaseFile::delPollutantConfigList(ipaddr,port,mn); //删除监测点污染监测因子
                    UserServerDatabaseFile::setPollutantConfigList(ipaddr,port,mn,pollList); //添加监测点吴然监测因子
                }
            } else {
                QString address = tabPageServer->address();
                QMessageBox::information(this,tr("提示"),tr("服务器(%1)正在使用，不允许编辑监测点！").arg(address));
            }
        }
    } else if(index==7) { //删除服务器监测点
        QTreeWidgetItem *item = tabPageClient->currentItem();
        if(tabPageServer->isSubItem(item)) {
            if(tabPageServer->serverState()==0) { //暂停状态
                QString ipaddr = tabPageServer->serverIPAddr();
                int port = tabPageServer->serverPort();
                QString mn = tabPageServer->deviceCode();

                tabPageServer->deleteSubItem(item); //从树型列表删除服务器监测点
                pageServer->deleteDevice(ipaddr,port,mn); //删除服务器监测点
                UserServerDatabaseFile::delDeviceConfig(ipaddr,port,mn); //从数据库删除服务器监测点
                UserServerDatabaseFile::delPollutantConfigList(ipaddr,port,mn); //从数据库删除服务器监测点污染监测因子
                UserServerLogFile::removeLogFile(ipaddr,port,mn); //删除服务器监测点日志文件
            } else {
                QString address = tabPageServer->address();
                QMessageBox::information(this,tr("提示"),tr("服务器(%1)正在使用，不允许删除监测点！").arg(address));
            }
        }
    }
}
//客户端动作触发槽函数
void MainWindow::clientActionsTriggeredHandle(int index)
{
    if(index==0) { //创建客户端
        if(dialogCreateClient->exec()==QDialog::Accepted) {
            QString mn = dialogCreateClient->deviceCode();
            if(!tabPageClient->findMainItem(mn)) {
                qDebug() << "client create start";
                QStringList baseInfo = dialogCreateClient->deviceBaseInfo();
                UserClientListFile::appendClient(baseInfo); //添加客户端到客户端列表文件
                qDebug() << 1;
                QStringList config = dialogCreateClient->deviceConfig();
                UserClientDatabaseFile::setDeviceConfig(mn,config); //添加客户端数据库
                qDebug() << 2;
                QList<QStringList> socketList = dialogCreateClient->serverConfigList();
                UserClientDatabaseFile::setSocketConfigList(mn,socketList); //添加客户端链接槽到数据库
                qDebug() << 3;
                QList<QStringList> pollutantList = dialogCreateClient->pollutantConfigList();
                UserClientDatabaseFile::setPollutantConfigList(mn,pollutantList); //添加污染监测因子到客户端数据库
                qDebug() << 4;
                tabPageClient->addMainItem(baseInfo); //添加客户端到树型列表
                qDebug() << 5;
                pageClient->createDevice(baseInfo); //创建客户端
                qDebug() << 6;
                tabPageClient->addMainAllSubItem(mn,socketList); //添加客户端链接槽到树型列表
                qDebug() << 7;
                pageClient->createDeviceAllSocket(baseInfo,socketList); //创建客户端链接槽
                qDebug() << 8;
                UserClientLogFile::newLogFile(mn,socketList); //创建客户端日志文件
                qDebug() << "client create End";
            } else {
                QMessageBox::information(this,tr("提示"),tr("客户端(%1)已存在!").arg(mn));
            }
        }
    } else if(index==1) { //编辑客户端
        QTreeWidgetItem *item = tabPageClient->currentItem();
        if(tabPageClient->isMainItem(item)) {
            QString mn = tabPageClient->deviceCode();
            if(tabPageClient->deviceState()==0) { //暂停状态
                dialogEditClient->setWindowTitle(QString("客户端(%1)编辑").arg(mn));
                dialogEditClient->setDeviceConfig(UserClientDatabaseFile::deviceConfig(mn));
                dialogEditClient->setServerConfigList(UserClientDatabaseFile::socketConfigList(mn));
                dialogEditClient->setPollutantConfigList(UserClientDatabaseFile::pollutantConfigList(mn));
                if(dialogEditClient->exec()==QDialog::Accepted) {
                    qDebug() << "client edit start";
                    QStringList config = dialogEditClient->deviceConfig();
                    UserClientDatabaseFile::setDeviceConfig(mn,config); //更新客户端配置到数据库
                    qDebug() << 1;
                    QList<QStringList> socketList = dialogEditClient->serverConfigList();
                    UserClientDatabaseFile::delSocketConfigList(mn); //从数据库删除客户端链接槽配置
                    UserClientDatabaseFile::setSocketConfigList(mn,socketList); //添加客户端链接槽到数据库
                    qDebug() << 2;
                    QList<QStringList> pollutantList = dialogEditClient->pollutantConfigList();
                    UserClientDatabaseFile::delPollutantConfigList(mn); //从数据库中删除客户端污染监测因子配置
                    UserClientDatabaseFile::setPollutantConfigList(mn,pollutantList); //添加客户端污染监测因子配置到数据库
                    qDebug() << 3;
                    tabPageClient->deleteMainAllSubItem(item); //从树型列表删除客户端链接槽
                    tabPageClient->addMainAllSubItem(mn,socketList); //添加客户端链接槽到树型列表
                    qDebug() << 4;
                    QStringList baseInfo = dialogEditClient->deviceBaseInfo();
                    pageClient->deleteDeviceAllSocket(mn); //删除客户端链接槽
                    pageClient->createDeviceAllSocket(baseInfo,socketList); //创建客户端链接槽
                    qDebug() << 5;
                    UserClientLogFile::removeLogFile(mn); //删除客户端日志文件
                    UserClientLogFile::newLogFile(mn,socketList); //新建客户端日志文件
                    qDebug() << "client edit end";
                }
            } else {
                QMessageBox::information(this,tr("提示"),tr("数采仪(%1)已启用，不允许编辑！").arg(mn));
            }
        }
    } else if(index==2) { //启动客户端
        QTreeWidgetItem *item = tabPageClient->currentItem();
        if(tabPageClient->isMainItem(item)) {
            QString mn = tabPageClient->deviceCode();
            if(tabPageClient->deviceState()==0) { //暂停状态
                QList<QStringList> serverList = tabPageClient->deviceServerList();
                tabPageClient->startMainItem(item);
                pageClient->startDevice(mn,serverList);
                pageClient->startDeviceAllSocket(mn,serverList);
            } else {
                QMessageBox::information(this,tr("提示"),tr("数采仪(%1)已启用！").arg(mn));
            }
        }
    } else if(index==3) { //暂停客户端
        QTreeWidgetItem *item = tabPageClient->currentItem();
        if(tabPageClient->isMainItem(item)) {
            QString mn = tabPageClient->deviceCode();
            if(tabPageClient->deviceState()==1) { //启用状态
                QList<QStringList> serverList = tabPageClient->deviceServerList();
                tabPageClient->stopMainItem(item);
                pageClient->stopDeviceAllSocket(mn,serverList);
                pageClient->stopDevice(mn);
            } else {
                QMessageBox::information(this,tr("提示"),tr("客户端(%1)已暂停！").arg(mn));
            }
        }
    } else if(index==4) { //删除客户端
        QTreeWidgetItem *item = tabPageClient->currentItem();
        if(tabPageClient->isMainItem(item)) {
            QString mn = tabPageClient->deviceCode();
            if(tabPageClient->deviceState()==0) { //暂停状态
                tabPageClient->deleteMainItem(item); //删除客户端从树型列表
                pageClient->deleteDeviceAllSocket(mn); //删除客户端链接槽
                pageClient->deleteDevice(mn); //删除客户端
                UserClientListFile::deleteClient(mn); //删除客户端从客户端列表文件
                UserClientDatabaseFile::removeDatabase(mn); //删除客户端数据库
                UserClientLogFile::removeLogFile(mn); //删除客户端日志文件
            } else {
                 QMessageBox::information(this,tr("提示"),tr("客户端(%1)正在使用，不能被删除！").arg(mn));
            }
        }
    }
}
//其他动作触发槽函数
void MainWindow::otherActionsTriggeredHandle(int index)
{
    if(index==0) {
        setWindowState(Qt::WindowActive);
        setGeometry(geometry());
        showNormal();
    } else if(index==1) {
        emit quit(); //产生一个退出信号
    } else if(index==2) {
        QString info;
        info.append("污染源在线监测(监控)系统数据传输标准调试工具\r\n");
        info.append("使用标准：HJ/T212-2005和HJ/T212-2016\r\n");
        info.append("版本号：0.1.0\r\n");
        QMessageBox::about(this,tr("关于HJ212"),tr("%1").arg(info));
    }
}

//属性页切换槽函数
void MainWindow::tabPageJump(int index)
{
    if(index==0) {
        Actions->setServerEnabled(true);
        Actions->setClientEnabled(false);
        toolDevice->clear();
        toolDevice->addAction(Actions->actionCreateServer());
        toolDevice->addAction(Actions->actionStartServer());
        toolDevice->addAction(Actions->actionSuspendServer());
        toolDevice->addAction(Actions->actionDeleteServer());
        stackWidget->setCurrentWidget(pageServer);
    } else if(index==1) {
        Actions->setServerEnabled(false);
        Actions->setClientEnabled(true);
        toolDevice->clear();
        toolDevice->addAction(Actions->actionCreateClient());
        toolDevice->addAction(Actions->actionStartClient());
        toolDevice->addAction(Actions->actionSuspendClient());
        toolDevice->addAction(Actions->actionDeleteClient());
        stackWidget->setCurrentWidget(pageClient);
    }
}

//服务器树型视图主项单击槽函数
void MainWindow::tabPageServerMainItemClicked(int state)
{
    popupMenu->setServerMainEnabled(state);
    pageServer->setServerAddress("0.0.0.0",0);
    pageServer->setClientAddress("0.0.0.0",0);
    pageServer->setCurrentServer(tabPageServer->serverIPAddr(),tabPageServer->serverPort());
}
//服务器树型视图子项单击槽函数
void MainWindow::tabPageServerSubItemClicked(int state)
{
    popupMenu->setServerSubEnabled(state);
    QStringList baseInfo = tabPageServer->deviceBaseInfo();
    if(baseInfo.count()>=4) {
        pageServer->setVersion(baseInfo.at(0).toInt());
        pageServer->setDeviceMN(baseInfo.at(1));
        pageServer->setDevicePW(baseInfo.at(2));
        pageServer->setDeviceST(baseInfo.at(3));
    }
    pageServer->setServerAddress(tabPageServer->serverIPAddr(),tabPageServer->serverPort());
    pageServer->setClientAddress(tabPageServer->deviceIPAddr(),tabPageServer->devicePort());
    pageServer->setCurrentDevice(tabPageServer->serverIPAddr(),tabPageServer->serverPort(),tabPageServer->deviceCode());
}
//服务器树型视图主项右击参函数
void MainWindow::tabPageServerMainItemRightClicked(int state)
{
    popupMenu->popupServerMainMenu(state);
}
//服务器树型视图子项右击槽函数
void MainWindow::tabPageServerSubItemRightClicked(int state)
{
    popupMenu->popupServerSubMenu(state);
}
//服务器监测点链接建立槽函数
void MainWindow::pageServerLinkerBuildHandle(const QString &id,const QString &ipaddr,int port)
{
    int ps = id.indexOf(':',0);
    int pd = id.indexOf('<',0);
    int pe = id.indexOf('>',0);
    if(ps!=-1 && pd!=-1 && pe !=-1) {
        QString srcIP = id.left(ps);
        int srcPort = id.mid(ps+1,pd-ps-1).toInt();
        QString mn = id.mid(pd+1,pe-pd-1);
        tabPageServer->connectSubItem(srcIP,srcPort,mn,ipaddr,port);
    }
}
//服务器监测点链接断开槽函数
void MainWindow::pageServerLinkerCloseHandle(const QString &id)
{
    int ps = id.indexOf(':',0);
    int pd = id.indexOf('<',0);
    int pe = id.indexOf('>',0);
    if(ps!=-1 && pd!=-1 && pe !=-1) {
        QString ipaddr = id.left(ps);
        int port = id.mid(ps+1,pd-ps-1).toInt();
        QString mn = id.mid(pd+1,pe-pd-1);
        tabPageServer->disconnectSubItem(ipaddr,port,mn);
    }
}

//客户端树型视图主项单击槽函数
void MainWindow::tabPageClientMainItemClicked(int state)
{
    popupMenu->setClientMainEnabled(state);
    QStringList baseInfo = tabPageClient->deviceBaseInfo();
    if(baseInfo.count()>=4) {
        pageClient->setVersion(baseInfo.at(0).toInt());
        pageClient->setDeviceMN(baseInfo.at(1));
        pageClient->setDevicePW(baseInfo.at(2));
        pageClient->setDeviceST(baseInfo.at(3));
    }
    pageClient->setClientAddress("0.0.0.0",0);
    pageClient->setServerAddress("0.0.0.0",0);
    pageClient->setCurrentDevice(tabPageClient->deviceCode());
}
//客户端树型视图子项单击槽函数
void MainWindow::tabPageClientSubItemClicked(int state)
{
    popupMenu->setClientSubEnabled(state);
    QStringList baseInfo = tabPageClient->deviceBaseInfo();
    if(baseInfo.count()>=4) {
        pageClient->setVersion(baseInfo.at(0).toInt());
        pageClient->setDeviceMN(baseInfo.at(1));
        pageClient->setDevicePW(baseInfo.at(2));
        pageClient->setDeviceST(baseInfo.at(3));
    }
    pageClient->setClientAddress(tabPageClient->localIPaddr(),tabPageClient->localPort());
    pageClient->setServerAddress(tabPageClient->serverIPAddr(),tabPageClient->serverPort());
    pageClient->setCurrentDeviceSocket(tabPageClient->deviceCode(),tabPageClient->serverIPAddr(),tabPageClient->serverPort());
}
//客户端树型视图主项右击槽函数
void MainWindow::tabPageClientMainItemRightClicked(int state)
{
    popupMenu->popupClientMainMenu(state);
}
//客户端树型视图子项右击槽函数
void MainWindow::tabPageClientSubItemRightClicked(int state)
{
    popupMenu->popupClientSubMenu(state);
}
//客户端槽链接建立槽函数
void MainWindow::pageClientLinkerBuildHandle(const QString &id,const QString &ipaddr,int port)
{
    int ps = id.indexOf('<',0);
    int pd = id.indexOf(':',0);
    int pe = id.indexOf('>',0);
    if(ps!=-1 && pd!=-1 && pe !=-1) {
        QString mn = id.left(ps);
        QString objIP = id.mid(ps+1,pd-ps-1);
        int objPort = id.mid(pd+1,pe-pd-1).toInt();
        tabPageClient->connectSubItem(mn,objIP,objPort,ipaddr,port);
    }
}
//客户端槽链接断开槽函数
void MainWindow::pageClientLinkerCloseHandle(const QString &id)
{
    int ps = id.indexOf('<',0);
    int pd = id.indexOf(':',0);
    int pe = id.indexOf('>',0);
    if(ps!=-1 && pd!=-1 && pe !=-1) {
        QString mn = id.left(ps);
        QString objIP = id.mid(ps+1,pd-ps-1);
        int objPort = id.mid(pd+1,pe-pd-1).toInt();
        tabPageClient->disconnectSubItem(mn,objIP,objPort);
    }
}

//后台运行(最小化到系统托盘)槽函数
void MainWindow::trayIconActivatedHandle(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::Trigger || reason==QSystemTrayIcon::DoubleClick) { //单击或双击
        if(!isVisible() || (isVisible() && isMinimized())){
            setWindowState(Qt::WindowActive);
            setGeometry(geometry());
            showNormal();
        }
    }
}



