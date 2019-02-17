#include "userframe.h"
#include <QDebug>

UserFrame::UserFrame(enum Direction dir,QObject *parent) : UserPacket(dir,parent)
{

}

UserFrame::UserFrame(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent)
    : UserPacket(dir,mn,pw,st,version,parent)
{

}

UserFrame::~UserFrame()
{

}

//帧检测
QString UserFrame::frameCheck(const QString &buffer,bool &ok)
{
    QString frame;
    ok = false;
    frame.clear();
    if(!buffer.isEmpty()) {
        int head = buffer.indexOf("##",0,Qt::CaseSensitive);
        int tail = buffer.indexOf("\r\n",0,Qt::CaseSensitive);
        if((head != -1)&&(tail != -1)) {
            frame = buffer.mid(head,tail+2-head);
            ok = true;
        }
    }
    return frame;
}

//帧解包
bool UserFrame::frameUnpack(const QString &frame)
{
    bool ok = false;
    int req = -1;
    if(!frame.isEmpty()) {
        bool tmp;
        Length = frame.mid(2,4).toInt(&tmp,10);
        if(tmp && (Length+12 == frame.length())) {
            Parity = frame.mid(Length+6,4).toInt(&tmp,16);
            Packet = frame.mid(6,Length);
            if(tmp && (Parity == packetVerifyCalculate(Packet))) {
                ok = true;
            } else {
                req = 10;
            }
        }
    }
    if(device()==NULL) {setRequest(req);} else {device()->setRequest(req);}
    return ok;
}

//帧打包
QString UserFrame::framePack()
{
    QString frame;
    frame.clear();
    if(!Packet.isEmpty()) {
        Length = Packet.length();
        Parity = packetVerifyCalculate(Packet);
        QString strLength = QString("%1").arg(Length,4,10,QLatin1Char('0'));
        QString strParity = QString("%1").arg(Parity,4,16,QLatin1Char('0')).toUpper();
        frame = "##" + strLength + Packet + strParity + "\r\n";
    }
    return frame;
}
