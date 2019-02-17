#include "userframeedit.h"
#include <QGridLayout>

UserFrameEdit::UserFrameEdit(QWidget *parent) : QWidget(parent)
{
    textEditFrame = new QTextEdit();
    textEditFrame->setFixedWidth(712);
    textEditFrame->setFixedHeight(96);
    textEditFrame->setReadOnly(true);
    textEditFrame->setTextColor(QColor(Qt::blue));
    buttonPack = new UserButton(tr("组帧"));
    buttonPack->setFixedWidth(72);
    buttonSend = new UserButton(tr("发送"));
    buttonSend->setFixedWidth(72);
    buttonSend->setEnabled(false);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(textEditFrame,0,0,3,1);
    mainLayout->addWidget(buttonPack,0,1,1,1);
    mainLayout->addWidget(buttonSend,2,1,1,1);
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);
    
    connect(buttonPack,SIGNAL(clicked()),this,SLOT(buttonPackClickedHandle()));
    connect(buttonSend,SIGNAL(clicked()),this,SLOT(buttonSendClickedHandle()));
}

UserFrameEdit::~UserFrameEdit()
{

}

void UserFrameEdit::buttonPackClickedHandle()
{
    buttonSend->setEnabled(true);
    emit buttonClicked(0);
}

void UserFrameEdit::buttonSendClickedHandle()
{
    emit buttonClicked(1);
}

