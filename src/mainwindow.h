#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QMenu>
#include <QAction>

// 页面类
#include "src/pages/daq_page.h"
#include "src/pages/galvo_page.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    void setupMenuBar();
    void setupConnect();

    // 槽函数
    void onAboutTriggered();
    void onSelectDeviceTriggered();
    void onExitTriggered();

    // 页面指针
    DAQWidget *daq_page;
    GalvoWidget *Galvo_page;

    // 菜单栏指针
    QMenu *MenuDevice;
    QMenu *MenuFile;
    QMenu *MenuAbout;

    // 动作指针
    QAction *ActSelect;
    QAction *ActOpenADC;
    QAction *ActOpen;
    QAction *ActImportDateFile;
    QAction *ActSaveDateFile;
    QAction *ActExportCSVFile;
    QAction *ActExit;
    QAction *ActSoftwareIntoduction;
    QAction *ActCheckUpdate;
    QAction *ActFeedbackAndAdvice;
    QAction *ActInstructionsAndHelp;
};

#endif // MAINWINDOW_H