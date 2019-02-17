#ifndef USERFRAME_H
#define USERFRAME_H

#include "../source/protocol/userpacket.h"
#include <QString>

class UserFrame : public UserPacket
{
	Q_OBJECT
public:
    explicit UserFrame(enum Direction dir,QObject *parent=0);
    explicit UserFrame(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent=0);
    ~UserFrame();
    QString frameCheck(const QString &buffer,bool &ok); //帧检测
    bool frameUnpack(const QString &frame); //帧解包
    QString framePack(); //帧打包
    QString framePacket() {return Packet;} //报文字符串获取
    void setFramePacket(const QString &packet) {Packet = packet;} //报文字符串设置
private:
    QString Packet;
    int Length;
    int Parity;
};

#endif // USERFRAME_H
