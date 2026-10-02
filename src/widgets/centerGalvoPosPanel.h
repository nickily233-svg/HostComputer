#ifndef CENTERGALVOWIDGET_H
#define CENTERGALVOWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "qcustomplot.h"

class CenterGalvoWidget : public QWidget
{
    Q_OBJECT

public :
    explicit CenterGalvoWidget(QWidget *parent = nullptr);
    ~CenterGalvoWidget();

public slots:
    void updatePosition(double x,double y);

private :
    QCustomPlot *customPlot;
    QCPGraph *positionGraph;

    void setupUI();
    void setupConnections();

signals :

};

#endif CENTERGALVOWIDGET_H