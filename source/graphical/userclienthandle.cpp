#include "../source/graphical/userclienthandle.h"
#include "../source/files/userclientlistfile.h"
#include "../source/files/userclientdatabasefile.h"
#include "../source/device/userdevice.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QVBoxLayout>

UserClientHandle::UserClientHandle(QWidget *parent) : QWidget(parent)
{
    Protocol = new UserProtocol(UserContent::Lower);
    addressEdit = new UserAddressEdit(UserAddressEdit::CLIENT);
    packetFieldEdit = new UserPacketFieldEdit(UserPacketFieldEdit::CLIENT,Protocol->version());
    frameEdit = new UserFrameEdit();

    emptyClient = new UserRunningLog(UserRunningLog::EMPTY);
    stackWidget = new UserStackedWidget();
    stackWidget->addWidget(emptyClient);
    stackWidget->setCurrentIndex(0);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(addressEdit);
    mainLayout->addWidget(packetFieldEdit);
    mainLayout->addWidget(frameEdit);
    mainLayout->addWidget(stackWidget);
    mainLayout->setSpacing(15);
    mainLayout->setMargin(5);
    setLayout(mainLayout);

    Protocol->setDeviceMN(packetFieldEdit->fieldMN());
    Protocol->setDevicePW(packetFieldEdit->fieldPW());
    Protocol->setDeviceST(packetFieldEdit->fieldPW());
    Protocol->setPacketMN(packetFieldEdit->fieldMN());
    Protocol->setPacketPW(packetFieldEdit->fieldPW());
    Protocol->setPacketST(packetFieldEdit->fieldST());
    Protocol->setPacketCN(packetFieldEdit->fieldCN());
    Protocol->setPacketFlag(packetFieldEdit->fieldFlag());

    connect(packetFieldEdit,SIGNAL(filedChanged(int)),this,SLOT(packetFieldEditFieldChangedHandle(int)));
    connect(frameEdit,SIGNAL(buttonClicked(int)),this,SLOT(frameEditButtonClickedHandle(int)));
}

UserClientHandle::~UserClientHandle()
{

}
//初始化客户端
void UserClientHandle::initialization()
{
    QList<QStringList> baseInfoList = UserClientListFile::clientList();
    for(int i=0;i<baseInfoList.count();i++) {
        QStringList baseInfo = baseInfoList.at(i);
        if(baseInfo.count()>=2) {
            createDevice(baseInfo); //创建客户端
            QString mn = baseInfo.at(1);
            QList<QStringList> socketList = UserClientDatabaseFile::socketConfigList(mn);
            createDeviceAllSocket(baseInfo,socketList); //创建客户端所有链接槽
        }
    }
}

//设置客户端的地址
void UserClientHandle::setClientAddress(const QString &ipaddr,int port)
{
    addressEdit->setClientIPAddrAndPort(ipaddr,port);
}
//设置客户端链接槽地址
void UserClientHandle::setServerAddress(const QString &ipaddr,int port)
{
    addressEdit->setServerIPAddrAndPort(ipaddr,port);
}
//设置标准版本
void UserClientHandle::setVersion(int version)
{
    Protocol->setVersion(version);
    addressEdit->setVersion(version);
    packetFieldEdit->setVersion(version);
}
//设置设备编码
void UserClientHandle::setDeviceMN(const QString &mn)
{
    Protocol->setDeviceMN(mn);
    Protocol->setPacketMN(mn);
    packetFieldEdit->setFieldMN(mn);
}
//设置设备密码
void UserClientHandle::setDevicePW(const QString &pw)
{
    Protocol->setPacketPW(pw);
    Protocol->setDevicePW(pw);
    packetFieldEdit->setFieldPW(pw);
}
//设置系统类型
void UserClientHandle::setDeviceST(const QString &st)
{
    Protocol->setPacketST(st);
    Protocol->setDeviceST(st);
    packetFieldEdit->setFiledST(st);
}

