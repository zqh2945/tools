#include "userdefaultparameter.h"

UserDefaultParameter::UserDefaultParameter(QObject *parent) : QObject(parent)
{

}

UserDefaultParameter::~UserDefaultParameter()
{

}

QStringList UserDefaultParameter::toPollutantConfig(const QString &code,const QString &name,int type,const QString &dUnit,int dDot)
{
    QStringList list;
    list.append(code);
    list.append(name);
    list.append(QString::number(type));
    list.append(dUnit);
    list.append(QString::number(dDot));
    list.append("/");
    list.append("/");
    return list;
}

QStringList UserDefaultParameter::toPollutantConfig(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,const QString qUnit,int qDot)
{
    QStringList list;
    list.append(code);
    list.append(name);
    list.append(QString::number(type));
    list.append(dUnit);
    list.append(QString::number(dDot));
    list.append(qUnit);
    list.append(QString::number(qDot));
    return list;
}

QList<QStringList> UserDefaultParameter::pollutantConfigList(int version,const QString &st)
{
    QList<QStringList> list;
    if(version==1) {
        if(st=="21" || st=="24" || st=="26") {
            list.append(toPollutantConfig("w01001","氢离子浓度指数pH",3,"",2));
            list.append(toPollutantConfig("w01018","化学需氧量",1,"mg/L",1));
            list.append(toPollutantConfig("w21003","氨氮",1,"mg/L",2));
            list.append(toPollutantConfig("w21011","总磷",1,"mg/L",3));
            list.append(toPollutantConfig("w21001","总氮",1,"mg/L",2));
        } else if(st=="22") {
            list.append(toPollutantConfig("a21026","二氧化硫",1,"ug/m3",1));
            list.append(toPollutantConfig("a21002","氮氧化物",1,"ug/m3",1));
            list.append(toPollutantConfig("a21003","一氧化碳",1,"mg/m3",3));
            list.append(toPollutantConfig("a34001","总悬浮颗粒物TSP",1,"ug/m3",3));
            list.append(toPollutantConfig("a34002","可吸入颗粒物PM10",1,"ug/m3",3));
            list.append(toPollutantConfig("a34003","可吸入颗粒物PM5",1,"ug/m3",3));
            list.append(toPollutantConfig("a34004","可吸入颗粒物PM2.5",1,"ug/m3",3));
            list.append(toPollutantConfig("a34005","可吸入颗粒物PM1.0",1,"ug/m3",3));
        } else if(st=="23" || st=="36") {
            list.append(toPollutantConfig("n00000","A权声级",1,"dB",1));
            list.append(toPollutantConfig("n00001","累计百分声级L5",1,"dB",1));
            list.append(toPollutantConfig("n00002","累计百分声级L10",1,"dB",1));
            list.append(toPollutantConfig("n00003","累计百分声级L50",1,"dB",1));
            list.append(toPollutantConfig("n00004","累计百分声级L90",1,"dB",1));
            list.append(toPollutantConfig("n00005","累计百分声级L95",1,"dB",1));
            list.append(toPollutantConfig("n00006","等效声级",1,"dB",1));
            list.append(toPollutantConfig("n00007","昼夜等效声级",1,"dB",1));
            list.append(toPollutantConfig("n00008","昼间等效声级",1,"dB",1));
            list.append(toPollutantConfig("n00009","夜间等效声级",1,"dB",1));
            list.append(toPollutantConfig("n00010","最大的瞬时声级",1,"dB",1));
            list.append(toPollutantConfig("n00011","最小的瞬时声级",1,"dB",1));
        } else if(st=="25" || st=="35") {
            list.append(toPollutantConfig("s00001","镉",1,"mg/kg",2));
            list.append(toPollutantConfig("s00002","汞",1,"mg/kg",2));
            list.append(toPollutantConfig("s00003","砷",1,"mg/kg",3));
            list.append(toPollutantConfig("s00004","铜",1,"mg/kg",3));
            list.append(toPollutantConfig("s00005","铅",1,"mg/kg",3));
            list.append(toPollutantConfig("s00006","铬",1,"mg/kg",3));
            list.append(toPollutantConfig("s00007","锌",1,"mg/kg",3));
            list.append(toPollutantConfig("s00008","镍",1,"mg/kg",3));
            list.append(toPollutantConfig("s00009","六六六",1,"mg/kg",3));
            list.append(toPollutantConfig("s00010","滴滴涕",1,"mg/kg",3));
		} else if(st=="27") {
        
		} else if(st=="31") {
            list.append(toPollutantConfig("a00000","烟气排量",0,"m3/s",3,"m3",1));
            list.append(toPollutantConfig("a21026","二氧化硫",2,"mg/m3",3,"kg",1));
            list.append(toPollutantConfig("a21002","氮氧化物",2,"mg/m3",3,"kg",1));
            list.append(toPollutantConfig("a01011","烟气流速",3,"m/s",2));
            list.append(toPollutantConfig("a01012","烟气温度",3,"℃",1));
            list.append(toPollutantConfig("a01014","烟气湿度",3,"%",1));
            list.append(toPollutantConfig("a01017","烟气动压",3,"kPa",3));
            list.append(toPollutantConfig("a19001","氧气含量",3,"%",1));
        } else if(st=="32") {
            list.append(toPollutantConfig("w00000","污水流量",0,"L/s",3,"t",3));
            list.append(toPollutantConfig("w01018","化学需氧量",1,"mg/L",1,"kg",1));
            list.append(toPollutantConfig("w21003","氨氮",1,"mg/L",2,"kg",2));
            list.append(toPollutantConfig("w21011","总磷",1,"mg/L",3,"kg",3));
            list.append(toPollutantConfig("w21001","总氮",1,"mg/L",2,"kg",2));
            list.append(toPollutantConfig("w01001","氢离子浓度指数pH",3,"",2));
        } else if(st=="33" || st=="34") {
            list.append(toPollutantConfig("w01001","氢离子浓度指数pH",1,"",2));
            list.append(toPollutantConfig("w01018","化学需氧量",1,"mg/L",1));
            list.append(toPollutantConfig("w21003","氨氮",1,"mg/L",2));
            list.append(toPollutantConfig("w21011","总磷",1,"mg/L",3));
            list.append(toPollutantConfig("w21001","总氮",1,"mg/L",2));
        } else if(st=="37") {

        } else if(st=="38") {
            list.append(toPollutantConfig("r00001","γ剂量率",1,"nGy/h",1));
            list.append(toPollutantConfig("r00002","综合电场强度",1,"V/m",1));
            list.append(toPollutantConfig("r00003","综合电场功率密度",1,"uW/cm2",1));
        } else if(st=="39") {
            list.append(toPollutantConfig("a34012","粉尘",1,"mg/m3",3));
            list.append(toPollutantConfig("a34001","总悬浮颗粒物TSP",1,"mg/m3",3));
            list.append(toPollutantConfig("a34002","可吸入颗粒物PM10",1,"mg/m3",3));
            list.append(toPollutantConfig("a34003","可吸入颗粒物PM5",1,"mg/m3",3));
            list.append(toPollutantConfig("a34004","可吸入颗粒物PM2.5",1,"mg/m3",3));
            list.append(toPollutantConfig("a34005","可吸入颗粒物PM1.0",1,"mg/m3",3));
        } else if(st=="41") {

        } else if(st=="51") {

        } else if(st=="52") {

        }
    } else if(version==0) {
        if(st=="21" || st=="24" || st=="26") {
            list.append(toPollutantConfig("001","氢离子浓度指数pH",1,"",2));
            list.append(toPollutantConfig("011","化学需氧量",1,"mg/L",1));
            list.append(toPollutantConfig("060","氨氮",1,"mg/L",2));
            list.append(toPollutantConfig("101","总磷",1,"mg/L",3));
            list.append(toPollutantConfig("065","总氮",1,"mg/L",2));
        } else if(st=="22") {
            list.append(toPollutantConfig("02","二氧化硫",1,"ug/m3",1));
            list.append(toPollutantConfig("03","氮氧化物",1,"ug/m3",1));
            list.append(toPollutantConfig("04","一氧化碳",1,"mg/m3",3));
        } else if(st=="23" || st=="36") {
            list.append(toPollutantConfig("B03","A权声级",1,"dB",1));
            list.append(toPollutantConfig("L5","累计百分声级L5",1,"dB",1));
            list.append(toPollutantConfig("L10","累计百分声级L10",1,"dB",1));
            list.append(toPollutantConfig("L50","累计百分声级L50",1,"dB",1));
            list.append(toPollutantConfig("L90","累计百分声级L90",1,"dB",1));
            list.append(toPollutantConfig("L95","累计百分声级L95",1,"dB",1));
            list.append(toPollutantConfig("Leq","等效声级",1,"dB",1));
            list.append(toPollutantConfig("Ldn","昼夜等效声级",1,"dB",1));
            list.append(toPollutantConfig("Ln","昼间等效声级",1,"dB",1));
            list.append(toPollutantConfig("Ld","夜间等效声级",1,"dB",1));
            list.append(toPollutantConfig("LMn","最大的瞬时声级",1,"dB",1));
            list.append(toPollutantConfig("LMx","最小的瞬时声级",1,"dB",1));
        } else if(st=="25" || st=="35") {
		
        } else if(st=="31") {
            list.append(toPollutantConfig("B02","烟气排量",0,"m3/s",3,"m3",1));
            list.append(toPollutantConfig("02","二氧化硫",2,"mg/m3",3,"kg",1));
            list.append(toPollutantConfig("03","氮氧化物",2,"mg/m3",3,"kg",1));
            list.append(toPollutantConfig("S02","烟气流速",3,"m/s",2));
            list.append(toPollutantConfig("S03","烟气温度",3,"℃",1));
            list.append(toPollutantConfig("S05","烟气湿度",3,"%",1));
            list.append(toPollutantConfig("S08","烟气动压",3,"kPa",3));
            list.append(toPollutantConfig("S01","氧气含量",3,"%",1));
        } else if(st=="32") {
            list.append(toPollutantConfig("B01","污水流量",0,"L/s",3,"t",3));
            list.append(toPollutantConfig("011","化学需氧量",1,"mg/L",1,"kg",1));
            list.append(toPollutantConfig("060","氨氮",1,"mg/L",2,"kg",2));
            list.append(toPollutantConfig("101","总磷",1,"mg/L",3,"kg",3));
            list.append(toPollutantConfig("065","总氮",1,"mg/L",2,"kg",2));
            list.append(toPollutantConfig("001","氢离子浓度指数pH",3,"",2));
        } else if(st=="33" || st=="34") {
            list.append(toPollutantConfig("001","氢离子浓度指数pH",1,"",2));
            list.append(toPollutantConfig("011","化学需氧量",1,"mg/L",1));
            list.append(toPollutantConfig("060","氨氮",1,"mg/L",2));
            list.append(toPollutantConfig("101","总磷",1,"mg/L",3));
            list.append(toPollutantConfig("065","总氮",1,"mg/L",2));
        } else if(st=="37") {

        } else if(st=="38") {

        } else if(st=="41") {

        }
    }
    return list;
}

