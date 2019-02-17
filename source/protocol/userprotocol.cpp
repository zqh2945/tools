#include "userprotocol.h"

UserProtocol::UserProtocol(enum Direction dir,QObject *parent) : UserFrame(dir,parent)
{

}

UserProtocol::UserProtocol(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent)
    : UserFrame (dir,mn,pw,st,version,parent)
{

}

UserProtocol::~UserProtocol()
{

}

//HJ/T212标准解包
int UserProtocol::protocolUnpack(const QString &buffer)
{
    bool ok;
    Frame.clear();
    Frame = frameCheck(buffer,ok);
    if(ok) {
        if(frameUnpack(Frame)) {
            if(packetUnpack(framePacket())) {
                if(contentUnpack(packetCP(),packetCN())) {
                    ok = true;
                }
            }
        }
    }
    if(ok) {
        return packetCN();
    } else {
        return -1;
    }
}
//HJ/T212标准打包
QString UserProtocol::protocolPack(int cn)
{
    setPacketCP(contentPack(cn));
    setPacketCN(cn);
    setFramePacket(packetPack());
    return framePack();
}
QString UserProtocol::protocolPack(int cn,bool reply,bool split)
{
    setPacketCP(contentPack(cn));
    setPacketCN(cn);
    setReplyAndSplit(reply,split);
    setFramePacket(packetPack());
    return framePack();
}
//更新QN
void UserProtocol::protocolUpdateQNHandle()
{
    setPacketQN();
}
//HJ/T212标准解包槽函数
void UserProtocol::protocolUnpackHandle(const QString &buffer)
{
    int cn = protocolUnpack(buffer);
    if(device()!=NULL) {device()->setCommand(cn);}
}
//HJ/T212标准打包槽函数
void UserProtocol::protocolPackHandle(QString *frame,int cn,bool reply,bool split)
{
    *frame = protocolPack(cn,reply,split);
}









