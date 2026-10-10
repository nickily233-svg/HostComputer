#include "src/pages/daq_page.h"

DAQWidget::DAQWidget(QWidget *parent)
    : QWidget(parent),
    WavePlot(nullptr), statusLabel(nullptr), shadowEffect(nullptr),
    channelSelector(nullptr), statsTable(nullptr),
    rulerWidget(nullptr), commandWidget(nullptr)
{
    WaveTimer = new QTimer(this);
    WaveTimer->setSingleShot(false);
    WaveTimer->setInterval(static_cast<double>(30.0f));

    // UI
    initUI();
    setupConnections();

    // 创建模拟设备
    device = new MockDevice();
    // 创建线程和 Worker
    daqThread = new QThread(this);
    daqWorker = new DAQWorker(device);

    daqWorker->moveToThread(daqThread);

    // 连接信号槽
    // 1. 开始采集线程
    connect(daqThread,&QThread::started,daqWorker,&DAQWorker::startAcquisition);
    // 2. 接受数据
    connect(daqWorker,&DAQWorker::dataReady,this,&DAQWidget::onDataReady);
    connect(daqWorker,&DAQWorker::statusUpdated,this,&DAQWidget::onStatusUpdated);
    // WaveTimer->start();
}

DAQWidget::~DAQWidget()
{
    /*** 先停止线程 再删除设备 ***/
    // 1. 通知 Worker 停止采集循环
    if(daqWorker) {
        daqWorker->stopAcquisition();
    }
    // 2. 退出线程并等待
    if(daqThread) {
        daqThread->quit();
        daqThread->wait(); // 等待线程完全结束
    }
    // 3. 删除 Worker
    if(daqWorker) {
        delete daqWorker;
        daqWorker = nullptr;
    }
    // 4. 关闭并删除设备
    if (device) {
        device->stop();
        device->close();
        delete device;
        device = nullptr;
    }
}

/*
 * 初始化主体 UI
 */
void DAQWidget::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    topBarWidget = new QWidget(this);
    RightPanelWidget = new QWidget(this);
    RightPanelWidget->setObjectName("rightpanelwidget");
    RightPanelWidget->setStyleSheet("#rightpanelwidget {background-color: transparent;}");
    waveAreaWidget = new QWidget(this);
    BottomStatusBar  = new QWidget(this);

    mainLayout->addWidget(topBarWidget,0);

    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addWidget(waveAreaWidget,static_cast<double>(3.0f));
    centerLayout->addWidget(RightPanelWidget,static_cast<double>(1.0f));

    mainLayout->addLayout(centerLayout,1);
    mainLayout->addWidget(BottomStatusBar);

    initTopBar();
    initRightBar();
    initWaveArea();
    initBottomStatusBar();
}

/*
 * 初始化顶部 BAR'UI
 */
