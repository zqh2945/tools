#include "userdatetimeedit.h"

UserDateTimeEdit::UserDateTimeEdit(const QDateTime &datetime)
{
    setAlignment(Qt::AlignHCenter);
    setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    setDateTime(datetime);
}

UserDateTimeEdit::~UserDateTimeEdit()
{

}
