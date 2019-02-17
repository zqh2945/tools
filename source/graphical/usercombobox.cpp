#include "usercombobox.h"
#include <QDebug>

UserComboBox::UserComboBox(enum ListType type)
{
	setCurrentIndex(-1);
    clear();
    setItemList(type);
    setAllItem(type);
}

UserComboBox::UserComboBox(enum ListType type,int version)
{
	setCurrentIndex(-1);
    clear();
    setItemList(type,version);
    setAllItem(type);
}

UserComboBox::UserComboBox(enum ListType type,int version,const QString &st)
{
	setCurrentIndex(-1);
    clear();
    setItemList(type,version,st);
    setAllItem(type);
}

UserComboBox::UserComboBox(enum ListType type,int version,const QString &st,const QString &argType)
{
	setCurrentIndex(-1);
    clear();
    setItemList(type,version,st,argType);
    setAllItem(type);
}

UserComboBox::~UserComboBox()
{
	
}

void UserComboBox::setItems(enum ListType type,int version)
{
	setCurrentIndex(-1);
	clear();
    setItemList(type,version);
    setAllItem(type);
}

void UserComboBox::setItems(enum ListType type,int version,const QString &st)
{
	setCurrentIndex(-1);
	clear();
    setItemList(type,version,st);
    setAllItem(type);
}

void UserComboBox::setItems(enum ListType type,int version,const QString &st,const QString &argType)
{
	setCurrentIndex(-1);
	clear();
    setItemList(type,version,st,argType);
    setAllItem(type);
}

//标准版本编码
bool UserComboBox::setItemList(enum ListType type)
{
    bool ok = false;
    itemList.clear();
    strDataList.clear();
    intDataList.clear();
	if(type==PROTOCOL) { //HJT212标准版本
		intDataList.append(0); itemList.append("HJ/T212-2005");
        intDataList.append(1); itemList.append("HJ/T212-2016");
		ok = true;
    } else if(type==DEVICE_POLLUTANT_TYPE) { //污染监测因子类型
        intDataList.append(0); itemList.append("流量排量类(0)");
        intDataList.append(1); itemList.append("监测因子类(1)");
        intDataList.append(2); itemList.append("监测因子类[折算](2)");
        intDataList.append(3); itemList.append("辅助因子类(3)");
        intDataList.append(4); itemList.append("工况类(4)");
        ok = true;
    }
	return ok;
}

