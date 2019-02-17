#ifndef USERTIMEEDIT_H
#define USERTIMEEDIT_H

#include <QTimeEdit>

class UserTimeEdit : public QTimeEdit
{
    Q_OBJECT
public:
    UserTimeEdit(const QTime &time = QTime::currentTime());
    ~UserTimeEdit();
};

#endif // USERTIMEEDIT_H
