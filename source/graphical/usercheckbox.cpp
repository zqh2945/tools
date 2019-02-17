#include "usercheckbox.h"

UserCheckBox::UserCheckBox(const QString &title,bool state)
{
    setText(title);
    setChecked(state);
}

UserCheckBox::~UserCheckBox()
{

}

int UserCheckBox::check()
{
    if(checkState()) {
        return 1;
    } else {
        return 0;
    }
}

void UserCheckBox::setCheck(int check)
{
    if(check==1) {
        setChecked(true);
    } else {
        setChecked(false);
    }
}