void DAQWidget::initTopBar()
{
    QHBoxLayout *topBarLayout = new QHBoxLayout(topBarWidget);
    QStringList SampleList = {"1000", "4000", "10000", "100000"};
    QStringList SampleNumList = {"1 ","2 ","3 ","4 "};

    SelectDeviceBtn = new QPushButton("选择设备",topBarWidget);
    SelectDeviceBtn->setToolTip("<b>打开设备</b><br>点击连接数据采集卡</br><br>注意:需提前插好板卡</br>");
    SelectADCBtn = new QPushButton("选择ADC",topBarWidget);
    SelectADCBtn->setToolTip("<b>选择ADC</b>");
    OpenDeviceBtn = new QPushButton("打开设备",topBarWidget);
    OpenDeviceBtn->setToolTip("<b>打开设备</b>");
    SaveDataFileBtn = new QPushButton("保存数据文件(可被导入)",topBarWidget);
    SaveDataFileBtn->setToolTip("<b>保存数据文件(可被导入)</b>");
    ExportFileBtn = new QPushButton("导出文件",topBarWidget);
    ExportFileBtn->setToolTip("<b>导出文件</b>");
    ImportDataFileBtn = new QPushButton("导入数据文件",topBarWidget);
    ImportDataFileBtn->setToolTip("<b>导入数据文件</b>");

    SampleRate = new QLabel("采样速率",topBarWidget);
    SampleRateComboBox = new QComboBox(topBarWidget);
    SampleRateComboBox->addItems(SampleList);

    SampleNum = new QLabel("采样数量",topBarWidget);
    SampleNumComboBox = new QComboBox(topBarWidget);
    SampleNumComboBox->addItems(SampleNumList);

    UnitComboBox = new QComboBox(topBarWidget);
    UnitComboBox->addItem("K");
    UnitComboBox->addItem("M");
    ClockPeriod = new QLabel("时钟周期",topBarWidget);
    ClockPeriodComboBox = new QSpinBox(topBarWidget);
    ClockPeriodComboBox->setValue(10);
    ClockPeriodComboBox->setRange(1,10000);
    ClockPeriodComboBox->setSingleStep(1);

    DragWaveFormCheckBox = new QCheckBox("拖动波形",topBarWidget);
    ZoomAreaCheckBox = new QCheckBox("框选放大",topBarWidget);
    LoopSamingCheckBox = new QCheckBox("循环采样",topBarWidget);

    edgeTypeBtn = new QPushButton(edgeTypeList[currentEdgeIndex],topBarWidget);
    triggerLevelSpinBox = new QDoubleSpinBox(topBarWidget);

    exclusiveGroup = new QButtonGroup(topBarWidget);
    exclusiveGroup->addButton(DragWaveFormCheckBox);
    exclusiveGroup->addButton(ZoomAreaCheckBox);

    topBarLayout->addWidget(SelectDeviceBtn);
    topBarLayout->addWidget(SelectADCBtn);
    topBarLayout->addWidget(OpenDeviceBtn);
    topBarLayout->addWidget(SaveDataFileBtn);
    topBarLayout->addWidget(ExportFileBtn);
    topBarLayout->addWidget(ImportDataFileBtn);

    topBarLayout->addWidget(SampleRate);
    topBarLayout->addWidget(SampleRateComboBox);
    topBarLayout->addWidget(SampleNum);
    topBarLayout->addWidget(SampleNumComboBox);

    topBarLayout->addWidget(UnitComboBox);
    topBarLayout->addWidget(ClockPeriod);
    topBarLayout->addWidget(ClockPeriodComboBox);
    topBarLayout->addWidget(DragWaveFormCheckBox);
    topBarLayout->addWidget(ZoomAreaCheckBox);
    topBarLayout->addWidget(LoopSamingCheckBox);

    topBarLayout->addStretch();

    topBarLayout->addWidget(edgeTypeBtn);
    topBarLayout->addWidget(triggerLevelSpinBox);

    /*-----init-----*/
    DragWaveFormCheckBox->setChecked(true);
}

/*
 * 初始化右侧 BAR'UI
 */
void DAQWidget::initRightBar()
{
    initRightPanelUI();
}

/*
 * 初始化波形区域 UI
 */
void DAQWidget::initWaveArea()
{
    QPen gridPen(QColor(80,80,80),1,Qt::DashLine);

    QVBoxLayout *WaveLayout = new QVBoxLayout(waveAreaWidget);
    WaveLayout->setContentsMargins(0,0,0,0);
    WaveLayout->setSpacing(0);

    WavePlot = new QCustomPlot(waveAreaWidget);
    ShowWaveLegend();
    WavePlot->setOpenGl(false);
    WavePlot->setNoAntialiasingOnDrag(true);
    // WavePlot->setNotAntialiasedElements(QCP::aeAll);

    WaveLayout->addWidget(WavePlot);

    WavePlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    WavePlot->xAxis->grid()->setPen(gridPen);
    WavePlot->yAxis->grid()->setPen(gridPen);
    WavePlot->xAxis->grid()->setSubGridVisible(false);
    WavePlot->yAxis->grid()->setSubGridVisible(false);

    WavePlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);

    WavePlot->xAxis->setLabel("X 轴");
    WavePlot->yAxis->setLabel("Y 轴");
    WavePlot->xAxis->setLabelFont(QFont("Microsoft YaHei",9));
    WavePlot->yAxis->setLabelFont(QFont("Microsoft YaHei",9));

    waveAreaWidget->setLayout(WaveLayout);
}

