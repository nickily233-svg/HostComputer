#ifndef DATA_STATISTICS_TABLE_H
#define DATA_STATISTICS_TABLE_H

#include <QTableWidget>
#include <QHeaderView>

class DataStatisticsTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit DataStatisticsTable(QWidget *parent = nullptr);
};

#endif // DATA_STATISTICS_TABLE_H