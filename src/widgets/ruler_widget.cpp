#include "ruler_widget.h"

RulerWidget::RulerWidget(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("rulerwidget");
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("#rulerwidget {background-color: 1e1e1e;border: 1px;border-radius: 6px;}");

    QVBoxLayout *RulerMainLayout = new QVBoxLayout(this);
    RulerMainLayout->setContentsMargins(5,5,5,5);
    RulerMainLayout->setAlignment(Qt::AlignCenter);
    RulerMainLayout->setSpacing(5);

    /*-----title-----*/
    QWidget *RulerTitleWidget = new QWidget(this);
    QHBoxLayout *RulerTitleLayout = new QHBoxLayout(RulerTitleWidget);
    RulerTitleLayout->setContentsMargins(0,0,0,0);
    RulerTitleLayout->setAlignment(Qt::AlignCenter);
    RulerTitleLayout->setSpacing(5);

    QLabel *TitleLabel = new QLabel("测量标尺",RulerTitleWidget);
    TitleLabel->setObjectName("titlelabel");
    TitleLabel->setStyleSheet("#titlelabel {color: #000000;font-weight: bold;font-size: 13px;}");

    QPushButton *addRulerBtn = new QPushButton("+",RulerTitleWidget);
    addRulerBtn->setObjectName("addrulerbtn");
    addRulerBtn->setFixedSize(20,20);
    addRulerBtn->setCursor(Qt::PointingHandCursor);
    addRulerBtn->setStyleSheet("#addrulerbtn {background-color: #1e8e3e;color: white;border-radius: 10px;font-weight: bold;font-size: 14px;border: none;}"
                               "#addrulerbtn:hover {background-color: #249e46;}"
                               "#addrulerbtn:press {background-color: #15652b;}");

    RulerTitleLayout->addWidget(TitleLabel);
    RulerTitleLayout->addStretch();
    RulerTitleLayout->addWidget(addRulerBtn);

    /*-----tree list-----*/
    RulerTree = new QTreeWidget(this);
    RulerTree->setObjectName("rulertreewidget");
    RulerTree->setHeaderHidden(true);
    RulerTree->setColumnCount(3);
    RulerTree->setIndentation(15);
    RulerTree->setStyleSheet("#rulertreewidget {background: transparent;color: #cccccc;border: none;font-size: 12px;}"
                             "#rulertreewidget:item {height: 28px;}"
                             "QTreeWidget:item:hover {background-color: #3c3c3c;}");
    RulerTree->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    /*------assembly----*/
    RulerMainLayout->addWidget(RulerTitleWidget);
    RulerMainLayout->addWidget(RulerTree);

    /*-----linked logic (add/delete ruler groups)-----*/
    connect(addRulerBtn,&QPushButton::clicked,this,[=]() mutable{
        if(groupCount >= 26)
            return;
        QString groupName = QString(QChar('A' + groupCount));
        groupCount++;

        /*-----create root node-----*/
        QTreeWidgetItem *groupItem = new QTreeWidgetItem(RulerTree);
        groupItem->setExpanded(true);
    });
}