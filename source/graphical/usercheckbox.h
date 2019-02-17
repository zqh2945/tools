#ifndef USERCHECKBOX_H
#define USERCHECKBOX_H

#include <QCheckBox>

class UserCheckBox : public QCheckBox
{
public:
    UserCheckBox(const QString &title,bool state);
    ~UserCheckBox();
    int check();
    void setCheck(int check);
};

#endif // USERCHECKBOX_H
