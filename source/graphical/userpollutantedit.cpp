#include "userpollutantedit.h"
#include "../source/files/userdefaultparameter.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

UserPollutantEdit::UserPollutantEdit(enum PlatformType type,int version,const QString &st,QWidget *parent) : QWidget(parent)
{
    Platform = type;
    DeviceST = st;
    Version = version;

    labelCode = new UserLabel(tr("污染物编码"));
    labelCode->setFixedWidth(80);
    comboBoxCode = new UserComboBox(UserComboBox::DEVICE_POLLUTANT,Version,DeviceST);
    comboBoxCode->setCurrentIndex(0);
    comboBoxCode->setMaxVisibleItems(20);
    comboBoxCode->setFixedWidth(208);
    labelName = new UserLabel(tr("污染物名称"));
    labelCode->setFixedWidth(80);
    lineEditName = new UserLineEdit(UserLineEdit::NONE);
    QStringList pollutant = comboBoxCode->currentText().split("(");
    lineEditName->setText(pollutant.first());
    lineEditName->setEnabled(false);
    lineEditName->setFixedWidth(176);
    labelType = new UserLabel(tr("污染物类型"));
    labelType->setFixedWidth(80);
    comboBoxType = new UserComboBox(UserComboBox::DEVICE_POLLUTANT_TYPE);
    comboBoxType->setCurrentIndex(0);
    comboBoxType->setMaxVisibleItems(20);
    comboBoxType->setFixedWidth(208);
    QHBoxLayout *row0Layout = new QHBoxLayout();
    row0Layout->addWidget(labelCode);
    row0Layout->addWidget(comboBoxCode);
    row0Layout->addSpacing(30);
    row0Layout->addWidget(labelName);
    row0Layout->addWidget(lineEditName);
    row0Layout->addSpacing(30);
    row0Layout->addWidget(labelType);
    row0Layout->addWidget(comboBoxType);

    labelDensityUnit = new UserLabel(tr("浓度单位"));
    labelDensityUnit->setFixedWidth(64);
    comboBoxDensityUnit = new UserComboBox(UserComboBox::DEVICE_UNIT,version);
    comboBoxDensityUnit->setFixedWidth(168);
    comboBoxDensityUnit->setCurrentIndex(0);
    comboBoxDensityUnit->setMaxVisibleItems(20);
    labelDensityDot = new UserLabel(tr("浓度精度"));
    labelDensityDot->setFixedWidth(64);
    comboBoxDensityDot = new UserComboBox(UserComboBox::DEVICE_PRECISION,version);
    comboBoxDensityDot->setFixedWidth(144);
    comboBoxDensityDot->setCurrentIndex(3);
    comboBoxDensityDot->setMaxVisibleItems(20);
    labelQuantityUnit = new UserLabel(tr("排量单位"));
    labelQuantityUnit->setFixedWidth(64);
    comboBoxQuantityUnit = new UserComboBox(UserComboBox::DEVICE_UNIT,version);
    comboBoxQuantityUnit->setFixedWidth(168);
    comboBoxQuantityUnit->setCurrentIndex(0);
    comboBoxQuantityUnit->setMaxVisibleItems(20);
    labelQuantityDot = new UserLabel(tr("排量精度"));
    labelQuantityDot->setFixedWidth(64);
    comboBoxQuantityDot = new UserComboBox(UserComboBox::DEVICE_PRECISION,version);
    comboBoxQuantityDot->setFixedWidth(144);
    comboBoxQuantityDot->setCurrentIndex(3);
    comboBoxQuantityDot->setMaxVisibleItems(20);
    QHBoxLayout *row1Layout = new QHBoxLayout();
    row1Layout->addWidget(labelDensityUnit);
    row1Layout->addWidget(comboBoxDensityUnit);
    row1Layout->addWidget(labelDensityDot);
    row1Layout->addWidget(comboBoxDensityDot);
    row1Layout->addWidget(labelQuantityUnit);
    row1Layout->addWidget(comboBoxQuantityUnit);
    row1Layout->addWidget(labelQuantityDot);
    row1Layout->addWidget(comboBoxQuantityDot);

    buttonAddition = new UserButton(tr("添加"));
    buttonAddition->setFixedWidth(72);
    buttonModified = new UserButton(tr("修改"));
    buttonModified->setFixedWidth(72);
    buttonDelete = new UserButton(tr("删除"));
    buttonDelete->setFixedWidth(72);
    QHBoxLayout *row2Layout = new QHBoxLayout();
    row2Layout->addSpacing(668);
    row2Layout->addWidget(buttonAddition);
    row2Layout->addWidget(buttonModified);
    row2Layout->addWidget(buttonDelete);

    QStringList header;
    header << "污染物编码" << "污染物名称" << "污染物类型" << "浓度单位" << "浓度精度" << "排量单位" << "排量精度";
    tableWidget = new UserTableWidget(Qt::Horizontal,header,header.count());
    QList<int> widths;
    widths << 96 << 192 << 80 << 80 << 80 << 80 << 80;
    tableWidget->setColumnsWidth(widths);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(row0Layout);
    mainLayout->addLayout(row1Layout);
    mainLayout->addLayout(row2Layout);
    mainLayout->addWidget(tableWidget);
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);

    connect(comboBoxCode,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxCodeCurrentIndexChangedHandle()));
    connect(tableWidget,SIGNAL(rowDoubleClicked(int,QStringList)),this,SLOT(tableWidgetRowDoubleClickedHandle(int,QStringList)));
    connect(buttonAddition,SIGNAL(clicked()),this,SLOT(buttonAdditionClickedHandle()));
    connect(buttonModified,SIGNAL(clicked()),this,SLOT(buttonModifiedClickedHandle()));
    connect(buttonDelete,SIGNAL(clicked()),this,SLOT(buttonDeleteClickedHandle()));

    setDefaultPollutantList(Version,DeviceST);
    setComboBoxCurrentIndex(Version,DeviceST);
}

