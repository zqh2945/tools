#include "userlineedit.h"
#include <QFont>

UserLineEdit::UserLineEdit(enum TextType type,int version)
{
    Version = version;
    LineType = type;

    setAlignment(Qt::AlignHCenter);
    if(LineType==MN && Version==0) {
        setMaxLength(14);
        setText("0152316J000000");
    } else if(LineType==MN && Version==1) {
        setMaxLength(24);
        setText("00000000000152316J000000");
    } else if(LineType==PW) {
        setMaxLength(6);
        setText("100000");
    } else if(LineType==IP) {
        setMaxLength(21);
        setText("0.0.0.0:0");
    }

    connect(this,SIGNAL(textChanged(const QString)),this,SLOT(textChangedHandle(const QString)));
}

UserLineEdit::~UserLineEdit()
{
}

void UserLineEdit::textChangedHandle(const QString &text)
{
    QPalette palette;
    if(LineType==MN && Version==0) {
        if(text.length()<7) {
            palette.setColor(QPalette::Text,Qt::red);
        } else if(text.length()>=7 && text.length() < maxLength()) {
            palette.setColor(QPalette::Text,Qt::darkCyan);
        } else {
            palette.setColor(QPalette::Text,Qt::black);
        }
    } else if(LineType==MN && Version==1) {
        if(text.length()<10) {
            palette.setColor(QPalette::Text,Qt::red);
        } else if(text.length() >=10 && text.length()<17) {
        palette.setColor(QPalette::Text,Qt::darkGreen);
        } else if(text.length()>=17 && text.length()<maxLength()) {
            palette.setColor(QPalette::Text,Qt::blue);
        } else {
            palette.setColor(QPalette::Text,Qt::black);
        }
    } else if(LineType==PW) {
        if(text.length()<maxLength()) {
            palette.setColor(QPalette::Text,Qt::red);
        } else {
            palette.setColor(QPalette::Text,Qt::black);
        }
    }
    setPalette(palette);
}

void UserLineEdit::setVersion(int version)
{
    Version = version;
    if(LineType==MN && Version==0) {
        setMaxLength(14);
        setText("0152316J000000");
    } else if(LineType==MN && Version==1) {
        setMaxLength(24);
        setText("00000000000152316J000000");
    } else if(LineType==PW) {
        setMaxLength(6);
        setText("100000");
    }
}

void UserLineEdit::setAddress(const QString &ipaddr,int port)
{
    setText(QString("%1:%2").arg(ipaddr).arg(port));
}


