#include "useripv4edit.h"

UserIPv4Edit::UserIPv4Edit(const QString &ipaddr)
{
    setAlignment(Qt::AlignHCenter);
    setMaxLength(15);
    setText(ipaddr);
}

UserIPv4Edit::~UserIPv4Edit()
{

}
