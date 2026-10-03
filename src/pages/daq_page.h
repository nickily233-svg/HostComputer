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

#include "src/widgets/ruler_widget.h"
#include "src/widgets/command_widget.h"
#include "src/widgets/channel_selector.h"
#include "src/widgets/data_statistics_table.h"
#include "qcustomplot.h"

#ifndef CHANNEL_COUNT
#define CHANNEL_COUNT 4
#endif

class DAQWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DAQWidget(QWidget *parent = nullptr);
    ~DAQWidget();

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
    void onConnectSlot();

    QHBoxLayout *TopBarHLayout;

    QWidget *topBarWidget;
    QWidget *RightPanelWidget;
    QWidget *waveAreaWidget;
    QWidget *BottomStatusBar;

    QPushButton *SelectDeviceBtn;
    QPushButton *SelectADCBtn;
    QPushButton *OpenDeviceBtn;
    QPushButton *SaveDataFileBtn;
    QPushButton *ExportCSVFileBtn;
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

    /*-----ptr-----*/
    void initRightPanelUI();

    ChannelSelectorWidget *m_channelSelector;
    DataStatisticsTable   *m_statsTable;
    RulerWidget           *m_rulerWidget;
    CommandWidget         *m_commandWidget;

    QVBoxLayout *RightPanelMainLayout;

    QLabel *statusLabel;
    QGraphicsDropShadowEffect *shadowEffect;

    /*-----variable-----*/
    QVector<double> x;
    QVector<double> y;
    const double PI = 3.14159265358979323846;

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

signals:
    void SelectDeviceClicked();
    void SelectADCClicked();
    void requestSendHardwareCommand(QString addr, QString data, bool isHex);
};

#endif // DAQ_PAGE_H