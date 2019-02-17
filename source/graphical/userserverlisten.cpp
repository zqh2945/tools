#include "userserverlisten.h"
#include "../source/files/userserverlogfile.h"
#include <QVBoxLayout>
#include <QDebug>

UserServerListen::UserServerListen(const QString &ipaddr,int port,QWidget *parent)
    : UserRunningLog(UserRunningLog::SERVER,parent)
{
    setTitle(ipaddr,port);
    ServerIPAddr = ipaddr;
    ServerPort = port;

    tcpServer = new UserTcpServer(ipaddr,port);
    connect(tcpServer,SIGNAL(runningLog(QString)),this,SLOT(tcpServerRunningLogHandle(QString)));
    connect(tcpServer,SIGNAL(connection(UserTcpSocket*)),this,SLOT(tcpServerConnectionHandle(UserTcpSocket*)));
}

UserServerListen::~UserServerListen()
{
    stop();
}
//获取服务器标识符
QString UserServerListen::identifier()
{
    return QString("%1:%2").arg(ServerIPAddr).arg(ServerPort);
}
//
UserDevice* UserServerListen::device()
{
    return NULL;
}

//启动服务器
void UserServerListen::start()
{
    tcpServer->startServer();
}
//停止服务器
void UserServerListen::stop()
{
    tcpServer->stopServer();
}
//获取服务器状态
bool UserServerListen::state()
{
    return tcpServer->isListening();
}

//设置服务器监测设备编码列表
void UserServerListen::setChildIdentifirtList(const QStringList &list)
{
    DeviceCodeList = list;
}
//发送消息
void UserServerListen::sendMessage(const QString&)
{
    //msg = msg;
}
//服务器日志槽函数
void UserServerListen::tcpServerRunningLogHandle(const QString &msg)
{
    appendRunningLog(msg);
    QString filename = QString("%1(%2)").arg(ServerIPAddr).arg(ServerPort);
    UserServerLogFile::writeLog(ServerIPAddr,ServerPort,msg);
}
//服务器监听到链接槽函数
void UserServerListen::tcpServerConnectionHandle(UserTcpSocket *socket)
{
    connect(socket,SIGNAL(runningLog(QString)), \
            this,SLOT(tcpSocketRunningLogHandle(QString)));
    connect(socket,SIGNAL(linkerClose(UserTcpSocket*)), \
            this,SLOT(tcpSocketLinkerCloseHandle(UserTcpSocket*)));
    connect(socket,SIGNAL(identification(UserTcpSocket*,QString)), \
            this,SLOT(tcpSocketIdentificationHandle(UserTcpSocket*,QString)));
    tcpSocketList.append(socket);
}
//链接槽日志函数
void UserServerListen::tcpSocketRunningLogHandle(const QString &log)
{
    appendRunningLog(log);
}
//链接槽接收消息槽函数
void UserServerListen::tcpSocketIdentificationHandle(UserTcpSocket *socket,const QString &msg)
{
    bool ok = false;
    for(int i=0;i<DeviceCodeList.count();i++) {
        if(deviceCodeCheck(msg,DeviceCodeList.at(i))) {
            QString mn = DeviceCodeList.at(i);
            for(int j=0;j<tcpSocketList.count();j++) {
                if(tcpSocketList.at(j)==socket) {
                    tcpSocketList.removeAt(j);
                    socket->setIdentification(true);
                    QString id = QString("%1:%2<%3>").arg(ServerIPAddr).arg(ServerPort).arg(mn);
                    emit connection(id,socket);
                    ok = true;
                    break;
                }
            }
            break;
        }
    }
    if(!ok) {
        QString ipaddr = socket->peerAddress().toString();
        int port = socket->peerPort();
        QString socketAddress = QString("%1:%2").arg(ipaddr).arg(port);
        appendReceiveMsg(socketAddress,msg);
    }
}
//链接断开槽函数
void UserServerListen::tcpSocketLinkerCloseHandle(UserTcpSocket *socket)
{
    for(int i=0;i<tcpSocketList.count();i++) {
        if(tcpSocketList.at(i)==socket) {
            tcpSocketList.removeAt(i);
            break;
        }
    }
}

//
bool UserServerListen::deviceCodeCheck(const QString &msg,const QString &mn)
{
    bool ok = false;
    QString tmp = QString("MN=%1").arg(mn);
    int ps = msg.indexOf(tmp,0);
    int pe = msg.indexOf(";",ps+tmp.length());
    if((ps != -1) && (pe != -1)) {
        ok = true;
    }
    return ok;
}