//基本字段编码
bool UserComboBox::setItemList(enum ListType type,int prot)
{
    bool ok = false;
    itemList.clear();
    strDataList.clear();
    intDataList.clear();
	if((type==SERVER_ST || type==CLIENT_ST) && (prot==1)) { //系统编号
        strDataList.append("21"); itemList.append("地表水质量监测(21)");
        strDataList.append("22"); itemList.append("空气质量监测(22)");
        strDataList.append("23"); itemList.append("声环境质量监测(23)");
        strDataList.append("24"); itemList.append("地下水质量监测(24)");
        strDataList.append("25"); itemList.append("土壤质量监测(25)");
        strDataList.append("26"); itemList.append("海水质量监测(26)");
		strDataList.append("27"); itemList.append("挥发性有机物监测(27)");
        strDataList.append("31"); itemList.append("大气污染源(31)");
        strDataList.append("32"); itemList.append("地表水污染源(32)");
        strDataList.append("33"); itemList.append("地下水污染源(33)");
        strDataList.append("34"); itemList.append("海洋污染源(34)");
        strDataList.append("35"); itemList.append("土壤污染源(35)");
        strDataList.append("36"); itemList.append("噪声污染源(36)");
        strDataList.append("37"); itemList.append("振动污染源(37)");
        strDataList.append("38"); itemList.append("放射性污染源(38)");
        strDataList.append("39"); itemList.append("工地扬尘污染源(39)");
        strDataList.append("41"); itemList.append("电磁污染源(41)");
        strDataList.append("51"); itemList.append("烟气处理(工况)监控(51)");
        strDataList.append("52"); itemList.append("污水处理(工况)监控(52)");
        ok = true;
    } else if((type==SERVER_ST || type==CLIENT_ST) && (prot==0)) {
		strDataList.append("21"); itemList.append("地表水质量监测(21)");
        strDataList.append("22"); itemList.append("空气质量监测(22)");
        strDataList.append("23"); itemList.append("声环境质量监测(23)");
        strDataList.append("24"); itemList.append("地下水质量监测(24)");
        strDataList.append("25"); itemList.append("土壤质量监测(25)");
        strDataList.append("26"); itemList.append("海水质量监测(26)");
        strDataList.append("31"); itemList.append("大气污染源(31)");
        strDataList.append("32"); itemList.append("地表水污染源(32)");
        strDataList.append("33"); itemList.append("地下水污染源(33)");
        strDataList.append("34"); itemList.append("海洋污染源(34)");
        strDataList.append("35"); itemList.append("土壤污染源(35)");
        strDataList.append("36"); itemList.append("噪声污染源(36)");
        strDataList.append("37"); itemList.append("振动污染源(37)");
        strDataList.append("38"); itemList.append("放射性污染源(38)");
		strDataList.append("41"); itemList.append("电磁污染源(41)");
        ok = true;
    } else if(type==SERVER_CN && prot==1) { //上位机命令编号
        intDataList.append(1000); itemList.append("超时时间及重发次数设置请求(1000)");
        intDataList.append(1011); itemList.append("数采仪时间查询请求(1011)");
        intDataList.append(1012); itemList.append("数采仪时间设置请求(1012)");
        intDataList.append(1013); itemList.append("数采仪时间校准响应(1013)");
        intDataList.append(1061); itemList.append("实时数据上报时间间隔查询请求(1061)");
        intDataList.append(1062); itemList.append("实时数据上报时间间隔设置请求(1062)");
        intDataList.append(1063); itemList.append("分钟数据上报时间间隔查询请求(1063)");
        intDataList.append(1064); itemList.append("分钟数据上报时间间隔设置请求(1064)");
        intDataList.append(1072); itemList.append("现场机密码设置请求(1072)");
        intDataList.append(2011); itemList.append("实时数据上报使能请求(2011)");
        intDataList.append(2012); itemList.append("实时数据上报禁止请求(2012)");
        intDataList.append(2021); itemList.append("污染治理设施运行状态上报使能请求(2021)");
        intDataList.append(2022); itemList.append("污染治理设施运行状态上报禁止请求(2022)");
        intDataList.append(2031); itemList.append("历史日数据请求(2031)");
		intDataList.append(2051); itemList.append("历史分钟数据请求(2051)");
        intDataList.append(2061); itemList.append("历史小时数据请求(2061)");
        intDataList.append(2041); itemList.append("历史染治理设施日运行时间请求(2041)");
        intDataList.append(3011); itemList.append("在线监控(监测)仪器仪表校零校满请求(3011)");
        intDataList.append(3012); itemList.append("在线监控(监测)仪器仪表即时采样请求(3012)");
        intDataList.append(3013); itemList.append("在线监控(监测)仪器仪表启动清洗请求(3013)");
        intDataList.append(3014); itemList.append("在线监控(监测)仪器仪表比对采样请求(3014)");
        intDataList.append(3015); itemList.append("在线监控(监测)仪器仪表超标留样启动请求(3015)");
        intDataList.append(3016); itemList.append("在线监控(监测)仪器仪表超标留样停止请求(3016)");
        intDataList.append(3017); itemList.append("在线监控(监测)仪器仪表时间校准请求(3017)");
        intDataList.append(3018); itemList.append("在线监控(监测)仪器仪表采样时间间隔设置请求(3018)");
        intDataList.append(3019); itemList.append("在线监控(监测)仪器仪表采样时间间隔查询请求(3019)");
        intDataList.append(3020); itemList.append("在线监控(监测)仪器仪表出样时间间隔查询请求(3020)");
        intDataList.append(3021); itemList.append("在线监控(监测)仪器仪表设备唯一标识查询请求(3021)");
        intDataList.append(3022); itemList.append("现场机信息查询请求(3022)");
        intDataList.append(9014); itemList.append("数据上报响应(9014)");
        ok = true;
    } else if(type==SERVER_CN && prot==0) {
		intDataList.append(1000); itemList.append("设置超时时间及重发次数(1000)");
        intDataList.append(1011); itemList.append("提取现场机时间(1011)");
        intDataList.append(1012); itemList.append("设置现场机时间(1012)");
		intDataList.append(1021); itemList.append("提取污染物报警门限值(1021)");
		intDataList.append(1022); itemList.append("设置污染物报警门限值(1022)");
		intDataList.append(1031); itemList.append("提取上位机地址(1031)");
		intDataList.append(1032); itemList.append("设置上位机地址(1032)");
		intDataList.append(1041); itemList.append("提取数据上报时间(1041)");
		intDataList.append(1042); itemList.append("设置数据上报时间(1042)");
		intDataList.append(1061); itemList.append("提取实时数据上报间隔(1061)");
		intDataList.append(1062); itemList.append("设置实时数据上报间隔(1062)");
		intDataList.append(1072); itemList.append("设置访问密码(1072)");
		intDataList.append(2011); itemList.append("取污染物实时数据(2011)");
        intDataList.append(2012); itemList.append("停止察看污染物实时数据(2012)");
        intDataList.append(2021); itemList.append("取污染治理设施运行状态(2021)");
        intDataList.append(2022); itemList.append("停止察看污染治理设施运行状态(2022)");
        intDataList.append(2031); itemList.append("历史日数据请求(2031)");
		intDataList.append(2051); itemList.append("历史分钟数据请求(2051)");
        intDataList.append(2061); itemList.append("历史小时数据请求(2061)");
        intDataList.append(2041); itemList.append("历史染治理设施日运行时间请求(2041)");
		intDataList.append(2071); itemList.append("历史污染物报警记录请求(2071)");
		intDataList.append(3011); itemList.append("校零校满(3011)");
        intDataList.append(3012); itemList.append("即时采样(3012)");
        intDataList.append(3013); itemList.append("设备操作(3013)");
        intDataList.append(3014); itemList.append("设置设备采样时间周期(3014)");
		intDataList.append(9013); itemList.append("通知响应(9013)");
		intDataList.append(9014); itemList.append("数据响应(9014)");
		
        ok = true;
    } else if(type==CLIENT_CN && prot==1) { //下位机命令编号
        intDataList.append(1011); itemList.append("数采仪时间查询响应(1011)");
        intDataList.append(1013); itemList.append("数采仪时间校准请求(1013)");
        intDataList.append(1061); itemList.append("实时数据上报时间间隔查询响应(1061)");
        intDataList.append(1063); itemList.append("分钟数据上报时间间隔查询响应(1063)");
        intDataList.append(2011); itemList.append("实时数据上报(2011)");
		intDataList.append(2031); itemList.append("日数据上报(2031)");
        intDataList.append(2051); itemList.append("分钟数据上报(2051)");
        intDataList.append(2061); itemList.append("小时数据上报(2061)");
        intDataList.append(2021); itemList.append("污染治理运行状态上报(2021)");
        intDataList.append(2041); itemList.append("污染治理日云行时间上报(2041)");
        intDataList.append(2081); itemList.append("数采仪开机时间上报(2081)");
        intDataList.append(3019); itemList.append("在线监控(监测)仪器仪表采样时间间隔查询响应(3019)");
        intDataList.append(3020); itemList.append("在线监控(监测)仪器仪表出样时间间隔查询响应(3020)");
		intDataList.append(3021); itemList.append("在线监控(监测)仪器仪表设备唯一标识查询响应(3021)");
        intDataList.append(3022); itemList.append("现场机信息查询响应(3022)");
        intDataList.append(9011); itemList.append("指令请求响应(9011)");
        intDataList.append(9012); itemList.append("指令执行响应(9012)");
        ok = true;
    } else if(type==CLIENT_CN && prot==0) { //标志位编号
		intDataList.append(1011); itemList.append("上传现场机时间(1011)");
		intDataList.append(1021); itemList.append("上传污染物报警门限值(1021)");
		intDataList.append(1031); itemList.append("上传上位机地(1031)");
		intDataList.append(1041); itemList.append("上传数据上报时间(1041)");
		intDataList.append(1061); itemList.append("上传实时数据间隔(1061)");
		intDataList.append(2011); itemList.append("实时数据上报(2011)");
		intDataList.append(2031); itemList.append("日数据上报(2031)");
        intDataList.append(2051); itemList.append("分钟数据上报(2051)");
        intDataList.append(2061); itemList.append("小时数据上报(2061)");
        intDataList.append(2021); itemList.append("污染治理运行状态上报(2021)");
        intDataList.append(2041); itemList.append("污染治理日云行时间上报(2041)");
		intDataList.append(2071); itemList.append("上传污染物报警记录(2071)");
		intDataList.append(2072); itemList.append("上传报警事件(2072)");
		intDataList.append(9011); itemList.append("请求应答(9011)");
        intDataList.append(9012); itemList.append("执行结果(9012)");
        intDataList.append(9013); itemList.append("通知应答(9012)");
        ok = true;
    } else if((type==SERVER_FLAG || type==CLIENT_FLAG) && (prot==1)) {
        intDataList.append(4); itemList.append("无拆分、无应答(4)");
        intDataList.append(5); itemList.append("无拆分、有应答(5)");
        intDataList.append(6); itemList.append("有拆分、无应答(6)");
        intDataList.append(7); itemList.append("有拆分、有应答(7)");
        ok = true;
    } else if((type==SERVER_FLAG || type==CLIENT_FLAG) && (prot==0)) {
		intDataList.append(0); itemList.append("无拆分、无应答(0)");
        intDataList.append(1); itemList.append("无拆分、有应答(1)");
        intDataList.append(2); itemList.append("有拆分、无应答(2)");
        intDataList.append(3); itemList.append("有拆分、有应答(3)");
        ok = true;
	} else if(type==DEVICE_OVERTIME && (prot==1 || prot==0)) { //超时时间
		intDataList.append(3); itemList.append("3(s)");
		intDataList.append(5); itemList.append("5(s)");
		intDataList.append(10); itemList.append("10(s)");
		ok = true;
	} else if(type==DEVICE_RECOUNT && (prot==1 || prot==0)) { //重发次数
		intDataList.append(1); itemList.append("1");
		intDataList.append(2); itemList.append("2");
		intDataList.append(3); itemList.append("3");
		intDataList.append(4); itemList.append("4");
		intDataList.append(5); itemList.append("5");
		ok = true;
	} else if(type==DEVICE_REALCYCLE && (prot==1 || prot==0)) { //实时数据周期
		intDataList.append(30); itemList.append("30(s)");
		intDataList.append(60); itemList.append("60(s)");
		intDataList.append(90); itemList.append("90(s)");
		intDataList.append(120); itemList.append("120(s)");
		intDataList.append(150); itemList.append("150(s)");
		intDataList.append(180); itemList.append("180(s)");
		intDataList.append(240); itemList.append("240(s)");
		intDataList.append(300); itemList.append("300(s)");
		intDataList.append(600); itemList.append("600(s)");
		intDataList.append(900); itemList.append("900(s)");
		intDataList.append(1200); itemList.append("1200(s)");
		intDataList.append(1500); itemList.append("1500(s)");
		intDataList.append(1800); itemList.append("1800(s)");
		intDataList.append(2400); itemList.append("2400(s)");
		intDataList.append(3000); itemList.append("3000(s)");
		intDataList.append(3600); itemList.append("3600(s)");
		ok = true;
	} else if(type==DEVICE_MINCYCLE && (prot==1 || prot==0)) { //分钟数据周期
		intDataList.append(1); itemList.append("1(m)");
		intDataList.append(2); itemList.append("2(m)");
		intDataList.append(3); itemList.append("3(m)");
		intDataList.append(4); itemList.append("4(m)");
		intDataList.append(5); itemList.append("5(m)");
		intDataList.append(6); itemList.append("6(m)");
		intDataList.append(10); itemList.append("10(m)");
		intDataList.append(12); itemList.append("12(m)");
		intDataList.append(15); itemList.append("15(m)");
		intDataList.append(20); itemList.append("20(m)");
		intDataList.append(30); itemList.append("30(m)");
		ok = true;
	} else if(type==DEVICE_SAMPLING_CYCLE && (prot==1 || prot==0)) { //数据精度
		intDataList.append(1); itemList.append("1(h)");
		intDataList.append(2); itemList.append("2(h)");
		intDataList.append(3); itemList.append("3(h)");
		ok = true;
    } else if(type==DEVICE_UNIT && (prot==1 || prot==0)) { //计量单位
        strDataList.append("/"); itemList.append("/");
		strDataList.append(""); itemList.append("无量纲");
        strDataList.append("ug"); itemList.append("微克");
        strDataList.append("mg"); itemList.append("毫克");
        strDataList.append("g"); itemList.append("克");
        strDataList.append("kg"); itemList.append("千克");
        strDataList.append("t"); itemList.append("吨");
        strDataList.append("L"); itemList.append("升");
        strDataList.append("L/s"); itemList.append("升/秒");
        strDataList.append("ug/L"); itemList.append("微克/升");
        strDataList.append("mg/L"); itemList.append("毫克/升");
        strDataList.append("g/L"); itemList.append("克/升");
        strDataList.append("kg/L"); itemList.append("千克/升");
        strDataList.append("m3"); itemList.append("立方米");
        strDataList.append("m3/s"); itemList.append("立方米/秒");
        strDataList.append("ug/m3"); itemList.append("微克/立方米");
        strDataList.append("mg/m3"); itemList.append("毫克/立方米");
        strDataList.append("g/m3"); itemList.append("克/立方米");
        strDataList.append("kg/m3"); itemList.append("千克/立方米");
		strDataList.append("m"); itemList.append("米");
		strDataList.append("m/s"); itemList.append("米/秒");
        strDataList.append("%"); itemList.append("百分比");
        strDataList.append("℃"); itemList.append("摄氏度");
        strDataList.append("Pa"); itemList.append("帕");
        strDataList.append("kPa"); itemList.append("千帕");
		strDataList.append("dB"); itemList.append("分贝");
		strDataList.append("mg/kg"); itemList.append("毫克/千克");
		strDataList.append("nGy/h"); itemList.append("纳戈/小时");
		strDataList.append("V/m"); itemList.append("伏/米");
		strDataList.append("uW/cm2"); itemList.append("微瓦/平方厘米");
        ok = true;
    } else if(type==DEVICE_PRECISION && (prot==1 || prot==0)) { //数据精度
		strDataList.append("/"); itemList.append("/");
		strDataList.append("0"); itemList.append("整数");
        strDataList.append("1"); itemList.append("1位精度的浮点数");
        strDataList.append("2"); itemList.append("2位精度的浮点数");
        strDataList.append("3"); itemList.append("3位精度的浮点数");
        strDataList.append("4"); itemList.append("4位精度的浮点数");
        strDataList.append("5"); itemList.append("5位精度的浮点数");
        strDataList.append("6"); itemList.append("6位精度的浮点数");
        strDataList.append("7"); itemList.append("7位精度的浮点数");
        strDataList.append("8"); itemList.append("8位精度的浮点数");
        strDataList.append("9"); itemList.append("9位精度的浮点数");
        ok = true;
    }
    return ok;
}

