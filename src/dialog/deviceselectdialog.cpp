#include "src/dialog/deviceselectdialog.h"

DeviceSelectDialog::DeviceSelectDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("选择设备");
    setFixedSize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *SelectDevicelabel = new QLabel("请选择要连接的设备", this);
    SelectDevicelabel->setAlignment(Qt::AlignCenter);

    deviceList = new QListWidget(this);
    deviceList->addItem("SimDevice");

    QPushButton *btnConnect = new QPushButton("Connect", this);
    btnConnect->setFixedWidth(120);
    QPushButton *btnCancel = new QPushButton("Cancel", this);
    btnCancel->setFixedWidth(120);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnConnect);
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();

    mainLayout->addWidget(SelectDevicelabel);
    mainLayout->addWidget(deviceList);
    mainLayout->addLayout(btnLayout);

    // 连接按钮
    connect(btnConnect, &QPushButton::clicked, this, &QDialog::accept);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

QString DeviceSelectDialog::getSelectedDevice() const
{
    if (deviceList->currentItem()) {
        return deviceList->currentItem()->text();
    }
    return "";
}