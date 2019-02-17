#ifndef USERTABLEWIDGET_H
#define USERTABLEWIDGET_H

#include <QTableWidget>
#include <QTableWidgetItem>

class UserTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    UserTableWidget(Qt::Orientation orientation,const QStringList &sizes,int num);
    ~UserTableWidget();
    void setColumnsWidth(QList<int> widths);
    void setRowsHeight(QList<int> heights);
    int currentRowOrColumn();
    void appendRowOrColumn();
    void removeRowOrColumn(int index);
    bool findPrimaryKey(int key,const QString &data);
    void appendData(const QStringList &data);
    QStringList dataRow(int row);
    void setDataRow(int row,const QStringList &data);
    QStringList dataColumn(int column);
    void setDataColumn(int column,const QStringList &data);
    QList <QStringList> datas();
signals:
    void rowDoubleClicked(int row,const QStringList &data);
    void columnDoubleClicked(int column,const QStringList &data);
private:
    Qt::Orientation Orientation;
    int FieldCount;
private slots:
    void itemDoubleClickedHandle();
};

#endif // USERTABLEWIDGET_H
