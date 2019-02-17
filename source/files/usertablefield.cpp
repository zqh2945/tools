#include "usertablefield.h"

UserTableField::UserTableField()
{

}

UserTableField::~UserTableField()
{

}

void UserTableField::append(const QString &name,const QString &type,int size,bool notnull,bool key)
{
    FieldType field;
    field.Name = name;
    field.Type = type;
    field.Size = size;
    field.NotNull = notnull;
    field.PrimaryKey = key;
      FieldList.append(field);
}

void UserTableField::append(const QString &name,const QString &type,bool notnull,bool key)
{
    FieldType field;
    field.Name = name;
    field.Type = type;
    field.Size = -1;
    field.NotNull = notnull;
    field.PrimaryKey = key;
      FieldList.append(field);
}

QStringList UserTableField::keyFieldNameList()
{
    QStringList list;
    for(int i=0;i<FieldList.count();i++) {
        if(FieldList.at(i).PrimaryKey) {
            list.append(FieldList.at(i).Name);
        }
    }
    return list;
}


QString UserTableField::keyCommand()
{
    QString key = keyFieldNameList().join(',');
    if(!key.isEmpty()) {
        return QString("primary key (%1)").arg(key);
    } else {
        return NULL;
    }
}

QString UserTableField::fieldCommand(FieldType field)
{
    QString command = QString("%1").arg(field.Name);
    if(field.Type=="char" || field.Type=="varchar") {
        command.append(QString(" %1(%2)").arg(field.Type).arg(field.Size));
    } else {
        command.append(QString(" %1").arg(field.Type));
    }
    if(field.NotNull==true) {
        command.append(" not null");
    }
    return command;
}

QString UserTableField::command()
{
    QStringList fieldCommandList;
    for(int i=0;i<FieldList.count();i++) {
        fieldCommandList.append(fieldCommand(FieldList.at(i)));
    }
    QString primaryKeyCommand = keyCommand();
    if(primaryKeyCommand.isNull()) {
        return fieldCommandList.join(',');
    } else {
        return fieldCommandList.join(',')+","+primaryKeyCommand;
    }
}

