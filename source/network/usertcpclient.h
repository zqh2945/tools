#ifndef USERTCPCLIENT_H
#define USERTCPCLIENT_H

#include <QTcpSocket>
#include <QTimerEvent>
#include <QHostAddress>

class UserTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    UserTcpClient(const QString &ipaddr,int port,QObject *parent=0);
    ~UserTcpClient();
    void startSocket();
    void stopSocket();
    bool stateSocket();
    void sendMsg(const QString &msg);
signals:
    void runningLog(const QString &log);
    void linkerBuild(const QString &ipaddr,int port);
    void linkerClose();
    void receiveMsg(const QString &msg);
protected:
    virtual void timerEvent(QTimerEvent *event);
private:
    QString ClientIPAddr; //
    int ClientPort; //
    QString ServerIPAddr; //
    int ServerPort; //
    int TimerID; //槽链接控制定时器

    QString toClientAddress();
    QString toServerAddress();
private slots:
    void connectedHandle();
    void disconnectedHandle();
    void receiveMessageHandle();
};

#endif // USERTCPCLIENT_H
