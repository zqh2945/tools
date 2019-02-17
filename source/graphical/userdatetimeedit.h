#ifndef USERDATETIMEEDIT_H
#define USERDATETIMEEDIT_H

#include <QDateTimeEdit>

class UserDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    UserDateTimeEdit(const QDateTime &datetime = QDateTime::currentDateTime());
    ~UserDateTimeEdit();
};

#endif // USERDATETIMEEDIT_H