//查找客户端
int UserClientHandle::findDevice(const QString &mn)
{
    int index = -1;
    for(int i=0;i<ClientList.count();i++) {
        if(ClientList.at(i)->identifier()==mn) {
            index = i;
            break;
        }
    }
    return index;
}
//创建客户端
void UserClientHandle::createDevice(const QStringList &baseInfo)
{
    UserRunningLog *device = new UserClientDevice(baseInfo);
    connect(device,SIGNAL(linkerBuild(QString,QString,int)),this,SLOT(clientSocketLinkerBuildHandle(QString,QString,int)));
    connect(device,SIGNAL(linkerClose(QString)),this,SLOT(clientSocketLinkerCloseHandle(QString)));
    ClientList.append(device);
    stackWidget->addWidget(device);
}
//启动客户端
void UserClientHandle::startDevice(const QString &mn,const QList<QStringList> &serList)
{
    int index = findDevice(mn);
    if(index!=-1) {
        QStringList idList;
        for(int i=0;i<serList.count();i++) {
            QStringList server = serList.at(i);
            if(server.count()>=3 && server.first().toInt()==1) {
                idList.append(QString("%1<%2:%3>").arg(mn).arg(server.at(1)).arg(server.at(2)));
            }
        }
        ClientList.at(index)->setChildIdentifirtList(idList);
        ClientList.at(index)->initialization();
        ClientList.at(index)->start(); //客户端启用
        stackWidget->setCurrentWidget(ClientList.at(index));
    }
}
//关闭客户端
void UserClientHandle::stopDevice(const QString &mn)
{
    int index = findDevice(mn);
    if(index!=-1) {
        ClientList.at(index)->stop(); //客户端关闭
    }
}
//删除客户端
void UserClientHandle::deleteDevice(const QString &mn)
{
    int index = findDevice(mn);
    if(index!=-1) {
        stackWidget->removeWidget(ClientList.at(index));
        delete ClientList.at(index);
        ClientList.removeAt(index);
    }
}
//设置当前需要显示的客户端
void UserClientHandle::setCurrentDevice(const QString &mn)
{
    stackWidget->setCurrentIndex(0);
    for(int i=1;i<stackWidget->count();i++) {
        UserRunningLog *client = (UserRunningLog*)stackWidget->widget(i);
        if(client->identifier()==mn) {
            stackWidget->setCurrentIndex(i);
            Protocol->setDevice(client->device());
            break;
        }
    }
}

//查找客户端链接槽
int UserClientHandle::findDeviceSocket(const QString &mn,const QString &ipaddr,int port)
{
    int index = -1;
    QString id = QString("%1<%2:%3>").arg(mn).arg(ipaddr).arg(port);
    for(int i=0;i<ClientList.count();i++) {
        if(ClientList.at(i)->identifier()==id) {
            index = i;
            break;
        }
    }
    return index;
}
//创建客户端链接槽
void UserClientHandle::createDeviceSocket(const QStringList &baseInfo,const QString &ipaddr,int port)
{
    if(baseInfo.count()>=2) {
        QString mn = baseInfo.at(1);
        int index = findDevice(mn);
        if(index!=-1 && findDeviceSocket(mn,ipaddr,port)==-1) {
            UserClientDevice *device = (UserClientDevice*)ClientList.at(index);
            UserClientSocketLink *socket = new UserClientSocketLink(mn,ipaddr,port);
            socket->setDevice(device->device());

            connect(socket,SIGNAL(linkerBuild(QString,QString,int)),device,SLOT(socketLinkerBuildHandle(QString,QString,int)));
            connect(socket,SIGNAL(linkerClose(QString)),device,SLOT(socketLinkerCloseHandle(QString)));
            connect(socket,SIGNAL(runningLog(QString,QString)),device,SLOT(socketRunningLogHandle(QString,QString)));
            connect(socket,SIGNAL(receiveMsg(QString,QString)),device,SLOT(socketReceiveMsgHandle(QString,QString)));
            connect(socket,SIGNAL(sendMsg(QString,QString)),device,SLOT(socketSendMsgHandle(QString,QString)));

            connect(device,SIGNAL(sendMsg(QString,QString)),socket,SLOT(sendMsgHandle(QString,QString)));
            ClientList.append(socket);
            stackWidget->addWidget(socket);
        }
    }
}
//启动客户端链接槽
void UserClientHandle::startDeviceSocket(const QString &mn,const QString &ipaddr,int port)
{
    int deviceIndex = findDevice(mn);
    int socketIndex = findDeviceSocket(mn,ipaddr,port);
    if(deviceIndex!=-1 && socketIndex!=-1) {
        if(ClientList.at(deviceIndex)->state()) {
            ClientList.at(socketIndex)->start(); //启用槽链接
        }
    }
}
//关闭客户端链接槽
void UserClientHandle::stopDeviceSocket(const QString &mn,const QString &ipaddr,int port)
{
    int deviceIndex = findDevice(mn);
    int socketIndex = findDeviceSocket(mn,ipaddr,port);
    if(deviceIndex!=-1 && socketIndex!=-1) {
        if(ClientList.at(deviceIndex)->state()) {
            ClientList.at(socketIndex)->stop(); //关闭槽链接
        }
    }
}
//删除客户端链接槽
void UserClientHandle::deleteDeviceSocket(const QString &mn,const QString &ipaddr,int port)
{
    int index = findDeviceSocket(mn,ipaddr,port);
    if(index!=-1) {
        stackWidget->removeWidget(ClientList.at(index));
        delete ClientList.at(index);
        ClientList.removeAt(index);
    }
}
//设置当前需要显示的客户端链接槽
void UserClientHandle::setCurrentDeviceSocket(const QString &mn,const QString &ipaddr,int port)
{
    stackWidget->setCurrentIndex(0);
    QString id = QString("%1<%2:%3>").arg(mn).arg(ipaddr).arg(port);
    for(int i=1;i<stackWidget->count();i++) {
        UserRunningLog *socket = (UserRunningLog*)stackWidget->widget(i);
        if(socket->identifier()==id) {
            stackWidget->setCurrentIndex(i);
            Protocol->setDevice(socket->device());
            break;
        }
    }
}

