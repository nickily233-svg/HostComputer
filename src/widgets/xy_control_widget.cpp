#include "src/widgets/xy_control_widget.h"

XYControlWidget::XYControlWidget(QWidget *parent) : QWidget(parent)
{

    setupUI();
    setupStyles();
    setupConnections();
    onParamChanged();

}

XYControlWidget::~XYControlWidget()
{

}

void XYControlWidget::setupUI()
{

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20,20,20,20);
    mainLayout->setSpacing(15);

    /*-----1.参数设置-----*/
    QGroupBox *paramGroup = new QGroupBox("参数设置", this);
    QFormLayout *paramLayout = new QFormLayout(paramGroup);
    paramLayout->setContentsMargins(15, 20, 15, 15);
    paramLayout->setSpacing(12);

    // 步长
    comboboxStep = new QComboBox(this);
    comboboxStep->addItems({"0.01mm", "0.1mm", "1.0mm", "10.0mm"});
    comboboxStep->setCurrentIndex(1);
    comboboxStep->setFixedWidth(100);
    paramLayout->addRow("移动步长:", comboboxStep);

    // 速度
    speedSpin = new QDoubleSpinBox(this);
    speedSpin->setRange(1, 10000);
    speedSpin->setValue(1000);
    speedSpin->setSuffix(" mm/s");
    speedSpin->setFixedWidth(100);
    paramLayout->addRow("扫描速度:", speedSpin);

    // 激光功率
    powerSlider = new QSlider(Qt::Horizontal, this);
    powerSlider->setRange(0, 100);
    powerSlider->setValue(50);
    powerValueLabel = new QLabel("50 %", this);
    powerValueLabel->setFixedWidth(40);
    powerValueLabel->setStyleSheet("color: #4a90e2; font-weight: bold;");

    QHBoxLayout *powerLayout = new QHBoxLayout();
    powerLayout->addWidget(powerSlider);
    powerLayout->addWidget(powerValueLabel);
    paramLayout->addRow("激光功率:", powerLayout);

    // 频率
    freqSpin = new QSpinBox(this);
    freqSpin->setRange(1, 1000);
    freqSpin->setValue(20);
    freqSpin->setSuffix(" KHz");
    freqSpin->setFixedWidth(100);
    paramLayout->addRow("激光频率:", freqSpin);

    mainLayout->addWidget(paramGroup,1);

    /*-----2.十字移动-----*/
    QGroupBox *moveGroup = new QGroupBox("方向控制", this);
    QGridLayout *moveGridLayout = new QGridLayout(moveGroup);
    moveGridLayout->setContentsMargins(20,20,20,20);
    moveGridLayout->setSpacing(15);
    moveGridLayout->setAlignment(Qt::AlignCenter);

    upBtn    = new QPushButton("↑", this); // 上
    downBtn  = new QPushButton("↓", this); // 下
    leftBtn  = new QPushButton("←", this); // 左
    rightBtn = new QPushButton("→", this); // 右
    homeBtn  = new QPushButton("⌂", this); // 回零
    homeBtn->setStyleSheet("homeBtn");

    QList<QPushButton *> btns ={leftBtn,rightBtn,upBtn,downBtn,homeBtn};
    for(QPushButton *btn : btns)
    {
        btn->setFixedSize(55,55);
        btn->setCursor(Qt::PointingHandCursor);
    }

    moveGridLayout->addWidget(upBtn,0,1);
    moveGridLayout->addWidget(leftBtn,1,0);
    moveGridLayout->addWidget(homeBtn,1,1);
    moveGridLayout->addWidget(rightBtn,1,2);
    moveGridLayout->addWidget(downBtn,2,1);

    mainLayout->addWidget(moveGroup,2);
    mainLayout->addStretch();

    /*-----3.状态反馈-----*/
    QGroupBox *statusGroup = new QGroupBox("实时状态 (反馈)", this);
    QFormLayout *statusLayout = new QFormLayout(statusGroup);
    statusLayout->setContentsMargins(15, 20, 15, 15);
    statusLayout->setSpacing(12);

    xPosLabel = new QLabel("0.00 mm", this);
    yPosLabel = new QLabel("0.00 mm", this);
    angleLabel = new QLabel("0.00 °", this);

    statusLayout->addRow("X轴位置:", xPosLabel);
    statusLayout->addRow("Y轴位置:", yPosLabel);
    statusLayout->addRow("振镜角度:", angleLabel);

    mainLayout->addWidget(statusGroup,1);

    /*-----4.紧急停止-----*/
    stopBtn = new QPushButton("紧急停止 (STOP)", this);
    stopBtn->setObjectName("stopBtn");
    stopBtn->setFixedHeight(55);
    stopBtn->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(stopBtn);

}

