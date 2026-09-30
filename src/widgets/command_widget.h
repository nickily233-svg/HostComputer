#ifndef COMMAND_WIDGET_H
#define COMMAND_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

class CommandWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CommandWidget(QWidget *parent = nullptr);

signals:
    void commandSent(const QString &addr, const QString &data, bool isHex);

private:
    QPushButton *btnSend;
    QLineEdit *editAddr;
    QLineEdit *editData;
    QCheckBox *chkHex;
};

#endif // COMMAND_WIDGET_H