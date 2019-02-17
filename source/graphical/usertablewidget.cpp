#include "usertablewidget.h"
#include <QAbstractItemView>
#include <QHeaderView>
#include <QDebug>

UserTableWidget::UserTableWidget(Qt::Orientation orientation,const QStringList &sizes,int num) : QTableWidget ()
{
    Orientation = orientation;
    FieldCount = num;

    setFixedHeight(200);
    if(Orientation==Qt::Horizontal) {
        setColumnCount(num);
        setRowCount(0);
        setHorizontalHeaderLabels(sizes);
        setSelectionBehavior(QAbstractItemView::SelectRows);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        setShowGrid(false);
        horizontalHeader()->setSectionsClickable(false);
        horizontalHeader()->setStretchLastSection(true);
        QFont font = horizontalHeader()->font();
        font.setBold(true);
        horizontalHeader()->setFont(font);
        verticalHeader()->setVisible(false);
    } else {
        setColumnCount(0);
        setRowCount(num);
        setVerticalHeaderLabels(sizes);
        setSelectionBehavior(QAbstractItemView::SelectItems);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setShowGrid(false);
        verticalHeader()->setSectionsClickable(false);
        verticalHeader()->setStretchLastSection(true);
        QFont font = verticalHeader()->font();
        font.setBold(true);
        verticalHeader()->setFont(font);
        horizontalHeader()->setVisible(false);
    }

    connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(itemDoubleClickedHandle()));
}

UserTableWidget::~UserTableWidget()
{

}

void UserTableWidget::setColumnsWidth(QList<int> widths)
{
    int count = FieldCount;
    if(count > widths.count()) {
        count = widths.count();
    }

    if(Orientation==Qt::Horizontal) {
        for(int i=0;i<count;i++) {
            setColumnWidth(i,widths.at(i));
        }
    }
}

void UserTableWidget::setRowsHeight(QList<int> heights)
{
    int count = FieldCount;
    if(count > heights.count()) {
        count = heights.count();
    }

    if(Orientation==Qt::Vertical) {
        for(int i=0;i<count;i++) {
            setRowHeight(i,heights.at(i));
        }
    }
}

int UserTableWidget::currentRowOrColumn()
{
    if(Orientation==Qt::Horizontal) {
        return currentRow();
    } else {
        return currentColumn();
    }
}

void UserTableWidget::appendRowOrColumn()
{
    if(Orientation==Qt::Horizontal) {
        setRowCount(rowCount()+1);
    } else {
        setColumnCount(columnCount()+1);
    }
}

void UserTableWidget::removeRowOrColumn(int index)
{
    if(Orientation==Qt::Horizontal) {
        removeRow(index);
    } else {
        removeColumn(index);
    }
}

bool UserTableWidget::findPrimaryKey(int key,const QString &data)
{
    bool ok = false;
    if(Orientation==Qt::Horizontal) {
        for(int i=0;i<rowCount();i++) {
            if(item(i,key)->text()==data) {
                ok = true; break;
            }
        }
    } else {
        for( int i=0;i<columnCount();i++) {
            if(item(key,i)->text()==data) {
                ok = true; break;
            }
        }
    }
    return ok;
}

void UserTableWidget::appendData(const QStringList &data)
{
    int field = FieldCount;
    if(field > data.count()) {
        field = data.count();
    }

    int count;
    if(Orientation==Qt::Horizontal) {
        count = rowCount() + 1;
        setRowCount(count);
        for(int i=0;i<field;i++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignHCenter);
            item->setText(data.at(i));
            setItem(count-1,i,item);
        }
    } else {
        count = columnCount() + 1;
        setColumnCount(count);
        for(int i=0;i<field;i++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignHCenter);
            item->setText(data.at(i));
            setItem(i,count-1,item);
        }
    }
 }

QStringList UserTableWidget::dataRow(int row)
{
    QStringList data;
    for(int i=0;i<columnCount();i++) {
        data.append(item(row,i)->text());
    }
    return data;
}

void UserTableWidget::setDataRow(int row,const QStringList &data)
{
    int column = columnCount();
    if(data.count()>column) {
        column = data.count();
    }

    for(int i=0;i<column;i++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter);
        item->setText(data.at(i));
        setItem(row,i,item);
    }
}

QStringList UserTableWidget::dataColumn(int column)
{
    QStringList data;
    for(int i=0;i<rowCount();i++) {
        data.append(item(i,column)->text());
    }
    return data;
}

void UserTableWidget::setDataColumn(int column,const QStringList &data)
{
    int row = rowCount();
    if(data.count()<row) {
        row = data.count();
    }

    for(int i=0;i<row;i++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter);
        item->setText(data.at(i));
        setItem(i,column,item);
    }
}

QList<QStringList> UserTableWidget::datas()
{
    QList<QStringList> list;
    QStringList data;
    if(Orientation==Qt::Horizontal) {
        for(int i=0;i<rowCount();i++) {
            data.clear();
            for(int j=0;j<columnCount();j++) {
                data.append(item(i,j)->text());
            }
            list.append(data);
        }
    } else {
        for(int i=1;i<columnCount();i++) {
            data.clear();
            for(int j=0;j<rowCount();j++) {
                data.append(item(j,i)->text());
            }
            list.append(data);
        }
    }
    return list;
}

void UserTableWidget::itemDoubleClickedHandle()
{
    if(Orientation==Qt::Horizontal) {
        emit rowDoubleClicked(currentRow(),dataRow(currentRow()));
    } else {
        emit columnDoubleClicked(currentColumn(),dataColumn(currentColumn()));
    }
}
