#ifndef USERPORTEDIT_H
#define USERPORTEDIT_H

#include <QLineEdit>

class UserPortEdit : public QLineEdit
{
    Q_OBJECT
public:
    UserPortEdit(int port);
    ~UserPortEdit();
    int port() {return text().toInt();}
    void setPort(int port) {setText(QString("%1").arg(port));}
};

#endif // USERPORTEDIT_H
