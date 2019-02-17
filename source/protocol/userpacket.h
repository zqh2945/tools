#ifndef USERPACKET_H
#define USERPACKET_H

#include "../source/protocol/usercontent.h"

class UserPacket : public UserContent
{
	Q_OBJECT
public:
    explicit UserPacket(enum Direction dir,QObject *parent=0);
    explicit UserPacket(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent=0);
    ~UserPacket();
    bool packetUnpack(QString packet); //报文解包
    QString packetPack(); //报文打包
    int packetVerifyCalculate(QString packet); //报文CRC校验计算
    void setPacketMN(const QString &mn) {MN = mn;} //MN设置
    void setPacketPW(const QString &pw) {PW = pw;} //PW设置
    void setPacketST(const QString &st) {ST = st;} //ST设置
    QString packetQN() {return QN;} //QN获取
    void setPacketQN(); //QN设置
    int packetCN() {return CN;} //CN获取
    void setPacketCN(int cn) {CN = cn;} //CN设置
    int packetFlag() {return Flag;} //Flag获取
    void setPacketFlag(int flag) {Flag = flag;} //Flag设置
    void setPacketPNUM(int num) {PNUM = num;} //PNUM设置
    void setPacketPNO(int no) {PNO = no;} //PNO设置
    QString packetCP() {return CP;} //报文内容获取
    void setPacketCP(const QString &cp) {CP = cp;} //报文内容设置
    void setReplyAndSplit(bool reply,bool split); //是否应答,是否拆包设置
private:
    QString CP;
    QString QN;
    QString MN;
    QString PW;
    QString ST;
    int CN;
    int Flag;
    int PNUM;
    int PNO;

    QString fieldExtract(const QString &packet,const QString &field,bool *ok);
};

#endif // USERPACKET_H
