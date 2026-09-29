#ifndef COMMON_WIDGET_H
#define COMMON_WIDGET_H

#include <QWidget>

class CommonWidgets : public QWidget
{
    Q_OBJECT

public :
    explicit CommonWidgets(QWidget *parent = nullptr);
    ~CommonWidgets();

protected :


private :
    void initUI();

};

#endif // COMMON_WIDGET_H