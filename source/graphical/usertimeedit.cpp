#include "usertimeedit.h"

UserTimeEdit::UserTimeEdit(const QTime &time)
{
    setAlignment(Qt::AlignHCenter);
    setDisplayFormat("hh:mm:ss");
    setTime(time);
}

UserTimeEdit::~UserTimeEdit()
{

}
