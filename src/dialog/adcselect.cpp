#include "src/dialog/adcselect.h"

ADCSelectDialog::ADCSelectDialog(QWidget *parent)
    :   QDialog(parent)
{

    this->setWindowTitle("选择ADC");
    this->setFixedSize(400,300);
    initDialog();
}

ADCSelectDialog::~ADCSelectDialog()
{

}

void ADCSelectDialog::initDialog()
{
    QGridLayout *mainLayout = new QGridLayout(this);
    InformationLbl = new QLabel("请选择要使用的ADC设备:",this);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    confirmBtn = new QPushButton("确认", this);
    cancelBtn = new QPushButton("取消", this);

    adcList = new QListWidget(this);
    adcList->addItem("ADC-1");
    adcList->addItem("ADC-2");
    adcList->addItem("ADC-3");
    adcList->setCurrentRow(0);

    btnLayout->addStretch();
    btnLayout->addWidget(confirmBtn);
    btnLayout->addWidget(cancelBtn);

    mainLayout->addWidget(InformationLbl,0,0);
    mainLayout->addWidget(adcList,1,0);
    mainLayout->addLayout(btnLayout,2,0);

    connect(confirmBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

}

QString ADCSelectDialog::getSelectADC() const
{
    if(adcList->currentItem())
    {
        return adcList->currentItem()->text();
    }

    return QString();
}