/*
 * 底部状态栏
 */
void DAQWidget::initBottomStatusBar()
{
    QHBoxLayout *BottomStatusLayout = new QHBoxLayout(BottomStatusBar);
    BottomStatusLayout->setContentsMargins(5,0,5,0);
    BottomStatusLayout->setSpacing(5);

    ADCLabel = new QLabel("暂未指定ADC");
    CommunicationLabel = new QLabel("未选择通信方式");
    StatusLabel = new QLabel("尚未开始采样");
    progressBar = new QProgressBar(BottomStatusBar);
    progressBar->setTextVisible(false);
    percentLabel = new QLabel("0%",BottomStatusBar);

    BottomStatusLayout->addWidget(ADCLabel);
    BottomStatusLayout->addWidget(CommunicationLabel);

    BottomStatusLayout->addStretch();

    BottomStatusLayout->addWidget(StatusLabel);
    BottomStatusLayout->addWidget(progressBar);
    BottomStatusLayout->addWidget(percentLabel);

    BottomStatusLayout->addStretch();
}

void DAQWidget::ShowWaveLegend()
{
    WavePlot->legend->setVisible(true);
    WavePlot->legend->setTextColor(Qt::black);
    WavePlot->legend->setFont(QFont("Microsoft YaHei", 9));
    WavePlot->legend->setBorderPen(Qt::NoPen);

    WavePlot->legend->setIconSize(20,10);
    WavePlot->legend->setRowSpacing(-3);
    WavePlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);

    for(int i = 0;i < ChxList.size();i++)
    {
        WavePlot->addGraph();
        WavePlot->graph(i)->setName(ChxList[i]);
        WavePlot->graph(i)->setPen(QPen(colors[i % ChxList.size()]));
    }
}

/*
 * 右侧面板组装
 */
void DAQWidget::initRightPanelUI()
{
    RightPanelMainLayout = new QVBoxLayout(RightPanelWidget);

    channelSelector = new ChannelSelectorWidget(RightPanelWidget);
    statsTable      = new DataStatisticsTable(RightPanelWidget);
    rulerWidget     = new RulerWidget(RightPanelWidget);
    commandWidget   = new CommandWidget(RightPanelWidget);

    RightPanelMainLayout->addWidget(channelSelector);
    RightPanelMainLayout->addWidget(statsTable);
    RightPanelMainLayout->addWidget(rulerWidget);
    RightPanelMainLayout->addWidget(commandWidget);

    statusLabel = new QLabel("未连接到设备",this);
    statusLabel->setFixedHeight(100);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setObjectName("devicestatusLabel");
    statusLabel->setStyleSheet("#devicestatusLabel {background-color: #1e3a5f; color: #ffffff; border: 1px solid transparent; border-radius: 4px; font-size: 14px;}");

    // mouse track
    statusLabel->setAttribute(Qt::WA_Hover,true);
    statusLabel->setCursor(Qt::PointingHandCursor);
    statusLabel->installEventFilter(this);

    RightPanelMainLayout->addWidget(statusLabel);

    shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(15);
    shadowEffect->setOffset(0);
    statusLabel->setGraphicsEffect(shadowEffect);
}

/*
 * 统一的信号连接
 */
