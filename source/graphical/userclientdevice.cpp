#include "userclientdevice.h"
#include "../source/files/userclientlogfile.h"
#include <QDebug>

UserClientDevice::UserClientDevice(const QStringList &baseInfo,QWidget *parent)
    : UserRunningLog(UserRunningLog::CLIENT,parent)
{
    if(baseInfo.count()>=4) {
        QString mn = baseInfo.at(1);
        QString pw = baseInfo.at(2);
        QString st = baseInfo.at(3);
        int version = baseInfo.at(0).toInt();
        DeviceCode = mn;
        setTitle(DeviceCode);
        Device = new UserDevice(UserDevice::Lower,mn,pw,st,version);
        Device->initialization(mn);
        Protocol = new UserProtocol(UserProtocol::Lower,mn,pw,st,version);
        Protocol->setDevice(Device);

        connect(Device,SIGNAL(protocolUpdateQN()),Protocol,SLOT(protocolUpdateQNHandle()));
        connect(Device,SIGNAL(protocolUnpack(QString)),Protocol,SLOT(protocolUnpackHandle(QString)));
        connect(Device,SIGNAL(protocolPack(QString*,int,bool,bool)),Protocol,SLOT(protocolPackHandle(QString*,int,bool,bool)));
        connect(Device,SIGNAL(runningLog(QString)),this,SLOT(deviceRunningLogHandle(QString)));
        connect(Device,SIGNAL(sendMsg(QString)),this,SLOT(deviceSendMsgHandle(QString)));
        connect(Device,SIGNAL(sendMsg(QString,QString)),this,SLOT(deviceSendMsgHandle(QString,QString)));
    }
}

UserClientDevice::~UserClientDevice()
{
    stop();
}
//获取数采仪唯一标识
QString UserClientDevice::identifier()
{
	return QString("%1").arg(DeviceCode);
}
//获取数采仪
UserDevice* UserClientDevice::device()
{
    return Device;
}
//数采仪初始化
void UserClientDevice::initialization()
{
    Device->initialization(DeviceCode);
}
//数采仪上电运行
void UserClientDevice::start()
{
    appendRunningLog(QString("客户端(%1)启动...").arg(DeviceCode));
    Device->start();
}
//数采仪掉电关机
void UserClientDevice::stop()
{
    appendRunningLog(QString("客户端(%1)关闭...").arg(DeviceCode));
    Device->stop();
}
//数采仪状态
bool UserClientDevice::state()
{
    return Device->state();
}
//设置数采仪链接槽唯一标识列表
void UserClientDevice::setChildIdentifirtList(const QStringList &list)
{
    ConnectIDList = list;
    for(int i=0;i<ConnectIDList.count();i++) {
        ConnectStateList.append(false);
    }
}
//数采仪发送消息，该函数用于数采仪发送消息给所以链接槽
void UserClientDevice::sendMessage(const QString &msg)
{
    for(int i=0;i<ConnectIDList.count();i++) {
        if(ConnectStateList.at(i)) {
            int ps = ConnectIDList.at(i).indexOf('<',0)+1;
            int pe = ConnectIDList.at(i).indexOf('>',0);
            if(ps!=-1 && pe!=-1) {
                QString address = ConnectIDList.at(i).mid(ps,pe-ps);
                QString log = QString("Send(%1):%2").arg(address).arg(msg);
                UserClientLogFile::writeLog(identifier(),log);
                appendSendMsg(address,msg);
                emit sendMsg(ConnectIDList.at(i),msg);
            }
        }
    }
}
//数采仪发送消息，该函数用于发送消息给指定链接槽
void UserClientDevice::sendMessage(const QString &id,const QString &msg)
{
    if(ConnectIDList.contains(id)) {
        int index = ConnectIDList.indexOf(id);
        if(ConnectStateList.at(index)) {
            int ps = id.indexOf('<',0)+1;
            int pe = id.indexOf('>',0);
            if(ps!=-1 && pe!=-1) {
                QString address = id.mid(ps,pe-ps);
                QString log = QString("Send(%1):%2").arg(address).arg(msg);
                UserClientLogFile::writeLog(identifier(),log);
                appendSendMsg(address,msg);
                emit sendMsg(id,msg);
            }
        }
    }
}

//链接槽链接链接槽函数
void UserClientDevice::socketLinkerBuildHandle(const QString &id,const QString &ipaddr,int port)
{
    for(int i=0;i<ConnectIDList.count();i++) {
        if(ConnectIDList.at(i)==id) {
            ConnectStateList.replace(i,true);
            emit linkerBuild(id,ipaddr,port);
        }
    }
}
//链接槽链接断开槽函数
void UserClientDevice::socketLinkerCloseHandle(const QString &id)
{
    for(int i=0;i<ConnectIDList.count();i++) {
        if(ConnectIDList.at(i)==id) {
            ConnectStateList.replace(i,false);
            emit linkerClose(id);
        }
    }
}
//链接槽运行日志槽函数，该函数用于处理从指定链接槽产生的日志信息
void UserClientDevice::socketRunningLogHandle(const QString &id,const QString &log)
{
    if(ConnectIDList.contains(id)) {
        UserClientLogFile::writeLog(identifier(),log);
        appendRunningLog(log);
    }
}
//链接槽接收消息槽函数，该函数用于处理指定链接槽接收的消息
void UserClientDevice::socketReceiveMsgHandle(const QString &id,const QString &msg)
{
    if(ConnectIDList.contains(id)) {
        int ps = id.indexOf('<',0)+1;
        int pe = id.indexOf('>',0);
        if(ps!=-1 && pe!=-1) {
            QString address = id.mid(ps,pe-ps);
            QString log = QString("Receive(%1):%2").arg(address).arg(msg);
            UserClientLogFile::writeLog(identifier(),log);
            appendReceiveMsg(address,msg);
            Device->receiveMessage(id,msg);
            //处理接收消息
        }
    }
}
//链接槽发送消息槽函数，该函数用于处理指定链接槽主动发送的消息
void UserClientDevice::socketSendMsgHandle(const QString &id,const QString &msg)
{
    if(ConnectIDList.contains(id)) {
        int index = ConnectIDList.indexOf(id);
        if(ConnectStateList.at(index)) {
            int ps = id.indexOf('<',0)+1;
            int pe = id.indexOf('>',0);
            if(ps!=-1 && pe!=-1) {
                QString address = id.mid(ps,pe-ps);
                QString log = QString("Send(%1):%2").arg(address).arg(msg);
                UserClientLogFile::writeLog(identifier(),log);
                appendSendMsg(address,msg);
            }
        }
    }
}
//数采仪运行日志槽函数
void UserClientDevice::deviceRunningLogHandle(const QString &log)
{
    UserClientLogFile::writeLog(identifier(),log);
    appendRunningLog(log);
}

//数采仪发送消息槽函数
void UserClientDevice::deviceSendMsgHandle(const QString &msg)
{
    sendMessage(msg);
}
//数采仪发送消息槽函数
void UserClientDevice::deviceSendMsgHandle(const QString &id,const QString &msg)
{
    sendMessage(id,msg);
}