//监测因子编码
bool UserComboBox::setItemList(enum ListType type,int prot,const QString &st)
{
    bool ok = false;
    itemList.clear();
    strDataList.clear();
    intDataList.clear();
	if(type==DEVICE_POLLUTANT && prot==1) { //污染监测因子编号
        if(st=="22" || st=="31" || st=="39") { //大气污染源
            strDataList.append("a00000"); itemList.append("烟气排量(a00000)");
			strDataList.append("a01001"); itemList.append("温度(a01001)");
			strDataList.append("a01002"); itemList.append("湿度(a01002)");
			strDataList.append("a01006"); itemList.append("气压(a01006)");
			strDataList.append("a01007"); itemList.append("风速(a01007)");
			strDataList.append("a01008"); itemList.append("风向(a01008)");
			strDataList.append("a01011"); itemList.append("烟气流速(a01011)");
			strDataList.append("a01012"); itemList.append("烟气温度(a01012)");
			strDataList.append("a01013"); itemList.append("烟气压力(a01013)");
			strDataList.append("a01014"); itemList.append("烟气湿度(a01014)");
			strDataList.append("a01015"); itemList.append("制冷温度(a01015)");
			strDataList.append("a01016"); itemList.append("烟道截面积(a01016)");
			strDataList.append("a01017"); itemList.append("烟气动压(a01017)");
			strDataList.append("a05001"); itemList.append("二氧化碳(a05001)");
			strDataList.append("a05002"); itemList.append("甲烷(a05002)");
			strDataList.append("a19001"); itemList.append("氧气含量(a19001)");
			strDataList.append("a21001"); itemList.append("氨气(a21001)");
			strDataList.append("a21002"); itemList.append("氮氧化物(a21002)");
			strDataList.append("a21003"); itemList.append("一氧化氮(a21003)");
			strDataList.append("a21004"); itemList.append("二氧化氮(a21004)");
			strDataList.append("a21005"); itemList.append("一氧化碳(a21005)");
			strDataList.append("a21017"); itemList.append("氰化物(a21017)");
			strDataList.append("a21018"); itemList.append("氟化物(a21018)");
			strDataList.append("a21022"); itemList.append("氯气(a21022)");
			strDataList.append("a21024"); itemList.append("氯化氢(a21024)");
			strDataList.append("a21026"); itemList.append("二氧化硫(a21026)");
			strDataList.append("a21028"); itemList.append("硫化氢(a21028)");
			strDataList.append("a34001"); itemList.append("总悬浮颗粒物TSP(a34001)");
			strDataList.append("a34002"); itemList.append("可吸入颗粒物PM10(a34002)");
			strDataList.append("a34003"); itemList.append("可吸入颗粒物PM5(a34003)");
			strDataList.append("a34004"); itemList.append("可吸入颗粒物PM2.5(a34004)");
			strDataList.append("a34005"); itemList.append("可吸入颗粒物PM1.0(a34005)");
			strDataList.append("a34011"); itemList.append("降尘(a34011)");
			strDataList.append("a34012"); itemList.append("粉尘(a34012)");
			strDataList.append("a34013"); itemList.append("烟尘(a34013)");
			strDataList.append("a34017"); itemList.append("炭黑尘(a34017)");
            ok = true;
        } else if(st=="21" || st=="24" || st== "26" || st=="32" || st=="33" || st=="34") { //水污染源
            strDataList.append("w00000"); itemList.append("污水流量(w00000)");
            strDataList.append("w01001"); itemList.append("氢离子浓度指数pH(w01001)");
            strDataList.append("w01002"); itemList.append("色度(w01002)");
            strDataList.append("w01012"); itemList.append("悬浮物(w01012)");
            strDataList.append("w01017"); itemList.append("五日生化需氧量(w01017)");
            strDataList.append("w01018"); itemList.append("化学需氧量(w01018)");
            strDataList.append("w01020"); itemList.append("总有机碳(w01020)");
            strDataList.append("w20012"); itemList.append("钡(w20012)");
            strDataList.append("w20023"); itemList.append("硼(w20023)");
            strDataList.append("w20038"); itemList.append("钴(w20038)");
            strDataList.append("w20061"); itemList.append("钼(w20061)");
            strDataList.append("w20089"); itemList.append("铊(w20089)");
            strDataList.append("w20092"); itemList.append("锡(w20092)");
            strDataList.append("w20111"); itemList.append("总汞(w20111)");
            strDataList.append("w20113"); itemList.append("烷基汞(w20113)");
            strDataList.append("w20115"); itemList.append("总镉(w20115)");
            strDataList.append("w20116"); itemList.append("总铬(w20116)");
            strDataList.append("w20117"); itemList.append("六价铬(w20117)");
            strDataList.append("w20119"); itemList.append("总砷(w20119)");
            strDataList.append("w20120"); itemList.append("总铅(w20120)");
            strDataList.append("w20121"); itemList.append("总镍(w20121)");
            strDataList.append("w20122"); itemList.append("总铜(w20122)");
            strDataList.append("w20123"); itemList.append("总锌(w20123)");
            strDataList.append("w20124"); itemList.append("总锰(w20124)");
            strDataList.append("w20125"); itemList.append("总铁(w20125)");
            strDataList.append("w20126"); itemList.append("总银(w20126)");
            strDataList.append("w20127"); itemList.append("总铍(w20127)");
            strDataList.append("w20128"); itemList.append("总硒(w20128)");
            strDataList.append("w21001"); itemList.append("总氮(w21001)");
            strDataList.append("w21003"); itemList.append("氨氮(w21003)");
            strDataList.append("w21011"); itemList.append("总磷(w21011)");
            strDataList.append("w21017"); itemList.append("氟化物(w21017)");
            strDataList.append("w21019"); itemList.append("硫化物(w21019)");
            strDataList.append("w22001"); itemList.append("石油类(w22001)");
            ok = true;
        } else if(st=="25" || st=="35") { //土壤污染源
            strDataList.append("s00001"); itemList.append("镉(s00001)");
			strDataList.append("s00002"); itemList.append("汞(s00002)");
			strDataList.append("s00003"); itemList.append("砷(s00003)");
			strDataList.append("s00004"); itemList.append("铜(s00004)");
			strDataList.append("s00005"); itemList.append("铅(s00005)");
			strDataList.append("s00006"); itemList.append("铬(s00006)");
			strDataList.append("s00007"); itemList.append("锌(s00007)");
			strDataList.append("s00008"); itemList.append("镍(s00008)");
			strDataList.append("s00009"); itemList.append("六六六(s00009)");
			strDataList.append("s00010"); itemList.append("滴滴涕(s00010)");
            ok = true;
        } else if(st=="23" || st=="36") { //噪声污染源
            strDataList.append("n00000"); itemList.append("A权声级(n00000)");
			strDataList.append("n00001"); itemList.append("累计百分声级L5(n00001)");
			strDataList.append("n00002"); itemList.append("累计百分声级L10(n00002)");
			strDataList.append("n00003"); itemList.append("累计百分声级L50(n00003)");
			strDataList.append("n00004"); itemList.append("累计百分声级L90(n00004)");
			strDataList.append("n00005"); itemList.append("累计百分声级L95(n00005)");
			strDataList.append("n00006"); itemList.append("等效声级(n00006)");
			strDataList.append("n00007"); itemList.append("昼夜等效声级(n00007)");
			strDataList.append("n00008"); itemList.append("昼间等效声级(n00008)");
			strDataList.append("n00009"); itemList.append("夜间等效声级(n00009)");
			strDataList.append("n00010"); itemList.append("最大的瞬时声级(n00010)");
			strDataList.append("n00011"); itemList.append("最小的瞬时声级(n00011)");
            ok = true;
        } else if(st=="38" || st=="41") { //辐射污染源
            strDataList.append("r00001"); itemList.append("γ剂量率(r00001)");
			strDataList.append("r00002"); itemList.append("综合电场强度(r00002)");
			strDataList.append("r00003"); itemList.append("综合电场功率密度(r00003)");
			strDataList.append("r00004"); itemList.append("降雨量(r00004)");
			strDataList.append("r00005"); itemList.append("大气压(r00005)");
			strDataList.append("r00006"); itemList.append("温度(r00006)");
			strDataList.append("r00007"); itemList.append("湿度(r00007)");
			strDataList.append("r00008"); itemList.append("风向(r00008)");
			strDataList.append("r00009"); itemList.append("风速(r00009)");
			strDataList.append("r00010"); itemList.append("中子通量(r00010)");
            ok = true;
        } else if(st=="51") { //烟气处理过程监控
			strDataList.append("g10101"); itemList.append("增压风机1-状态(g10101)");
			strDataList.append("g10201"); itemList.append("增压风机1-电流(g10201)");
			strDataList.append("g11901"); itemList.append("烟气入口1-二氧化硫(g11901)");
			strDataList.append("g12001"); itemList.append("烟气入口1-氮氧化物(g12001)");
			strDataList.append("g12101"); itemList.append("烟气入口1-氧气含量(g12101)");
			strDataList.append("g12201"); itemList.append("烟气入口1-烟气排量(g12201)");
			strDataList.append("g12301"); itemList.append("烟气入口1-烟气温度(g12301)");
			strDataList.append("g12401"); itemList.append("烟气入口1-烟尘(g12401)");
			strDataList.append("g12501"); itemList.append("烟气入口1-烟气压力(g12501)");
			strDataList.append("g12601"); itemList.append("烟气入口1-烟气湿度(g12601)");
			strDataList.append("g12701"); itemList.append("烟气出口1-二氧化硫(g12701)");
			strDataList.append("g12801"); itemList.append("烟气出口1-氮氧化物(g12801)");
			strDataList.append("g12901"); itemList.append("烟气出口1-氧气含量(g12901)");
			strDataList.append("g13001"); itemList.append("烟气出口1-烟气排量(g13001)");
			strDataList.append("g13101"); itemList.append("烟气出口1-烟气温度(g13101)");
			strDataList.append("g13201"); itemList.append("烟气出口1-烟尘(g13201)");
			strDataList.append("g13301"); itemList.append("烟气出口1-烟气压力(g13301)");
			strDataList.append("g13401"); itemList.append("烟气出口1-烟气湿度(g13401)");
            ok = true;
        } else if(st=="52") { //污水处理过程监控
            strDataList.append("e10101"); itemList.append("进水口1-流量(e10101)");
			strDataList.append("e10201"); itemList.append("进水口1-COD(e10201)");
			strDataList.append("e10301"); itemList.append("进水口1-氨氮(e10301)");
			strDataList.append("e10401"); itemList.append("进水口1-总磷(e10401)");
			strDataList.append("e10501"); itemList.append("进水口1-总氮(e10501)");
			strDataList.append("e10601"); itemList.append("进水口1-pH值(e10601)");
			strDataList.append("e20101"); itemList.append("出水口1-流量(e20101)");
			strDataList.append("e20201"); itemList.append("出水口1-COD(e20201)");
			strDataList.append("e20301"); itemList.append("出水口1-氨氮(e20301)");
			strDataList.append("e20401"); itemList.append("出水口1-总磷(e20401)");
			strDataList.append("e20501"); itemList.append("出水口1-总氮(e20501)");
			strDataList.append("e20601"); itemList.append("出水口1-pH值(e20601)");
            ok = true;
        }
    } else if(type==DEVICE_POLLUTANT && prot==0) {
		if(st=="22" || st=="31") { //大气污染源
			strDataList.append("S01"); itemList.append("氧气含量(S01)");
			strDataList.append("S02"); itemList.append("烟气流速(S02)");
			strDataList.append("S03"); itemList.append("烟气温度(S03)");
			strDataList.append("S04"); itemList.append("烟气压力(S04)");
			strDataList.append("S05"); itemList.append("烟气湿度(S05)");
			strDataList.append("S06"); itemList.append("制冷温度(S06)");
			strDataList.append("S07"); itemList.append("烟道截面积(S07)");
			strDataList.append("S08"); itemList.append("烟气动压(S08)");
			strDataList.append("B02"); itemList.append("烟气排量(B02)");
			strDataList.append("01"); itemList.append("烟尘(01)");
			strDataList.append("02"); itemList.append("二氧化硫(02)");
			strDataList.append("03"); itemList.append("氮氧化物(03)");
			strDataList.append("04"); itemList.append("一氧化碳(04)");
			strDataList.append("05"); itemList.append("硫化氢(05)");
			strDataList.append("06"); itemList.append("氰化物(06)");
			strDataList.append("07"); itemList.append("氟化物(07)");
			strDataList.append("08"); itemList.append("氯化氢(08)");
			strDataList.append("09"); itemList.append("沥青烟(09)");
			strDataList.append("10"); itemList.append("氨气(10)");
			strDataList.append("11"); itemList.append("氯气(11)");
			strDataList.append("12"); itemList.append("二氧化氮(12)");
			strDataList.append("13"); itemList.append("硫醇(13)");
			strDataList.append("14"); itemList.append("硫酸雾(14)");
			ok = true;
		} else if(st=="21" || st=="24" || st== "26" || st=="32" || st=="33" || st=="34") { //水污染源
			strDataList.append("B01"); itemList.append("污水流量(B01)");
            strDataList.append("001"); itemList.append("pH值(001)");
            strDataList.append("002"); itemList.append("色度(002)");
            strDataList.append("003"); itemList.append("悬浮物(003)");
            strDataList.append("010"); itemList.append("五日生化需氧量(010)");
            strDataList.append("011"); itemList.append("化学需氧量(011)");
            strDataList.append("015"); itemList.append("总有机碳(015)");
            strDataList.append("020"); itemList.append("总汞(020)");
            strDataList.append("021"); itemList.append("烷基汞(021)");
            strDataList.append("022"); itemList.append("总镉(022)");
            strDataList.append("023"); itemList.append("总铬(023)");
            strDataList.append("024"); itemList.append("六价铬(024)");
			strDataList.append("025"); itemList.append("三价铬(025)");
            strDataList.append("026"); itemList.append("总砷(026)");
            strDataList.append("027"); itemList.append("总铅(027)");
            strDataList.append("028"); itemList.append("总镍(028)");
            strDataList.append("029"); itemList.append("总铜(029)");
            strDataList.append("030"); itemList.append("总锌(030)");
            strDataList.append("031"); itemList.append("总锰(031)");
            strDataList.append("032"); itemList.append("总铁(032)");
            strDataList.append("033"); itemList.append("总银(033)");
            strDataList.append("034"); itemList.append("总铍(034)");
            strDataList.append("035"); itemList.append("总硒(035)");
			strDataList.append("036"); itemList.append("锡(036)");
            strDataList.append("037"); itemList.append("硼(037)");
			strDataList.append("038"); itemList.append("钼(038)");
			strDataList.append("039"); itemList.append("钡(039)");
            strDataList.append("040"); itemList.append("钴(040)");
            strDataList.append("041"); itemList.append("铊(041)");
            strDataList.append("060"); itemList.append("氨氮(060)"); 
            strDataList.append("061"); itemList.append("有机氮(061)");
			strDataList.append("065"); itemList.append("总氮(065)");
            strDataList.append("080"); itemList.append("石油类(080)");
			strDataList.append("101"); itemList.append("总磷(101)");
			ok = true;
		} else if(st=="23" || st=="36") { //噪声污染源
			strDataList.append("B03"); itemList.append("A权声级(B03)");
			strDataList.append("L5"); itemList.append("累计百分声级L5(L5)");
			strDataList.append("L10"); itemList.append("累计百分声级L10(L10)");
			strDataList.append("L50"); itemList.append("累计百分声级L50(L50)");
			strDataList.append("L90"); itemList.append("累计百分声级L90(L90)");
			strDataList.append("L95"); itemList.append("累计百分声级L95(L95)");
			strDataList.append("Leq"); itemList.append("30秒等效声级(Leq)");
			strDataList.append("Ldn"); itemList.append("昼夜等效声级(Ldn)");
			strDataList.append("Ln"); itemList.append("昼间等效声级(Ln)");
			strDataList.append("Ld"); itemList.append("夜间等效声级(Ld)");
			strDataList.append("LMn"); itemList.append("最大的瞬时声级(LMn)");
			strDataList.append("LMx"); itemList.append("最小的瞬时声级(LMx)");
			ok = true;
		}
    }
    return ok;
}

