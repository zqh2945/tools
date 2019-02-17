#include "userrunninglog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

UserRunningLog::UserRunningLog(enum PlatformType type,QWidget *parent) : QWidget(parent)
{
    Platform = type;
    if(Platform!=EMPTY) {
        labelTitle = new UserLabel(tr("运行日志"));
        labelTitle->setFixedWidth(644);
        buttonClear = new UserButton(tr("清空"));
        buttonClear->setFixedWidth(72);
        QHBoxLayout *row0Layout = new QHBoxLayout();
        row0Layout->addWidget(labelTitle);
        row0Layout->addWidget(buttonClear);

        textEditLog = new QTextEdit();
        textEditLog->setReadOnly(true);
        textEditLog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(row0Layout);
        mainLayout->addWidget(textEditLog);
        mainLayout->setSpacing(5);
        mainLayout->setMargin(0);

        connect(buttonClear,SIGNAL(clicked()),this,SLOT(buttonClearClickedHandle()));
    }
}

UserRunningLog::~UserRunningLog()
{
}
//获取设备标识符
QString UserRunningLog::identifier()
{
    return QString("");
}
//获取设备
UserDevice* UserRunningLog::device()
{
    return NULL;
}
//设备初始化
void UserRunningLog::initialization()
{

}
//启动设备
void UserRunningLog::start(UserTcpSocket*)
{

}
//启动设备
void UserRunningLog::start()
{
}
//关闭设备
void UserRunningLog::stop()
{
}
//获取设备状态
bool UserRunningLog::state()
{
    return true;
}
//设置子设备标识符列表
void UserRunningLog::setChildIdentifirtList(const QStringList&)
{
}
//发送消息
void UserRunningLog::sendMessage(const QString &msg)
{
    textEditLog->setTextColor(QColor(Qt::blue));
    textEditLog->append("Send:" + msg);
}

//设置运行日志窗口标题
void UserRunningLog::setTitle(const QString &ipaddr,int port)
{
    QString address = QString("%1:%2").arg(ipaddr).arg(port);
    if(Platform==SERVER) {
        labelTitle->setText("服务器(" + address + ")运行日志");
    } else if(Platform==CLIENT_LINKER) {
        labelTitle->setText("客户端链接槽(" + address + ")运行日志");
    }
}
//设置运行窗口标题
void UserRunningLog::setTitle(const QString &title)
{
    if(Platform==CLIENT) {
        labelTitle->setText("客户端(" + title + ")运行日志");
    } else if(Platform==SERVER_DEVICE) {
        labelTitle->setText("服务器监测点(" + title + ")运行日志");
    }
}
//增加运行日志
void UserRunningLog::appendRunningLog(const QString &log)
{
    textEditLog->setTextColor(QColor(Qt::black));
    textEditLog->append(log+"\n");
}
//增加发送消息
void UserRunningLog::appendSendMsg(const QString &target,const QString &msg)
{
    textEditLog->setTextColor(QColor(Qt::blue));
    textEditLog->append("Send(" + target + "):" + msg);
}
//增加接收消息
void UserRunningLog::appendReceiveMsg(const QString &target,const QString &msg)
{
    textEditLog->setTextColor(QColor(Qt::red));
    textEditLog->append("Receive(" + target + "):" + msg);
}
//
void UserRunningLog::buttonClearClickedHandle()
{
    textEditLog->clear();
}
