#include "src/widgets/rightPanelLog.h"

RightPanelWidget::RightPanelWidget(QWidget *parent)
{

    initUI();

}

RightPanelWidget::~RightPanelWidget()
{

}

void RightPanelWidget::initUI()
{

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,10,0,10);
    mainLayout->setSpacing(10);

    /* Status */
    QHBoxLayout *statusLayout = new QHBoxLayout();
    lightLbl = new QLabel(this);
    lightLbl->setObjectName("lightLbl");
    lightLbl->setFixedSize(14,14);
    lightLbl->setStyleSheet("#lightLbl {background-color: #f44336;}");
    // lightLbl->setStyleSheet("#lightLbl {background-color: #4caf50;}");
    statusLbl = new QLabel("设备未连接",this);
    statusLbl->setStyleSheet("font-weight: bold;color: #2c3e50;font-size: 14px;");

    statusLayout->addWidget(lightLbl);
    statusLayout->addWidget(statusLbl);
    statusLayout->addStretch();

    /* Log */
    logTextEdit = new QPlainTextEdit(this);
    logTextEdit->setReadOnly(true);
    logTextEdit->setCenterOnScroll(true);

    /* Btn */
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0,10,0,10);
    btnLayout->setSpacing(10);
    clearBtn = new QPushButton("清空日志",this);
    clearBtn->setCursor(Qt::PointingHandCursor);
    saveBtn = new QPushButton("导出日志",this);
    saveBtn->setCursor(Qt::PointingHandCursor);

    btnLayout->addWidget(clearBtn);
    btnLayout->addWidget(saveBtn);

    mainLayout->addLayout(statusLayout);
    mainLayout->addWidget(logTextEdit,1);
    mainLayout->addLayout(btnLayout);

}

void RightPanelWidget::setupConnections()
{
    connect(clearBtn,&QPushButton::clicked,logTextEdit,&QPlainTextEdit::clear);

    connect(saveBtn,&QPushButton::clicked,this,[=](){
        emit exportLogRequested(logTextEdit->toPlainText());
    });
}

void RightPanelWidget::setConnectionStatus(bool isConnected)
{
    if (isConnected) {
        lightLbl->setStyleSheet("#lightLbl { background-color: #2ecc71; border-radius: 7px; }"); // 绿
        statusLbl->setText("硬件已连接");
        statusLbl->setStyleSheet("font-weight: bold; color: #2ecc71;");
    } else {
        lightLbl->setStyleSheet("#lightLbl { background-color: #e74c3c; border-radius: 7px; }"); // 红
        statusLbl->setText("设备未连接");
        statusLbl->setStyleSheet("font-weight: bold; color: #e74c3c;");
    }
}

void RightPanelWidget::appendLog(const QString &msg, const QString &level)
{
    QString color = "#d4d4d4"; // 默认灰白
    if (level == "ERROR") color = "#e74c3c";
    if (level == "TX")    color = "#2ecc71";
    if (level == "RX")    color = "#3498db";

    QString timeStr = QTime::currentTime().toString("HH:mm:ss.zzz");
    QString html = QString("<span style='color:#7f8c8d;'>[%1]</span> <span style='color:%2;'>%3</span>")
                       .arg(timeStr, color, msg);
    logTextEdit->appendHtml(html);
}