UserPollutantEdit::~UserPollutantEdit()
{

}
void UserPollutantEdit::setPollutantList(const QList<QStringList> &list)
{
    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    for(int i=0;i<list.count();i++) {
        tableWidget->appendData(list.at(i));
    }
}

void UserPollutantEdit::setVersion(int version)
{
    Version = version;
    comboBoxCode->setItems(UserComboBox::DEVICE_POLLUTANT,Version,DeviceST);
    comboBoxDensityUnit->setItems(UserComboBox::DEVICE_UNIT,Version);
    comboBoxDensityDot->setItems(UserComboBox::DEVICE_PRECISION,Version);
    comboBoxQuantityUnit->setItems(UserComboBox::DEVICE_UNIT,Version);
    comboBoxQuantityDot->setItems(UserComboBox::DEVICE_PRECISION,Version);
    setDefaultPollutantList(Version,DeviceST);
    setComboBoxCurrentIndex(Version,DeviceST);
}

void UserPollutantEdit::setDeviceST(const QString &st)
{
    DeviceST = st;
    comboBoxCode->setItems(UserComboBox::DEVICE_POLLUTANT,Version,DeviceST);
    setDefaultPollutantList(Version,DeviceST);
    setComboBoxCurrentIndex(Version,DeviceST);
}

void UserPollutantEdit::comboBoxCodeCurrentIndexChangedHandle()
{
    QStringList pollutant = comboBoxCode->currentText().split("(");
    lineEditName->setText(pollutant.first());
}

