#ifndef USERTABLEFIELD_H
#define USERTABLEFIELD_H

#include <QString>
#include <QList>

typedef struct {
    QString Name;  //字段名称
    QString Type; //数据类型
    int Size; //数据大小，用于设置字符串的最大长度
    bool NotNull; //非空，表示该字段不能为空
    bool PrimaryKey; //主键，用于说明该字段是否为主键
  }FieldType;

class UserTableField
{
public:
    UserTableField();
    ~UserTableField();
    void append(const QString &name,const QString &type,int size,bool notnull=false,bool key=false);
    void append(const QString &name,const QString &type,bool notnull=false,bool key=false);
    void clear() {FieldList.clear();}
    QString command();
private:
    QList<FieldType> FieldList;
    QStringList keyFieldNameList();
    QString keyCommand();
    QString fieldCommand(FieldType field);
};

#endif // USERTABLEFIELD_H