void DAQWidget::setupConnections()
{
    connect(DragWaveFormCheckBox,&QCheckBox::toggled,this,[=](bool checked){
        if (checked) {
            WavePlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
            WavePlot->setSelectionRectMode(QCP::srmNone);
        } else {
            WavePlot->setInteractions(QCP::iNone);
            WavePlot->setSelectionRectMode(QCP::srmNone);
        }
    });

    connect(ZoomAreaCheckBox, &QCheckBox::toggled, this, [=](bool checked){
        if (checked) {
            WavePlot->setInteractions(QCP::iNone);
            WavePlot->setSelectionRectMode(QCP::srmZoom);
            WavePlot->selectionRect()->setPen(QPen(Qt::blue, 1, Qt::DashLine));
            WavePlot->selectionRect()->setBrush(QBrush(QColor(0, 170, 255, 50)));
        } else {
            WavePlot->setSelectionRectMode(QCP::srmNone);
            WavePlot->setInteractions(QCP::iNone);
        }
    });

    connect(edgeTypeBtn,&QPushButton::clicked,this,[=](){
        currentEdgeIndex = (currentEdgeIndex + 1) % edgeTypeList.size();
        edgeTypeBtn->setText(edgeTypeList[currentEdgeIndex]);
    });

    connect(SelectDeviceBtn,&QPushButton::clicked,this,[=](){
        emit SelectDeviceClicked();
    });

    connect(SelectADCBtn,&QPushButton::clicked,this,[=](){
        emit SelectADCClicked();
    });

    if(DragWaveFormCheckBox->isChecked()) {
        WavePlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    }

    /* 通道选择 */
    connect(channelSelector, &ChannelSelectorWidget::channelVisibilityChanged,this,[=](int row,bool checked){
        /* 控制表格行的隐藏/显示 */
        statsTable->setRowHidden(row,!checked);
        /* 控制波形图层的隐藏/显示 */
        if(row >= 0 && row < WavePlot->graphCount()) {
            WavePlot->graph(row)->setVisible(checked);
            WavePlot->replot();
        }
    });

    connect(commandWidget, &CommandWidget::commandSent, this,
        [=](QString addr, QString data, bool isHex){
            emit requestSendHardwareCommand(addr, data, isHex);
    });

    connect(OpenDeviceBtn,&QPushButton::clicked,this,&DAQWidget::onOpenDeviceBtnClicked);
    connect(SelectDeviceBtn,&QPushButton::clicked,this,&DAQWidget::onSelectDeviceBtnClicked);

    /* 采样率发生变化 */
    connect(SampleRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &DAQWidget::onSampleRateChanged);

    WavePlot->graph(1)->setVisible(false);
    WavePlot->graph(2)->setVisible(false);
    WavePlot->graph(3)->setVisible(false);
    statsTable->setRowHidden(0,false);
}

void DAQWidget::onOpenDeviceBtnClicked()
{
    if(!isDeviceOpened) {
        if(device->open()) {
            currentConfig.channels = 4;
            currentConfig.bitDepth = 16;
            currentConfig.isInterleaved = true;
            currentConfig.sampleRate = SampleRateComboBox->currentText().trimmed().toDouble();

            device->configure(currentConfig);
            device->start();
            if(!daqThread->isRunning()) {
                daqThread->start();
            }
            // status change
            isDeviceOpened = true;
            isAcquiring = true;

            OpenDeviceBtn->setText("停止采集");
            statusLabel->setText("已连接到设备\n正在采集...");
            StatusLabel->setText("正在采样");
        } else {
            qDebug() << "打开设备失败:" << QString::fromStdString(device->getError());
        }
    } else {
        device->stop();
        device->close();
        /*** 通知 Worker 停止采集循环 ***/
        daqWorker->stopAcquisition();

        isDeviceOpened = false;
        isAcquiring = false;

        OpenDeviceBtn->setText("打开设备");
        statusLabel->setText("未连接到设备");
        StatusLabel->setText("已停止采样");
    }
}

void DAQWidget::onSelectDeviceBtnClicked()
{

}

