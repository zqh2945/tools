#include "userdeviceedit.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

UserDeviceEdit::UserDeviceEdit(QWidget *parent) : QWidget(parent)
{
    labelVersion = new UserLabel(tr("标准版本"));
    labelVersion->setFixedWidth(64);
    comboBoxVersion = new UserComboBox(UserComboBox::PROTOCOL);
    comboBoxVersion->setCurrentIndex(1);
    comboBoxVersion->setFixedWidth(140);
    int version = comboBoxVersion->currentData().toInt();

    labelMN = new UserLabel(tr("设备编码"));
    labelMN->setFixedWidth(64);
    lineEditMN = new UserLineEdit(UserLineEdit::MN,version);
    lineEditMN->setFixedWidth(224);

    labelPW = new UserLabel(tr("设备密码"));
    labelPW->setFixedWidth(64);
    lineEditPW = new UserLineEdit(UserLineEdit::PW,version);
    lineEditPW->setFixedWidth(64);

    QHBoxLayout *row0Layout = new QHBoxLayout();
    row0Layout->addWidget(labelVersion);
    row0Layout->addWidget(comboBoxVersion);
    row0Layout->addWidget(labelMN);
    row0Layout->addWidget(lineEditMN);
    row0Layout->addWidget(labelPW);
    row0Layout->addWidget(lineEditPW);

    labelST = new UserLabel(tr("系统编号"));
    labelST->setFixedWidth(64);
    comboBoxST = new UserComboBox(UserComboBox::SERVER_ST,version);
    comboBoxST->setCurrentIndex(comboBoxST->findData("32"));
    comboBoxST->setMaxVisibleItems(20);
    comboBoxST->setFixedWidth(208);
    buttonAddition = new UserButton(tr("添加"));
    buttonAddition->setFixedWidth(72);
    buttonModified = new UserButton(tr("修改"));
    buttonModified->setFixedWidth(72);
    buttonDelete = new UserButton(tr("删除"));
    buttonDelete->setFixedWidth(72);
    QHBoxLayout *row1Layout = new QHBoxLayout();
    row1Layout->addWidget(labelST);
    row1Layout->addWidget(comboBoxST);
    row1Layout->addSpacing(140);
    row1Layout->addWidget(buttonAddition);
    row1Layout->addWidget(buttonModified);
    row1Layout->addWidget(buttonDelete);

    QStringList header;
    header << "标准版本" << "设备编号(MN)" << "设备密码(PW)" << "系统类型(ST)";
    tableWidget = new UserTableWidget(Qt::Horizontal,header,header.count());
    QList<int> widths;
    widths << 100 << 280 << 120 << 120;
    tableWidget->setColumnsWidth(widths);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(row0Layout);
    mainLayout->addLayout(row1Layout);
    mainLayout->addWidget(tableWidget);
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);

    connect(comboBoxVersion,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxVersionCurrentIndexChangedHandle()));
    connect(tableWidget,SIGNAL(rowDoubleClicked(int,QStringList)),this,SLOT(tableWidgetRowDoubleClickedHandle(int,QStringList)));
    connect(buttonAddition,SIGNAL(clicked()),this,SLOT(buttonAdditionClickedHandle()));
    connect(buttonModified,SIGNAL(clicked()),this,SLOT(buttonModifiedClickedHandle()));
    connect(buttonDelete,SIGNAL(clicked()),this,SLOT(buttonDeleteClickedHandle()));
}

UserDeviceEdit::~UserDeviceEdit()
{

}

void UserDeviceEdit::setDeviceList(const QList<QStringList> &list)
{
    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    for(int i=0;i<list.count();i++) {
        tableWidget->appendData(list.at(i));
    }
}

void UserDeviceEdit::comboBoxVersionCurrentIndexChangedHandle()
{
    int version = comboBoxVersion->currentData().toInt();
    lineEditMN->setVersion(version);
    lineEditPW->setVersion(version);
    comboBoxST->setItems(UserComboBox::SERVER_ST,version);
    comboBoxST->setCurrentIndex(comboBoxST->findData("32"));
}

void UserDeviceEdit::tableWidgetRowDoubleClickedHandle(int row,const QStringList &list)
{
    SelectRow = row;
    comboBoxVersion->setCurrentIndex(comboBoxVersion->findData(list.at(0)));
    lineEditMN->setText(list.at(1));
    lineEditPW->setText(list.at(2));
    comboBoxST->setCurrentIndex(comboBoxST->findData(list.at(3)));
}

void UserDeviceEdit::buttonAdditionClickedHandle()
{
    QStringList list;
    list.append(comboBoxVersion->currentData().toString());
    list.append(lineEditMN->text());
    list.append(lineEditPW->text());
    list.append(comboBoxST->currentData().toString());
    if(!tableWidget->findPrimaryKey(1,lineEditMN->text())) {
        tableWidget->appendData(list);
    } else {
        QMessageBox::information(this,tr("提示"),tr("设备(%1)已存在！").arg(lineEditMN->text()));
    }
}

void UserDeviceEdit::buttonModifiedClickedHandle()
{
    QStringList list;
    list.append(comboBoxVersion->currentData().toString());
    list.append(lineEditMN->text());
    list.append(lineEditPW->text());
    list.append(comboBoxST->currentData().toString());
    tableWidget->setDataRow(SelectRow,list);
}

void UserDeviceEdit::buttonDeleteClickedHandle()
{
    tableWidget->removeRowOrColumn(tableWidget->currentRowOrColumn());
}

