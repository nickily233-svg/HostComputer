#include "src/pages/galvo_page.h"

GalvoWidget::GalvoWidget(QWidget *parent)
    // :QWidget(parent)
{
    initUI();
    setupConnections();
}

GalvoWidget::~GalvoWidget()
{

}

void GalvoWidget::initUI()
{

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(10,10,10,10);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(createLeftPanel());
    mainLayout->addWidget(createCenterPanel(),2);
    mainLayout->addWidget(createRightPanel(),1);

}

QWidget* GalvoWidget::createLeftPanel()
{
    QWidget *leftPanel = new QWidget(this);
    QVBoxLayout *leftPanelLayout = new QVBoxLayout();

    xycontrolwidget = new XYControlWidget(leftPanel);
    leftPanelLayout->addWidget(xycontrolwidget);
    leftPanel->setLayout(leftPanelLayout);

    return leftPanel;
}

QWidget* GalvoWidget::createRightPanel()
{
    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightPanelLayout = new QVBoxLayout();

    rightpanelwidget = new RightPanelWidget(rightPanel);
    rightPanelLayout->addWidget(rightpanelwidget);
    rightPanel->setLayout(rightPanelLayout);

    return rightPanel;
}

QWidget* GalvoWidget::createCenterPanel()
{
    QWidget *centerPanel = new QWidget(this);
    QVBoxLayout *centerPanelLayout = new QVBoxLayout();

    centergalvowidget = new CenterGalvoWidget(centerPanel);
    centerPanelLayout->addWidget(centergalvowidget);
    centerPanel->setLayout(centerPanelLayout);

    return centerPanel;
}

void GalvoWidget::setupConnections()
{



}
