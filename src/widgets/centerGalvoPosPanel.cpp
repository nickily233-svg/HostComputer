#include "src/widgets/centerGalvoPosPanel.h"

CenterGalvoWidget::CenterGalvoWidget(QWidget *parent) : QWidget(parent)
{

    setupUI();
    setupConnections();

}


CenterGalvoWidget::~CenterGalvoWidget()
{

}

void CenterGalvoWidget::setupUI()
{

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);

    customPlot = new QCustomPlot(this);

    customPlot->xAxis->setLabel("X 轴位置(mm)");
    customPlot->yAxis->setLabel("Y 轴位置(mm)");
    customPlot->xAxis->setRange(-60,60);
    customPlot->yAxis->setRange(-60,60);
    customPlot->xAxis->ticker()->setTickCount(6);
    customPlot->yAxis->ticker()->setTickCount(6);
    customPlot->xAxis->setBasePen(QPen(Qt::NoPen));
    customPlot->yAxis->setBasePen(QPen(Qt::NoPen));

    customPlot->setInteractions(QCP::iNone);
    customPlot->setStyleSheet("border: 1px solid #dcdcdc; border-radius: 6px; padding: 5px;");
    customPlot->axisRect()->setMargins(QMargins(10,10,10,10));
    // customPlot->axisRect()->setAutoMargins(QCP::msNone);

    // 图表背景设为纯白
    customPlot->axisRect()->setBackground(QBrush(Qt::white));
    customPlot->setBackground(QBrush(Qt::white));

    // 绘制软限位边界框
    // QCPItemRect *boundaryRect = new QCPItemRect(customPlot);
    // boundaryRect->topLeft->setCoords(-60, 60);
    // boundaryRect->bottomRight->setCoords(60, -60);
    // boundaryRect->setPen(QPen(Qt::black, 1, Qt::DashLine));

    // QSharedPointer<QCPAxisTickerFixed> tickerX(new QCPAxisTickerFixed);
    // tickerX->setTickStep(20.0);
    // customPlot->xAxis->setTicker(tickerX);

    // QSharedPointer<QCPAxisTickerFixed> tickerY(new QCPAxisTickerFixed);
    // tickerY->setTickStep(20.0);
    // customPlot->yAxis->setTicker(tickerY);

    // 绘制十字准星中心线
    QCPItemStraightLine *vLine = new QCPItemStraightLine(customPlot);
    vLine->point1->setCoords(0, -60);
    vLine->point2->setCoords(0, 60);
    vLine->setPen(QPen(Qt::black, 1, Qt::DotLine));

    QCPItemStraightLine *hLine = new QCPItemStraightLine(customPlot);
    hLine->point1->setCoords(-60, 0);
    hLine->point2->setCoords(60, 0);
    hLine->setPen(QPen(Qt::black, 1, Qt::DotLine));

    // 绘制当前位置的红点
    positionGraph = customPlot->addGraph();
    positionGraph->setLineStyle(QCPGraph::lsNone);
    positionGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::red, Qt::red, 10));

    mainLayout->addWidget(customPlot);

}

void CenterGalvoWidget::setupConnections()
{

}

void CenterGalvoWidget::updatePosition(double x, double y)
{
    positionGraph->setData({x}, {y});
    customPlot->replot();
}