void DAQWidget::onSampleRateChanged(int index)
{
    Q_UNUSED(index);

    if(isDeviceOpened) {
        isAcquiring = false;
        device->stop();
        currentConfig.sampleRate = SampleRateComboBox->currentText().toDouble();
        device->configure(currentConfig);
        device->start();
        isAcquiring = true;
        OpenDeviceBtn->setText("停止采集");
        StatusLabel->setText("正在采样");
        qDebug() << "采样率已切换为:" << currentConfig.sampleRate;
    }
}

void DAQWidget::onDataReady(const QByteArray &rawData, quint64 bytesRead)
{
    const int16_t *samples = reinterpret_cast<const int16_t*>(rawData.constData());
    size_t totalSamples = bytesRead / sizeof(int16_t);
    size_t pointsPerChannel = totalSamples / 4;

    static QVector<double> x(pointsPerChannel);
    static std::vector<QVector<double>> yChannels(4, QVector<double>(pointsPerChannel));

    if(!WavePlot || WavePlot->graphCount() < 4) {
        return;
    }

    if (x.size() != (int)pointsPerChannel) {
        x.resize(pointsPerChannel);
        for (int ch = 0; ch < 4; ++ch) {
            yChannels[ch].resize(pointsPerChannel);
        }
    }

    for (size_t i = 0; i < pointsPerChannel; ++i) {
        x[i] = sampleCounter + i;
        for (int ch = 0; ch < 4; ++ch) {
            yChannels[ch][i] = samples[i * 4 + ch] / 20000.0;
        }
    }
    sampleCounter += pointsPerChannel;

    for (int ch = 0; ch < 4; ++ch) {
        WavePlot->graph(ch)->setData(x,yChannels[ch],true);
        if (WavePlot->graph(ch)->dataCount() > 200000) {
            WavePlot->graph(ch)->data()->removeBefore(sampleCounter - 50000);
        }
    }

    // double currentUpper = WavePlot->xAxis->range().upper;
    // if (std::abs(currentUpper - sampleCounter) < pointsPerChannel * 2) {
    //     WavePlot->xAxis->setRange(sampleCounter, pointsPerChannel, Qt::AlignRight);
    // }
    WavePlot->xAxis->setRange(sampleCounter, pointsPerChannel, Qt::AlignRight);
    WavePlot->replot(QCustomPlot::rpQueuedReplot);
}

void DAQWidget::onStatusUpdated(const DAQStatus &status)
{

}

/*
 * 悬停特效
 */
bool DAQWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == statusLabel) {
        if(event->type() == QEvent::Enter) {
            statusLabel->setStyleSheet(
                "#devicestatusLabel {background-color: #1e3a5f; color: #ffffff; border: 1px solid #00aaff; border-radius: 4px; font-size: 12px; font-weight: bold;}"
                );
            shadowEffect->setColor(QColor(0,170,255,180));
            shadowEffect->setBlurRadius(15);
        }else if(event->type() == QEvent::Leave) {
            statusLabel->setStyleSheet(
                "#devicestatusLabel {background-color: #2b2b2b; color: #aaaaaa; border: 1px solid #444; border-radius: 4px; font-size: 12px;}"
                );
            shadowEffect->setColor(QColor(0,150,255,0));
            shadowEffect->setBlurRadius(15);
        }else if(event->type() == QEvent::MouseButtonPress) {
            statusLabel->setStyleSheet(
                "#devicestatusLabel { background-color: #14273f; color: #cccccc; border: 1px solid #0077cc; border-radius: 4px; font-size: 12px; }"
                );
        }else if(event->type() == QEvent::MouseButtonRelease) {
            statusLabel->setStyleSheet(
                "#devicestatusLabel {background-color: #1e3a5f; color: #ffffff; border: 1px solid #00aaff; border-radius: 4px; font-size: 12px; font-weight: bold;}"
                );
            emit SelectDeviceClicked();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}