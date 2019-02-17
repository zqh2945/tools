#ifndef USERPROTOCOL_H
#define USERPROTOCOL_H

#include "../source/protocol/userframe.h"

class UserProtocol : public UserFrame
{
    Q_OBJECT
public:
    explicit UserProtocol(enum Direction dir,QObject *parent=0);
    explicit UserProtocol(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent=0);
    ~UserProtocol();
    int protocolUnpack(const QString &buffer);
    QString protocolPack(int cn);
    QString protocolPack(int cn,bool reply,bool split);
public slots:
    void protocolUpdateQNHandle();
    void protocolUnpackHandle(const QString &buffer);
    void protocolPackHandle(QString *frame,int cn,bool reply,bool split);
private:
    QString Frame;
};

#endif // USERPROTOCOL_H
