#include "userportedit.h"

UserPortEdit::UserPortEdit(int port)
{
    setMaxLength(5);
    setAlignment(Qt::AlignHCenter);
    setText(QString::number(port));
}

UserPortEdit::~UserPortEdit()
{

}
