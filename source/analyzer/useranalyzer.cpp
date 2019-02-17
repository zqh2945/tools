#include "useranalyzer.h"

UserAnalyzer::UserAnalyzer(const QString &code,QObject *parent) : QObject(parent)
{
    Code = code;
}

UserAnalyzer::~UserAnalyzer()
{

}
