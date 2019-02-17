#ifndef USERDEFAULTPARAMETER_H
#define USERDEFAULTPARAMETER_H

#include <QObject>

class UserDefaultParameter : public QObject
{
    Q_OBJECT
public:
    explicit UserDefaultParameter(QObject *parent = 0);
    virtual ~UserDefaultParameter();
    static QList<QStringList> pollutantConfigList(int version,const QString &st);
signals:

public slots:

private:
    static QStringList toPollutantConfig(const QString &code,const QString &name,int type,const QString &dUnit,int dDot);
    static QStringList toPollutantConfig(const QString &code,const QString &name,int type,const QString &dUnit,int dDot,const QString qUnit,int qDot);
private slots:

};

#endif // USERDEFAULTPARAMETER_H
