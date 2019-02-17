#ifndef USERCOMBOBOX_H
#define USERCOMBOBOX_H

#include <QComboBox>
#include <QString>

class UserComboBox : public QComboBox
{
    Q_OBJECT
public:
    enum ListType {
		PROTOCOL = 0,
		SERVER_ST = 1,CLIENT_ST = 2,
		SERVER_CN = 3,CLIENT_CN = 4,
		SERVER_FLAG = 5,CLIENT_FLAG = 6,
		DEVICE_OVERTIME = 7,DEVICE_RECOUNT = 8,
		DEVICE_REALCYCLE = 9,DEVICE_MINCYCLE = 10,
        DEVICE_POLLUTANT = 11,
        DEVICE_POLLUTANT_TYPE = 12,
        DEVICE_UNIT = 13,
        DEVICE_PRECISION = 14,
        DEVICE_SAMPLING_CYCLE = 15,
        DEVICE_INFORMATION = 16
	};
    UserComboBox(enum ListType type);
    UserComboBox(enum ListType type,int version);
    UserComboBox(enum ListType type,int version,const QString &st);
    UserComboBox(enum ListType type,int version,const QString &st,const QString &device);
    ~UserComboBox();
    void setItems(enum ListType type,int version);
    void setItems(enum ListType type,int version,const QString &st);
    void setItems(enum ListType type,int version,const QString &st,const QString &argType);
private:
    QStringList itemList;
    QStringList strDataList;
    QList<int> intDataList;
    bool setItemList(enum ListType type);
    bool setItemList(enum ListType type,int version);
    bool setItemList(enum ListType type,int version,const QString &st);
    bool setItemList(enum ListType type,int version,const QString &st,const QString &argType);
    void setAllItem(enum ListType type);
};

#endif // USERCOMBOBOX_H