void UserPollutantEdit::tableWidgetRowDoubleClickedHandle(int row,const QStringList &list)
{
    if(list.count()>=7) {
        SelectRow = row;
        comboBoxCode->setCurrentIndex(comboBoxCode->findData(list.at(0)));
        comboBoxType->setCurrentIndex(comboBoxType->findData(list.at(2)));
        comboBoxDensityUnit->setCurrentIndex(comboBoxDensityUnit->findData(list.at(3)));
        comboBoxDensityDot->setCurrentIndex(comboBoxDensityDot->findData(list.at(4)));
        comboBoxQuantityUnit->setCurrentIndex(comboBoxQuantityUnit->findData(list.at(5)));
        comboBoxQuantityDot->setCurrentIndex(comboBoxQuantityDot->findData(list.at(6)));
    }
}

void UserPollutantEdit::buttonAdditionClickedHandle()
{
    QStringList list;
    QString code = comboBoxCode->currentData().toString();
    list.append(code);
    list.append(lineEditName->text());
    list.append(comboBoxType->currentData().toString());
    list.append(comboBoxDensityUnit->currentData().toString());
    list.append(comboBoxDensityDot->currentData().toString());
    list.append(comboBoxQuantityUnit->currentData().toString());
    list.append(comboBoxQuantityDot->currentData().toString());
      if(!tableWidget->findPrimaryKey(0,code)) {
        tableWidget->appendData(list);
    } else {
        QMessageBox::information(this,tr("提示"),tr("污染监测因子(%1)已存在！").arg(code));
    }
}

void UserPollutantEdit::buttonModifiedClickedHandle()
{
    QStringList list;
    list.append(comboBoxCode->currentData().toString());
    list.append(lineEditName->text());
    list.append(comboBoxType->currentData().toString());
    list.append(comboBoxDensityUnit->currentData().toString());
    list.append(comboBoxDensityDot->currentData().toString());
    list.append(comboBoxQuantityUnit->currentData().toString());
    list.append(comboBoxQuantityDot->currentData().toString());
    tableWidget->setDataRow(SelectRow,list);
}

void UserPollutantEdit::buttonDeleteClickedHandle()
{
    tableWidget->removeRowOrColumn(tableWidget->currentRowOrColumn());
}

void UserPollutantEdit::setDefaultPollutantList(int version,const QString &st)
{
    QList<QStringList> list = UserDefaultParameter::pollutantConfigList(version,st);
    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    for(int i=0;i<list.count();i++) {
        tableWidget->appendData(list.at(i));
    }
}

void UserPollutantEdit::setComboBoxCurrentIndex(int version,const QString &st)
{
    if(version==1) {
        if(st=="21" || st=="24" || st=="26") {
			comboBoxCode->setCurrentIndex(1);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(2);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="22") {
			comboBoxCode->setCurrentIndex(1);
            comboBoxDensityUnit->setCurrentIndex(19);
            comboBoxDensityDot->setCurrentIndex(1);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="23" || st=="36") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="25" || st=="35") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="27") {
            comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="31") {
            comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(13);
            comboBoxDensityDot->setCurrentIndex(2);
            comboBoxQuantityUnit->setCurrentIndex(12);
            comboBoxQuantityDot->setCurrentIndex(1);
        } else if(st=="32") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="33" || st=="34") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="37") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="38") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="39") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(13);
            comboBoxDensityDot->setCurrentIndex(2);
            comboBoxQuantityUnit->setCurrentIndex(12);
            comboBoxQuantityDot->setCurrentIndex(1);
        } else if(st=="41") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="51") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="52") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        }
    } else if(version==0) {
        if(st=="21" || st=="24" || st=="26") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="22") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="23" || st=="36") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="25" && st=="35") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="31") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="32") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="33" || st=="34") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="37") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="38") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        } else if(st=="41") {
			comboBoxCode->setCurrentIndex(0);
            comboBoxDensityUnit->setCurrentIndex(0);
            comboBoxDensityDot->setCurrentIndex(0);
            comboBoxQuantityUnit->setCurrentIndex(0);
            comboBoxQuantityDot->setCurrentIndex(0);
        }
    }
}
