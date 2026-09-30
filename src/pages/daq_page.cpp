#include "src/ui/daq_page.h"

/*
 * 构造函数
 */
DAQWidget::DAQWidget(QWidget *parent)
    : QWidget(parent),tableWidget(nullptr),WavePlot(nullptr),statusLabel(nullptr),shadowEffect(nullptr)
{
    WaveTimer = new QTimer(this);
    WaveTimer->setSingleShot(false);
    WaveTimer->setInterval(static_cast<double>(30.0f));

    initUI();

    WaveTimer->start();

}

/*
 * 析构函数
 */
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
    onConnectSlot();

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

    // WavePlot->xAxis->setRange(0, 2 * PI);
    // WavePlot->yAxis->setRange(-1.2, 1.2);

    WavePlot->xAxis->setLabel(" X 轴 ");
    WavePlot->yAxis->setLabel(" Y 轴 ");
    WavePlot->xAxis->setLabelFont(QFont("Microsoft YaHei",9));
    WavePlot->yAxis->setLabelFont(QFont("Microsoft YaHei",9));

    // WavePlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    // WavePlot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    // WavePlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);

    // Test
    // x.resize(101);
    // for(int i = 0;i < 101;i++)
    // {
    //     x[i] = i * (2 * PI / 100.0);
    // }
    // y.resize(101);

    // WavePlot->addGraph();
    // WavePlot->graph(0)->setPen(QPen(Qt::black));
    // WavePlot->replot();

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
    // Test
    // connect(WaveTimer,&QTimer::timeout,this,[=](){

    //     static double phase = 0;
    //     phase += 0.1;

    //     for(int i = 0; i < 101; i++) {
    //         y[i] = std::sin(x[i] + phase);
    //     }

    //     WavePlot->graph(0)->setData(x,y);
    //     WavePlot->replot(QCustomPlot::rpQueuedReplot);
    // });

    connect(DragWaveFormCheckBox,&QCheckBox::toggled,this,[=](bool checked){
        if (checked) {
            WavePlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

            // WavePlot->axisRect()->setRangeDrag(Qt::Horizontal);
            // WavePlot->axisRect()->setRangeDrag(Qt::Vertical);
            // WavePlot->axisRect()->setRangeZoom(Qt::Horizontal);
            // WavePlot->axisRect()->setRangeZoom(Qt::Vertical);

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

    /*-----init status-----*/
    if(DragWaveFormCheckBox->isChecked()) {

        WavePlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    }
}

void DAQWidget::ShowWaveLegend()
{

    WavePlot->legend->setVisible(true);
    // WavePlot->legend->setBrush(QColor(255,255,255,150));
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

void DAQWidget::initRightPanelUI()
{
    RightPanelMainLayout = new QVBoxLayout(RightPanelWidget);

    QTableWidget *datatablewidget = initDataTableWidget();
    QWidget *chxwidget = initchannelWidget();
    QWidget *runlerwidget = initRulerWidget();
    QWidget *commandwidget = initCommandWidget();

    RightPanelMainLayout->addWidget(chxwidget);
    RightPanelMainLayout->addWidget(datatablewidget);
    RightPanelMainLayout->addWidget(runlerwidget);
    RightPanelMainLayout->addWidget(commandwidget);

    statusLabel = new QLabel("未连接到设备",this);
    // statusLabel->setFixedSize(200,100);
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

QWidget *DAQWidget::initchannelWidget()
{
    QWidget *ChxWidget = new QWidget(RightPanelWidget);
    QGridLayout *chLayout = new QGridLayout(ChxWidget);
    chLayout->setContentsMargins(0,0,0,0);
    chLayout->setSpacing(5);

    for(int i = 0;i < 4;i++)
    {
        chxCheckBox[i] = new QCheckBox(QString("CH%1").arg(i + 1),ChxWidget);
        chLayout->addWidget(chxCheckBox[i],i / 4,i % 4);

        connect(chxCheckBox[i],&QCheckBox::toggled,this,[=](bool checked){
            if(tableWidget) {
                tableWidget->setRowHidden(i,!checked);
            }
        });
    }

    chxCheckBox[0]->setChecked(true);

    selectAllCheckBox = new QCheckBox("全选",ChxWidget);
    chLayout->addWidget(selectAllCheckBox,0,5);

    connect(selectAllCheckBox,&QCheckBox::toggled,this,[=](bool checked){

        for(int i = 0;i < 4;i++)
        {
            chxCheckBox[i] ->setChecked(checked);
        }

    });

    return ChxWidget;
}

QTableWidget *DAQWidget::initDataTableWidget()
{
    tableWidget = new QTableWidget(RightPanelWidget);

    // 1. col num and label head
    tableWidget->setColumnCount(5);
    tableWidget->setRowCount(4);
    tableWidget->setHorizontalHeaderLabels({"通道名称", "最大值", "最小值", "平均值", "峰峰值"});

    // 2. row num
    tableWidget->setRowCount(4);

    // 3. hide row num
    tableWidget->verticalHeader()->setVisible(false);

    // 4. stretch
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 5. only read
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 6. init table
    for(int row = 0;row < 4;++row) {
        tableWidget->setItem(row,0,new QTableWidgetItem(QString("通道%1").arg(row + 1)));
        tableWidget->item(row, 0)->setTextAlignment(Qt::AlignCenter);
        for(int col = 1;col < 5;++col) {
            QTableWidgetItem *item = new QTableWidgetItem("--");
            item->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(row,col,item);
        }

        tableWidget->setRowHidden(row, true);

    }

    tableWidget->setObjectName("ChxTable");
    tableWidget->setStyleSheet("#ChxTable {}");

    // 7. make sure stretch
    tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    return tableWidget;
}

QWidget *DAQWidget::initRulerWidget()
{
    QWidget *RulerWidget = new QWidget(RightPanelWidget);
    RulerWidget->setObjectName("rulerwidget");
    RulerWidget->setAttribute(Qt::WA_StyledBackground,true);
    RulerWidget->setStyleSheet("#rulerwidget {background-color: 1e1e1e;border: 1px;border-radius: 6px;}");
    QVBoxLayout *RulerMainLayout = new QVBoxLayout(RulerWidget);
    RulerMainLayout->setContentsMargins(5,5,5,5);
    RulerMainLayout->setAlignment(Qt::AlignCenter);
    RulerMainLayout->setSpacing(5);

    /*-----title-----*/
    QWidget *RulerTitleWidget = new QWidget(RulerWidget);
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
    QTreeWidget *RulerTree = new QTreeWidget(RulerWidget);
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

    return RulerWidget;
}

QWidget *DAQWidget::initCommandWidget()
{
    QWidget *CommandWidget = new QWidget(RightPanelWidget);
    QGridLayout *CommandLayout = new QGridLayout(CommandWidget);
    CommandLayout->setContentsMargins(0,5,0,5);
    CommandLayout->setSpacing(5);

    QLabel *lblCmd = new QLabel("自定义指令",CommandWidget);
    QLabel *lblAddr = new QLabel("地址",CommandWidget);
    QLabel *lblData = new QLabel("数据值(32位)",CommandWidget);
    QLabel *lblHex = new QLabel("Hex",CommandWidget);

    QString labelStyle = "QLabel {color: #000000;font-size: 12px;font-family:'Microsoft YaHei';font-weight: bold;}";
    lblCmd->setStyleSheet(labelStyle);
    lblAddr->setStyleSheet(labelStyle);
    lblData->setStyleSheet(labelStyle);
    lblHex->setStyleSheet(labelStyle);

    QPushButton *btnSend = new QPushButton("发送",CommandWidget);
    QLineEdit *editAddr = new QLineEdit("04",CommandWidget);
    editAddr->setAlignment(Qt::AlignCenter);
    QLineEdit *editData = new QLineEdit("00 00 0B 04",CommandWidget);
    editData->setAlignment(Qt::AlignCenter);
    QCheckBox *chkHex = new QCheckBox(CommandWidget);
    chkHex->setChecked(true);

    CommandLayout->addWidget(lblCmd,0,0);
    CommandLayout->addWidget(lblAddr,0,1);
    CommandLayout->addWidget(lblData,0,2);
    CommandLayout->addWidget(lblHex,0,3);

    CommandLayout->addWidget(btnSend,1,0);
    CommandLayout->addWidget(editAddr,1,1);
    CommandLayout->addWidget(editData,1,2);
    CommandLayout->addWidget(chkHex,1,3);

    return CommandWidget;
}

  /*-------------------------------------------------------------------------------------------------------------------------------------*/
bool DAQWidget::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == statusLabel) {

        // 1. enter
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
                "#devicestatusLabel { background-color: #14273f; color: #cccccc; border: 1px solid #0077cc; border-radius: 4px; font-size: 12px; }");


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


