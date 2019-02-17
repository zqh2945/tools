#ifndef USERFRAMEEDIT_H
#define USERFRAMEEDIT_H

#include <QWidget>
#include <QTextEdit>
#include "userbutton.h"

class UserFrameEdit : public QWidget
{
    Q_OBJECT
public:
    explicit UserFrameEdit(QWidget *parent = 0);
    ~UserFrameEdit();
    QString frame() {return textEditFrame->toPlainText().replace("\n","\r\n");}
    void setFrame(const QString &frame) {textEditFrame->setText(frame);}
signals:
    void buttonClicked(int num);
private:
    QTextEdit *textEditFrame; //帧
    UserButton *buttonPack; //组帧
    UserButton *buttonSend; //发送
private slots:
    void buttonPackClickedHandle();
    void buttonSendClickedHandle();

};

#endif // USERFRAMEEDIT_H
