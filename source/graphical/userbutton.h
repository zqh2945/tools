#ifndef USERBUTTON_H
#define USERBUTTON_H

#include <QPushButton>

class UserButton : public QPushButton
{
public:
    UserButton(const QString &name);
    ~UserButton();
};

#endif // USERBUTTON_H
