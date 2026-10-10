#ifndef GALVOWIDGET_H
#define GALVOWIDGET_H

#include <QWidget>
#include "qcustomplot.h"
#include "src/widgets/xy_control_widget.h"
#include "src/widgets/center_galvo_pos_panel.h"
#include "src/widgets/right_panel_log.h"

class GalvoWidget : public QWidget
{
    Q_OBJECT

public :
    explicit GalvoWidget(QWidget *parent = nullptr);
    ~GalvoWidget();

protected :


private :
    void initUI();
    QWidget *createLeftPanel();
    QWidget *createRightPanel();
    QWidget *createCenterPanel();
    void setupConnections();

    /*-----Left Controller-----*/
    XYControlWidget *xycontrolwidget;
    /*-----Center Controller-----*/
    CenterGalvoWidget *centergalvowidget;
    /*-----Right Controller-----*/
    RightPanelWidget *rightpanelwidget;

signals :

};

#endif // GALVOWIDGET_H