//创建客户端所有链接槽
void UserClientHandle::createDeviceAllSocket(const QStringList &baseInfo,const QList<QStringList> &serList)
{
    for(int i=0;i<serList.count();i++) {
        if(serList.at(i).count()>=3 && serList.at(i).first().toInt()==1) {
            createDeviceSocket(baseInfo,serList.at(i).at(1),serList.at(i).at(2).toInt());
        }
    }
}
//启用客户端所有链接槽
void UserClientHandle::startDeviceAllSocket(const QString &mn,const QList<QStringList> &serList)
{
    for(int i=0;i<serList.count();i++) {
        if(serList.at(i).count()>=3 && serList.at(i).first().toInt()==1) {
            startDeviceSocket(mn,serList.at(i).at(1),serList.at(i).at(2).toInt());
        }
    }
}
//关闭客户端所有链接槽
void UserClientHandle::stopDeviceAllSocket(const QString &mn,const QList<QStringList> &serList)
{
    for(int i=0;i<serList.count();i++) {
        if(serList.at(i).count()>=3 && serList.at(i).first().toInt()==1) {
            stopDeviceSocket(mn,serList.at(i).at(1),serList.at(i).at(2).toInt());
        }
    }
}
//删除客户端所有链接槽
void UserClientHandle::deleteDeviceAllSocket(const QString &mn)
{
    QString id = QString("%1<").arg(mn);
    for(int i=0;i<ClientList.count();i++) {
        if(ClientList.at(i)->identifier().indexOf(id,0)!=-1) {
            stackWidget->removeWidget(ClientList.at(i));
            delete ClientList.at(i);
            ClientList.removeAt(i);
        }
    }
}
//客户端报文字段其中改变槽函数
void UserClientHandle::packetFieldEditFieldChangedHandle(int num)
{
    if(num==0) {
        Protocol->setPacketMN(packetFieldEdit->fieldMN());
    } else if(num==1) {
        Protocol->setPacketPW(packetFieldEdit->fieldPW());
    } else if(num==2) {
        Protocol->setPacketST(packetFieldEdit->fieldST());
    } else if(num==3) {
        Protocol->setPacketCN(packetFieldEdit->fieldCN());
    } else if(num==4) {
        Protocol->setPacketFlag(packetFieldEdit->fieldFlag());
    }
}
//客户端帧组包或发送槽函数
void UserClientHandle::frameEditButtonClickedHandle(int num)
{
    if(num==0) { //帧打包
        Protocol->setPacketQN(); //生成新的QN
        frameEdit->setFrame(Protocol->protocolPack(Protocol->packetCN()));
    } else if(num==1) { //帧发送
        UserRunningLog *currentClient = (UserRunningLog*)stackWidget->currentWidget();
        if(currentClient!=NULL) {
            if(currentClient->identifier()==Protocol->deviceMN()) {
                //当前选中的通信端是数采仪
                if(currentClient->state()) {
                    currentClient->sendMessage(frameEdit->frame());
                } else {
                    QString mn = Protocol->deviceMN();
                    QMessageBox::information(this,tr("提示"),tr("数采仪(%1)未启动!").arg(mn));
                }
            } else {
                //当前选中的通信端是数采仪对应的一个链接槽
                if(currentClient->state()) {
                    currentClient->sendMessage(frameEdit->frame());
                } else {
                    QString mn = Protocol->deviceMN();
                    QString address = addressEdit->serverAddress();
                    QMessageBox::information(this,tr("提示"),tr("数采仪(%1)与服务器(%2)未链接！").arg(mn).arg(address));
                }
            }
        }
    }
}
//
void UserClientHandle::clientSocketLinkerBuildHandle(const QString &id,const QString &ipaddr,int port)
{
    emit linkerBuild(id,ipaddr,port);
}
//
void UserClientHandle::clientSocketLinkerCloseHandle(const QString &id)
{
    emit linkerClose(id);
}




