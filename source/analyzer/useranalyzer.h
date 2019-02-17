#ifndef USERANALYZER_H
#define USERANALYZER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTime>

class UserAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit UserAnalyzer(const QString &code,QObject *parent=0);
    ~UserAnalyzer();
private:
    QString Code; //污染物分析仪编码
    QTime ZeroTime; //采样起点时间
    int Cycle; //采样周期

    QStringList InfoCodeList; //污染物分析仪信息编码列表


};

#endif // USERANALYZER_H
