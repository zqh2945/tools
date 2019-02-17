#ifndef USERLABEL_H
#define USERLABEL_H

#include <QLabel>

class UserLabel : public QLabel
{
public:
    UserLabel(const QString &text);
    ~UserLabel();
};

#endif // USERLABEL_H
