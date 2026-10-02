#ifndef XY_CONTROL_WIDGET_H
#define XY_CONTROL_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <qdebug.h>

/* galvo parameter */
struct GalvoParams {

    double step = 0.1f;
    double speed = 1000.0f;
    int power = 50;
    int frequency = 20;

};

Q_DECLARE_METATYPE(GalvoParams);

class XYControlWidget : public QWidget
{

    Q_OBJECT

public :
    explicit XYControlWidget(QWidget *parent = nullptr);
    ~XYControlWidget();

public slots :
    void updateFeedbackData(double x,double y,double angle);

private slots:
    void onParamChanged();

private :

    void setupUI();
    void setupStyles();
    void setupConnections();

    GalvoParams getCurrentParams() const;

    /* UI */
    QComboBox *comboboxStep;
    QDoubleSpinBox *speedSpin;
    QSlider *powerSlider;
    QLabel  *powerValueLabel;
    QSpinBox *freqSpin;

    /* Pos Value */
    QLabel *xPosLabel;
    QLabel *yPosLabel;
    QLabel *angleLabel;
    QLabel *dirControlLbl;

    /* command */
    QPushButton *leftBtn;
    QPushButton *rightBtn;
    QPushButton *upBtn;
    QPushButton *downBtn;
    QPushButton *homeBtn;
    QPushButton *stopBtn;

protected :

signals :

    void moveRequest(double dx,double dy);
    void homeRequest();
    void stopRequest();
    void parametersChanged(const GalvoParams &params);

};

#endif // XY_CONTROL_WIDGET_H