void XYControlWidget::setupStyles()
{

    // this->setStyleSheet(R"(
    //     QGroupBox { border: 1px solid #dcdcdc; border-radius: 6px; margin-top: 12px; font-weight: bold; color: #333333; }
    //     QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 5px; left: 10px; }
    //     QPushButton { background-color: #f7f9fc; border: 1px solid #c4c4c4; border-radius: 8px; font-size: 20px; color: #444444; }
    //     QPushButton:hover { background-color: #e6f0ff; border-color: #4a90e2; }
    //     QPushButton:pressed { background-color: #d0e4ff; padding-top: 2px; padding-left: 2px; }
    //     QPushButton#homeBtn { background-color: #fff2f2; color: #e74c3c; border-color: #f5c6cb; }
    //     QPushButton#homeBtn:hover { background-color: #ffe0e0; border-color: #e74c3c; }
    //     QPushButton#stopBtn { background-color: #e74c3c; color: white; font-size: 18px; border-radius: 8px; }
    //     QPushButton#stopBtn:hover { background-color: #c0392b; }
    //     QPushButton#stopBtn:pressed { background-color: #a5281b; }
    //     QComboBox, QDoubleSpinBox, QSpinBox { border: 1px solid #c4c4c4; border-radius: 4px; padding: 4px; background-color: white; }
    //     QSlider::groove:horizontal { height: 6px; background: #dcdcdc; border-radius: 3px; }
    //     QSlider::handle:horizontal { background: #4a90e2; width: 14px; margin: -4px 0; border-radius: 7px; }
    // )");

}

void XYControlWidget::setupConnections()
{

    /*-----连接信号-----*/

    connect(upBtn, &QPushButton::clicked, this, [=](){
        emit moveRequest(0, getCurrentParams().step);  // Y轴正方向
    });
    connect(downBtn, &QPushButton::clicked, this, [=](){
        emit moveRequest(0, -getCurrentParams().step); // Y轴负方向
    });
    connect(leftBtn, &QPushButton::clicked, this, [=](){
        emit moveRequest(-getCurrentParams().step, 0); // X轴负方向
    });
    connect(rightBtn, &QPushButton::clicked, this, [=](){
        emit moveRequest(getCurrentParams().step, 0);  // X轴正方向
    });

    connect(powerSlider, &QSlider::valueChanged, this, [=](int val){
        powerValueLabel->setText(QString::number(val) + " %");
        // emit powerChanged(val);
    });

    connect(homeBtn, &QPushButton::clicked, this, &XYControlWidget::homeRequest);
    connect(stopBtn, &QPushButton::clicked, this, &XYControlWidget::stopRequest);

}

GalvoParams XYControlWidget::getCurrentParams() const
{

    GalvoParams p;
    QString stepText = comboboxStep->currentText();
    stepText.remove("mm");
    p.step = stepText.toDouble();
    p.speed = speedSpin->value();
    p.frequency = freqSpin->value();
    p.power = powerSlider->value();

    return p;

}

void XYControlWidget::onParamChanged()
{

    emit parametersChanged(getCurrentParams());

}

void XYControlWidget::updateFeedbackData(double x,double y,double angle)
{

    xPosLabel->setText(QString::number(x, 'f', 2) + " mm");
    yPosLabel->setText(QString::number(y, 'f', 2) + " mm");
    angleLabel->setText(QString::number(angle, 'f', 2) + " °");

}
