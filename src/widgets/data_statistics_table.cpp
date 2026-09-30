#include "data_statistics_table.h"

DataStatisticsTable::DataStatisticsTable(QWidget *parent) : QTableWidget(parent)
{
    // 1. col num and label head
    setColumnCount(5);
    setRowCount(4);
    setHorizontalHeaderLabels({"通道名称", "最大值", "最小值", "平均值", "峰峰值"});

    // 2. row num
    setRowCount(4);

    // 3. hide row num
    verticalHeader()->setVisible(false);

    // 4. stretch
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 5. only read
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 6. init table
    for(int row = 0;row < 4;++row) {
        setItem(row,0,new QTableWidgetItem(QString("通道%1").arg(row + 1)));
        item(row, 0)->setTextAlignment(Qt::AlignCenter);
        for(int col = 1;col < 5;++col) {
            QTableWidgetItem *item = new QTableWidgetItem("--");
            item->setTextAlignment(Qt::AlignCenter);
            setItem(row,col,item);
        }

        setRowHidden(row, true);
    }

    setObjectName("ChxTable");
    setStyleSheet("#ChxTable {}");

    // 7. make sure stretch
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}