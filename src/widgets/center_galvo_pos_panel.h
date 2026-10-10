#ifndef CENTER_GALVO_POS_PANEL_H
#define CENTER_GALVO_POS_PANEL_H

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

#endif CENTER_GALVO_POS_PANEL_H