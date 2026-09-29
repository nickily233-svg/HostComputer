#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>

#include "src/ui/common_widgets.h"
#include "src/ui/daq_page.h"
#include "src/ui/galvo_page.h"

class MainWindow : public QMainWindow
{

    Q_OBJECT

public :
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
protected :

private :
    /* external page class */
    DAQWidget *daq_page;
    GalvoWidget *Galvo_page;

    /* init */
    void initUI();
    void setupMenuBar();
    void setupConnect();

    /* slot func */
    void onAboutTriggered();
    void onSelectDeviceTriggered();
    void onExitTriggered();

    /* ptr */
    QMenu *MenuDevice;
    QMenu *MenuFile;
    QMenu *MenuAbout;

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