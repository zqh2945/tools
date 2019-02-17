#ifndef USERTCPSOCKET_H
#define USERTCPSOCKET_H

#include <QTcpSocket>
#include <QTimerEvent>

class UserTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    UserTcpSocket(QObject *parent=0);
    ~UserTcpSocket();
    void setIdentification(bool flag);
    virtual void timerEvent(QTimerEvent *event);
    void disconnectedSocket();
    void sendMessage(const QString &msg);
signals:
    void linkerClose(UserTcpSocket *socket);
    void runningLog(const QString &log);
    void receiveMsg(const QString &msg);
    void identification(UserTcpSocket *socket,const QString &msg);
private:
    bool Identification;
    int TimerWait;

    QString toServerAddress();
    QString toSocketAddress();
private slots:
    void disconnectedHandle();
    void receiveMessage();
};

#endif // USERTCPSOCKET_H
