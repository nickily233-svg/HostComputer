#ifndef RIGHTPANELLOG_H
#define RIGHTPANELLOG_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTime>

class RightPanelWidget : public QWidget
{

    Q_OBJECT

public :
    explicit RightPanelWidget(QWidget *Widget = nullptr);
    ~RightPanelWidget();

public slots:

private :
    void initUI();
    void setupConnections();
    void setConnectionStatus(bool isConnected);
    void appendLog(const QString &msg, const QString &level);

    QLabel *lightLbl;
    QLabel *statusLbl;

    QPlainTextEdit *logTextEdit;
    QPushButton *clearBtn;
    QPushButton *saveBtn;

signals:
    void exportLogRequested(const QString &logContent);

};

#endif // RIGHTPANELLOG_H