//设备信息编码
bool UserComboBox::setItemList(enum ListType type,int prot,const QString &st,const QString &device)
{
    bool ok = false;
    itemList.clear();
    strDataList.clear();
    intDataList.clear();
	if(type==DEVICE_INFORMATION && prot==1) { //设备信息编码
		if(st=="32") {
			if(device=="320001") {
				ok = true;
			} else if(device=="321011") {
				ok = true;
			}
		} else if(st=="31") {
			if(device=="310001") {
				ok = true;
			} else if(device=="311011") {
				ok = true;
			}
		}
    }
    return ok;
}
	
void UserComboBox::setAllItem(enum ListType type)
{
    if(type==PROTOCOL) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),intDataList.at(i));
        }
    } else if(type== SERVER_ST || type==CLIENT_ST) {
		for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),strDataList.at(i));
        }
	} else if(type==SERVER_CN || type==CLIENT_CN) {
		for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),intDataList.at(i));
        }
	} else if(type==SERVER_FLAG || type==CLIENT_FLAG) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),intDataList.at(i));
        }
	} else if(type==DEVICE_OVERTIME || type==DEVICE_RECOUNT) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),intDataList.at(i));
        }
	} else if(type==DEVICE_REALCYCLE || type==DEVICE_MINCYCLE) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),intDataList.at(i));
        }
    } else if(type==DEVICE_POLLUTANT) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),strDataList.at(i));
        }
    } else if(type==DEVICE_POLLUTANT_TYPE) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),intDataList.at(i));
        }
    } else if(type==DEVICE_UNIT) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),strDataList.at(i));
        }
    } else if(type==DEVICE_PRECISION) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),strDataList.at(i));
        }
	} else if(type==DEVICE_SAMPLING_CYCLE) {
        for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),intDataList.at(i));
        }
    } else if(type==DEVICE_INFORMATION) {
		for(int i=0;i<itemList.count();i++) {
            addItem(itemList.at(i),strDataList.at(i));
        }
	}
}
