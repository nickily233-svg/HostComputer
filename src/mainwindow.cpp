#include "src/mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QDateTime>
#include <QDialog>

// ⭐ 引入刚才解耦的独立组件
#include "src/dialog/deviceselectdialog.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1280, 800);
    this->setWindowTitle("多功能数据采集仪 -- NEFU -- LiuYang");
    initUI();
}

MainWindow::~MainWindow()
{
}

/*
 * 初始化主体 UI
 */
void MainWindow::initUI()
{
    setupMenuBar();

    QTabWidget *tabWidget = new QTabWidget(this);

    daq_page = new DAQWidget(tabWidget);
    Galvo_page = new GalvoWidget(tabWidget);

    tabWidget->addTab(daq_page, "数据采集");
    tabWidget->addTab(Galvo_page, "振镜控制");

    this->setCentralWidget(tabWidget);

    setupConnect();
}

/*
 * 设置菜单 BAR
 */
void MainWindow::setupMenuBar()
{
    QMenuBar *MenuBar = this->menuBar();

    MenuDevice = MenuBar->addMenu("设备");
    MenuFile = MenuBar->addMenu("文件");
    MenuAbout = MenuBar->addMenu("关于");

    ActSelect = new QAction("选择设备", this);
    ActOpenADC = new QAction("打开ADC", this);
    ActOpen = new QAction("打开设备", this);

    ActImportDateFile = new QAction("导入数据文件", this);
    ActSaveDateFile = new QAction("保存数据文件", this);
    ActExportCSVFile = new QAction("导出CSV文件", this);
    ActExit = new QAction("退出", this);

    ActSoftwareIntoduction = new QAction("软件介绍", this);
    ActCheckUpdate = new QAction("检查更新", this);
    ActFeedbackAndAdvice = new QAction("反馈建议", this);
    ActInstructionsAndHelp = new QAction("使用说明/帮助", this);

    MenuDevice->addAction(ActSelect);
    MenuDevice->addAction(ActOpenADC);
    MenuDevice->addAction(ActOpen);

    MenuFile->addAction(ActImportDateFile);
    MenuFile->addAction(ActSaveDateFile);
    MenuFile->addAction(ActExportCSVFile);
    MenuFile->addAction(ActExit);

    MenuAbout->addAction(ActSoftwareIntoduction);
    MenuAbout->addAction(ActCheckUpdate);
    MenuAbout->addAction(ActFeedbackAndAdvice);
    MenuAbout->addAction(ActInstructionsAndHelp);
}

/*
 * 设置连接槽函数
 */
void MainWindow::setupConnect()
{
    connect(ActSoftwareIntoduction, &QAction::triggered, this, [=](){
        QMessageBox *MsgBox = new QMessageBox(this);
        MsgBox->setMinimumSize(400, 300);
        MsgBox->setWindowTitle("关于");
        MsgBox->setText("多功能数据采集仪\n 版本:2026/9/27 \n 开发者: NEFU LiuYang");
        MsgBox->show();
    });

    connect(ActExit, &QAction::triggered, this, &MainWindow::onExitTriggered);
    connect(ActSelect, &QAction::triggered, this, &MainWindow::onSelectDeviceTriggered);

    // 接收 DAQWidget 发出的选择设备信号
    connect(this->daq_page, &DAQWidget::SelectDeviceClicked, this, &MainWindow::onSelectDeviceTriggered);
}

/*
 * 触发 Menu about - SoftwareIntoduction 槽函数
 */
void MainWindow::onAboutTriggered()
{
    QString dataStr = QDateTime::currentDateTime().toString("yyyy/MM/dd");
    QString AboutStr = QString("多功能数据采集仪\n版本:%1\n开发者:NEFU LiuYang").arg(dataStr);
}

/*
 * 触发 Menu File - Exit 槽函数
 */
void MainWindow::onExitTriggered()
{
    this->close();
}

/*
 * 触发 Menu Device - Select Device 槽函数
 */
void MainWindow::onSelectDeviceTriggered()
{
    // ⭐ 改为直接调用独立组件，代码极其清爽
    DeviceSelectDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString selectedDevice = dialog.getSelectedDevice();
        if (!selectedDevice.isEmpty()) {
            // TODO: 这里可以处理设备连接后的逻辑，比如更新界面状态
            qDebug() << "用户选择了设备：" << selectedDevice;
        }
    }
}