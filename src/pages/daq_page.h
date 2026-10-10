#ifndef DAQ_PAGE_H
#define DAQ_PAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QStringList>
#include <QButtonGroup>
#include <QSpinBox>
#include <QProgressBar>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QTimer>
#include <QPen>
#include <QGraphicsDropShadowEffect>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QScrollArea>
#include <QHeaderView>
#include <QLineEdit>
#include <QThread>

#include "src/widgets/ruler_widget.h"
#include "src/widgets/command_widget.h"
#include "src/widgets/channel_selector.h"
#include "src/widgets/data_statistics_table.h"
#include "qcustomplot.h"
#include "src/drivers/idevice.h"
#include "src/drivers/mock_device.h"
#include "src/drivers/daq_worker.h"

#ifndef CHANNEL_COUNT
#define CHANNEL_COUNT 4
#endif

class DAQWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DAQWidget(QWidget *parent = nullptr);
    ~DAQWidget();

private slots:
    void onDataReady(const QByteArray &rawData,quint64 bytesRead);
    void onStatusUpdated(const DAQStatus &status);

    /* 设备控制槽函数 */
    void onOpenDeviceBtnClicked();   // 处理打开/停止采集按钮
    void onSelectDeviceBtnClicked(); // 处理选择设备按钮
    void onSampleRateChanged(int index); // 处理采样率改变

protected:
    bool eventFilter(QObject *wtched, QEvent *event) override;

private:
    void initUI();
    void initTopBar();
    void initRightBar();
    void initWaveArea();
    void initBottomStatusBar();
    void setupConnections();
    void ShowWaveLegend();

    QHBoxLayout *TopBarHLayout;

    QWidget *topBarWidget;
    QWidget *RightPanelWidget;
    QWidget *waveAreaWidget;
    QWidget *BottomStatusBar;

    QPushButton *SelectDeviceBtn;
    QPushButton *SelectADCBtn;
    QPushButton *OpenDeviceBtn;
    QPushButton *SaveDataFileBtn;
    QPushButton *ExportFileBtn;
    QPushButton *ImportDataFileBtn;

    QLabel *SampleRate;
    QComboBox *SampleRateComboBox;
    QLabel *SampleNum;
    QComboBox *SampleNumComboBox;
    QComboBox *UnitComboBox;
    QLabel *ClockPeriod;
    QSpinBox *ClockPeriodComboBox;

    QCheckBox *DragWaveFormCheckBox;
    QCheckBox *ZoomAreaCheckBox;
    QCheckBox *LoopSamingCheckBox;

    QStringList edgeTypeList = {"rise","fall","any"};
    int currentEdgeIndex = 1;
    QPushButton *edgeTypeBtn;
    QDoubleSpinBox *triggerLevelSpinBox;

    QButtonGroup *exclusiveGroup;

    QCustomPlot *WavePlot;
    QTimer *WaveTimer;

    QLabel *ADCLabel;
    QLabel *CommunicationLabel;
    QLabel *StatusLabel;
    QProgressBar *progressBar;
    QLabel *percentLabel;

    QStringList ChxList = {"通道1","通道2","通道3","通道4"};

    /* 设备状态 */
    bool isDeviceSelected = false; // 是否选择了设备
    bool isDeviceOpened = false; // 是否已打开设备
    bool isAcquiring = false; // 是否正在采集
    DAQConfig currentConfig; // 保存当前设备的配置

    /*-----ptr-----*/
    void initRightPanelUI();

    ChannelSelectorWidget *channelSelector;
    DataStatisticsTable   *statsTable;
    RulerWidget           *rulerWidget;
    CommandWidget         *commandWidget;

    QVBoxLayout *RightPanelMainLayout;

    QLabel *statusLabel;
    QGraphicsDropShadowEffect *shadowEffect;

    /*-----variable-----*/
    QVector<double> x;
    QVector<double> y;

    QVector<QColor> colors = {
        Qt::red,
        Qt::yellow,
        Qt::green,
        Qt::cyan,
        Qt::blue,
        Qt::magenta,
        Qt::lightGray,
        Qt::darkCyan
    };

    IDevice *device;
    uint64_t sampleCounter = 0;

    /* Thread */
    QThread *daqThread;
    DAQWorker *daqWorker;

signals:
    void SelectDeviceClicked();
    void SelectADCClicked();
    void requestSendHardwareCommand(QString addr, QString data, bool isHex);
};

#endif // DAQ_PAGE_H