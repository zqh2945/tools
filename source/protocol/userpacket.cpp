#include "userpacket.h"
#include <QDateTime>
#include <QDebug>

UserPacket::UserPacket(enum Direction dir,QObject *parent) : UserContent (dir,parent)
{
    setPacketQN();
    MN = "00000000000152316J000000";
    PW = "100000";
    ST = "32";
    Flag = (1<<2); //默认标准版本为HJ/T212-2016
    PNUM = 1;
    PNO = 1;

}

UserPacket::UserPacket(enum Direction dir,const QString &mn,const QString &pw,const QString &st,int version,QObject *parent)
    : UserContent(dir,mn,pw,st,version,parent)
{
    setPacketQN();
    MN = mn;
    PW = pw;
    ST = st;
    Flag = (version<<2);
    PNUM = 1;
    PNO = 1;
}

UserPacket::~UserPacket()
{

}
//字段解析
QString UserPacket::fieldExtract(const QString &packet,const QString &field,bool *ok)
{
    QString value;
    *ok = false;
    int length = field.length() + 1;
    int ps = packet.indexOf(field+"=",0);
    int pe = packet.indexOf(";",ps+length);
    if((ps != -1) && (pe != -1)) {
        ps += length;
        value = packet.mid(ps,pe-ps);
        *ok = true;
    }
    return value;
}
//报文解包
bool UserPacket::packetUnpack(QString packet)
{
    QString mn,pw,st;
    int ver,request;
    bool dir;
    //获取报文解包所需基本信息
    if(device()==NULL) {
        mn = deviceMN();
        pw = devicePW();
        st = deviceST();
        ver = version();
        CN = -1;
        request = -1;
        if(direction()==Upper) {dir = true;} else {dir = false;}
    } else {
        mn = device()->deviceMN();
        pw = device()->devicePW();
        st = device()->deviceST();
        ver = device()->version();
        device()->setCommand(-1);
        request = -1;
        if(device()->direction()==UserDevice::Upper) {dir = true;} else {dir = false;}
    }
    bool state = false;
    //报文解包
	if(!packet.isEmpty()) {
		bool ok;
        if(ver==0) { //HJ/T212-2005标准
            if(dir) { //服务器端
				//ST提取
                if(request == -1) {
					ST = fieldExtract(packet,"ST",&ok);
                    if(!ok) {request = 5;}
				}
				//CN提取
                if(request == -1) {
					CN = fieldExtract(packet,"CN",&ok).toInt();
                    if(!ok) {request = 9;}
				}
                if(request == -1) {
					if(CN < 9000) {
                        if(ST != st) {request = 5;}
					} else {
                        if(ST != "91") {request = 5;}
					}
				}	
				if(CN<2000 || CN>=3000) {
					//QN提取
                    if(request == -1) {
						QN = fieldExtract(packet,"QN",&ok);
                        if(!ok || (ok && QN.length()!=17)) {request = 8;}
					}	
				} 
				//PW提取
                if(request == -1) {
					PW = fieldExtract(packet,"PW",&ok);
                    if(!ok || (ok && PW.length()!=6) || (ok && PW.length()==6 && PW!=pw)) {request = 3;}
				}
				//MN提取
                if(request == -1) {
					MN = fieldExtract(packet,"MN",&ok);
                    if(!ok || (ok && MN.length()!=14) || (ok && MN.length()==14 && MN!=mn)) {request = 4;}
				}
				if(CN==2072 || CN==9011) {
					//Flag提取
                    if(request == -1) {
						Flag = fieldExtract(packet,"Flag",&ok).toInt();
                        if(!ok || (ok && (Flag>>2)!=ver)) {request = 6;}
					}	
				}
				//CP提取
                if(request == -1) {
					int ps = packet.indexOf("CP=&&",0);
					int pe = packet.indexOf("&&",ps+5);
					if((ps != -1) && (pe != -1)) {
                        pe += 2;
						CP = packet.mid(ps,pe-ps);
                    } else {request = 100;}
				}
                if((Flag&0x01)==0x01) {request =1;} else {request = 0;}
                if(device()==NULL) {setRequest(request);} else {device()->setRequest(request);}
                if(request==0 || request==1) {return true;} else {return false;}
            } else { //数采仪端
				//QN提取
                if(request == -1) {
					QN = fieldExtract(packet,"QN",&ok);
                    if(!ok || (ok && QN.length()!=17)) {request = 8;}
				}
				//ST提取
                if(request == -1) {
					ST = fieldExtract(packet,"ST",&ok);
                    if(!ok) {request = 5;}
				}
				//CN提取
                if(request == -1) {
					CN = fieldExtract(packet,"CN",&ok).toInt();
                    if(!ok) {request = 9;}
				}
                if(request == -1) {
					if(CN < 9000) {
                        if(ST != st) {request = 5;}
					} else {
                        if(ST != "91") {request = 5;}
					}
				}	
				if(CN!=9014) {
					//PW提取
                    if(request == -1) {
						PW = fieldExtract(packet,"PW",&ok);
                        if(!ok || (ok && PW.length()!=6) || (ok && PW.length()==6 && PW!=pw)) {request = 3;}
					}
					//MN提取
                    if(request == -1) {
						MN = fieldExtract(packet,"MN",&ok);
                        if(!ok || (ok && MN.length()!=14) || (ok && MN.length()==14 && MN!=mn)) {request = 4;}
					}	
				}
				if(CN!=2012 && CN!=2022 && CN!=9014) {
					//Flag提取
                    if(request == -1) {
						Flag = fieldExtract(packet,"Flag",&ok).toInt();
                        if(!ok || ((Flag>>2)!=ver)) {request = 6;}
					}	
				}
				//CP提取
                if(request == -1) {
					int ps = packet.indexOf("CP=&&",0);
					int pe = packet.indexOf("&&",ps+5);
					if((ps != -1) && (pe != -1)) {
                        pe += 2;
						CP = packet.mid(ps,pe-ps);
                    } else {request = 100;}
				}
                if((Flag&0x01)==0x01) {request =1;} else {request = 0;}
                if(device()==NULL) {setRequest(request);} else {device()->setRequest(request);}
                if(request==0 || request==1) {return true;} else {return false;}
            }
        } else if(ver==1) { //HJ/T212-2016标准
			//QN提取
            if(request == -1) {
				QN = fieldExtract(packet,"QN",&ok);
                if(!ok || (ok && QN.length()!=17)) {request = 8;}
			}
			//ST提取
            if(request == -1) {
				ST = fieldExtract(packet,"ST",&ok);
                if(!ok) {request = 5;}
			}
			//CN提取
            if(request == -1) {
				CN = fieldExtract(packet,"CN",&ok).toInt();
                if(!ok) {request = 9;}
			}
            if(request == -1) {
				if(CN < 9000) {
                    if(ST != deviceST()) {request = 5;}
				} else {
                    if(ST != "91") {request = 5;}
				}
			}
			//PW提取
            if(request == -1) {
				PW = fieldExtract(packet,"PW",&ok);
                if(!ok || (ok && PW.length()!=6) || (ok && PW.length()==6 && PW!=pw)) {request = 3;}
			}
			//MN提取
            if(request == -1) {
				MN = fieldExtract(packet,"MN",&ok);
                if(!ok || (ok && MN.length()!=24) || (ok && MN.length()==24 && MN!=mn)) {request = 4;}
			}
			//Flag提取
            if(request == -1) {
				Flag = fieldExtract(packet,"Flag",&ok).toInt();
                if(!ok || (ok && (Flag>>2)!=ver)) {request = 6;}
			}
			//PNUM提取
            if((request == -1)&&((Flag&0x02)==0x02)) {
				PNUM = fieldExtract(packet,"PNUM",&ok).toInt();
                if(!ok) {request = 100;}
			}
			//PNO提取
            if((request == -1)&&((Flag&0x02)==0x02)) {
				PNO = fieldExtract(packet,"PNO",&ok).toInt();
                if(!ok) {request = 100;}
			}
            if((request == -1) && (PNUM < PNO)) {request = 100;}
			//CP提取
            if(request == -1) {
				int ps = packet.indexOf("CP=&&",0);
				int pe = packet.indexOf("&&",ps+5);
				if((ps != -1) && (pe != -1)) {
                    pe += 2;
					CP = packet.mid(ps,pe-ps);
                } else {request = 100;}
			}
            if((Flag&0x01)==0x01) {request =1;} else {request = 0;}
            if(device()==NULL) {setRequest(request);} else {device()->setRequest(request);}
            if(request==0 || request==1) {state = true;}
        }
    }
    return state;
}
//报文打包
QString UserPacket::packetPack()
{
    if(device()==NULL) {
        MN = deviceMN();
        PW = devicePW();
        ST = deviceST();
        //Flag &= 0x03;
        //Flag = (version()<<2);
    } else {
        MN = device()->deviceMN();
        PW = device()->devicePW();
        ST = device()->deviceST();
        Flag &= 0x03;
        Flag |= (device()->version()<<2);
    }
    QString packet;
    packet.clear();
    if(version()==0) { //HJ/T212-2005标准
        if(direction()==Upper) { //服务器端
            if(CN<9000) {
				packet += QString("QN=%1;").arg(QN);
				packet += QString("ST=%1;").arg(ST);
				packet += QString("CN=%1;").arg(QString::number(CN));
				packet += QString("PW=%1;").arg(PW);
				packet += QString("MN=%1;").arg(MN);
				if(CN!=2012 && CN!=2022) {
					packet += QString("Flag=%1;").arg(QString::number(Flag));
				}
				packet += QString("CP=&&%1&&").arg(CP);
            } else if(CN==9013){
				packet += QString("ST=91;");
				packet += QString("CN=%1;").arg(QString::number(CN));
				packet += QString("PW=%1;").arg(PW);
				packet += QString("MN=%1;").arg(MN);
				packet += QString("Flag=0;");
				packet += QString("CP=&&QN=%1&&").arg(QN);							
			} else if(CN==9014) {
				packet += QString("ST=91;");
				packet += QString("CN=%1;").arg(QString::number(CN));		
				packet += QString("CP=&&QN=%1;%2&&").arg(QN).arg(CP);
			}
        } else if(direction()==Lower) { //数采仪端
			if(CN<9000) {
				if(CN==2072) {
					packet += QString("QN=%1;").arg(QN);
					packet += QString("ST=%1;").arg(ST);
					packet += QString("CN=%1;").arg(QString::number(CN));
					packet += QString("PW=%1;").arg(PW);
					packet += QString("MN=%1;").arg(MN);
					packet += QString("Flag=%1;").arg(QString::number(Flag));
					packet += QString("CP=&&%1&&").arg(CP);
				} else {
					packet += QString("ST=%1;").arg(ST);
					packet += QString("CN=%1;").arg(QString::number(CN));
					packet += QString("PW=%1;").arg(PW);
					packet += QString("MN=%1;").arg(MN);
					if(CN>=2000 && CN<3000) {
						packet += QString("CP=&&%1&&").arg(CP);	
					} else {
						packet += QString("CP=&&QN=%1;%2&&").arg(QN).arg(CP);
					}
				}
			} else if(CN==9011){
				packet += QString("ST=91;");
				packet += QString("CN=%1;").arg(QString::number(CN));
				packet += QString("PW=%1;").arg(PW);
				packet += QString("MN=%1;").arg(MN);
				packet += QString("Flag=0;");				
				packet += QString("CP=&&QN=%1;%2&&").arg(QN).arg(CP);
			} else if(CN==9012) {
				packet += QString("ST=91;");
				packet += QString("CN=%1;").arg(QString::number(CN));
				packet += QString("PW=%1;").arg(PW);
				packet += QString("MN=%1;").arg(MN);		
				packet += QString("CP=&&QN=%1;%2&&").arg(QN).arg(CP);
			} else if(CN==9013) {
				packet += QString("ST=91;");
				packet += QString("CN=%1;").arg(QString::number(CN));
				packet += QString("PW=%1;").arg(PW);
				packet += QString("MN=%1;").arg(MN);
				packet += QString("CP=&&QN=%1&&").arg(QN);		
			}
        }
    } else if(version()==1) { //HJ/T212-2016标准
		packet += QString("QN=%1;").arg(QN);
		if(CN < 9000) {
			packet += QString("ST=%1;").arg(ST);
		} else {
			packet += QString("ST=91;");
		}
		packet += QString("CN=%1;").arg(QString::number(CN));
		packet += QString("PW=%1;").arg(PW);
		packet += QString("MN=%1;").arg(MN);
		if(CN < 9000) {
			packet += QString("Flag=%1;").arg(QString::number(Flag));
			if(Flag==6 || Flag==7) {
				packet += QString("PNUM=%1;").arg(QString::number(PNUM));
				packet += QString("PNO=%1;").arg(QString::number(PNO));
			}
		} else {
			packet += QString("Flag=4;");
		}
		packet += QString("CP=&&%1&&").arg(CP);
	}
    return packet;
}

//CRC校验计算
int UserPacket::packetVerifyCalculate(QString packet)
{
    QChar *pstr = packet.data();
    int result = 0xffff;
    while(!pstr->isNull()) {
        result >>= 8;
        result ^= pstr->unicode();
        ++pstr;
        for(int j=0;j<8;j++) {
            bool flag = (result&0x0001)==0x0001 ? true : false;
            result >>= 1;
            if(flag) {result ^= 0xA001;}
        }
     }
     return result;
}

void UserPacket::setPacketQN()
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString rand = QString("%1").arg(qrand()%256,3,10,QLatin1Char('0'));
    QN = timestamp + rand;
}
//是否应答,是否拆包设置
void UserPacket::setReplyAndSplit(bool reply,bool split)
{
    Flag &= 0xFC;
    if(split) {Flag |= 0x02;}
    if(reply) {Flag |= 0x01;}
}
