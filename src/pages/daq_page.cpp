#include "src/pages/daq_page.h"

DAQWidget::DAQWidget(QWidget *parent)
    : QWidget(parent),
    WavePlot(nullptr), statusLabel(nullptr), shadowEffect(nullptr),
    m_channelSelector(nullptr), m_statsTable(nullptr),
    m_rulerWidget(nullptr), m_commandWidget(nullptr)
{
    WaveTimer = new QTimer(this);
    WaveTimer->setSingleShot(false);
    WaveTimer->setInterval(static_cast<double>(30.0f));

    initUI();
    setupConnections();

    WaveTimer->start();
}

DAQWidget::~DAQWidget()
{

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
    QStringList SampleList = {"1000 ", "4000 ", "10000 ", "100000 "};
    QStringList SampleNumList = {"1 ","2 ","3 ","4 "};

    SelectDeviceBtn = new QPushButton("选择设备",topBarWidget);
    SelectDeviceBtn->setToolTip("<b>打开设备</b><br>点击连接数据采集卡</br><br>注意:需提前插好板卡</br>");
    SelectADCBtn = new QPushButton("选择ADC",topBarWidget);
    SelectADCBtn->setToolTip("<b>选择ADC</b>");
    OpenDeviceBtn = new QPushButton("打开设备",topBarWidget);
    OpenDeviceBtn->setToolTip("<b>打开设备</b>");
    SaveDataFileBtn = new QPushButton("保存数据文件(可被导入)",topBarWidget);
    SaveDataFileBtn->setToolTip("<b>保存数据文件(可被导入)</b>");
    ExportCSVFileBtn = new QPushButton("导出CSV文件",topBarWidget);
    ExportCSVFileBtn->setToolTip("<b>导出CSV文件</b>");
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
    topBarLayout->addWidget(ExportCSVFileBtn);
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
    WavePlot->setOpenGl(true);

    WaveLayout->addWidget(WavePlot);

    WavePlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    WavePlot->xAxis->grid()->setPen(gridPen);
    WavePlot->yAxis->grid()->setPen(gridPen);
    WavePlot->xAxis->grid()->setSubGridVisible(false);
    WavePlot->yAxis->grid()->setSubGridVisible(false);

    WavePlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);

    WavePlot->xAxis->setLabel(" X 轴 ");
    WavePlot->yAxis->setLabel(" Y 轴 ");
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

/*
 * 连接槽函数
 */
void DAQWidget::onConnectSlot()
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

    /*-----init status-----*/
    if(DragWaveFormCheckBox->isChecked()) {
        WavePlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    }
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

    m_channelSelector = new ChannelSelectorWidget(RightPanelWidget);
    m_statsTable      = new DataStatisticsTable(RightPanelWidget);
    m_rulerWidget     = new RulerWidget(RightPanelWidget);
    m_commandWidget   = new CommandWidget(RightPanelWidget);

    RightPanelMainLayout->addWidget(m_channelSelector);
    RightPanelMainLayout->addWidget(m_statsTable);
    RightPanelMainLayout->addWidget(m_rulerWidget);
    RightPanelMainLayout->addWidget(m_commandWidget);

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
    onConnectSlot();

    connect(m_channelSelector, &ChannelSelectorWidget::channelVisibilityChanged,
            m_statsTable, &DataStatisticsTable::setRowHidden);

    connect(m_commandWidget, &CommandWidget::commandSent, this,
            [=](QString addr, QString data, bool isHex){
                emit requestSendHardwareCommand(addr, data, isHex);
            });
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