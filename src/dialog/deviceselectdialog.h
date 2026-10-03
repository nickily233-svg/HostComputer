#ifndef DEVICE_SELECT_DIALOG_H
#define DEVICE_SELECT_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

class DeviceSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceSelectDialog(QWidget *parent = nullptr);
    ~DeviceSelectDialog();

public slots:
    QString getSelectedDevice() const;

private:
    QListWidget *deviceList;
};

#endif // DEVICE_SELECT_DIALOG_H