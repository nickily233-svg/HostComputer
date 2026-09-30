#include "command_widget.h"

CommandWidget::CommandWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *CommandLayout = new QGridLayout(this);
    CommandLayout->setContentsMargins(0,5,0,5);
    CommandLayout->setSpacing(5);

    QLabel *lblCmd = new QLabel("自定义指令",this);
    QLabel *lblAddr = new QLabel("地址",this);
    QLabel *lblData = new QLabel("数据值(32位)",this);
    QLabel *lblHex = new QLabel("Hex",this);

    QString labelStyle = "QLabel {color: #000000;font-size: 12px;font-family:'Microsoft YaHei';font-weight: bold;}";
    lblCmd->setStyleSheet(labelStyle);
    lblAddr->setStyleSheet(labelStyle);
    lblData->setStyleSheet(labelStyle);
    lblHex->setStyleSheet(labelStyle);

    btnSend = new QPushButton("发送",this);
    editAddr = new QLineEdit("04",this);
    editAddr->setAlignment(Qt::AlignCenter);
    editData = new QLineEdit("00 00 0B 04",this);
    editData->setAlignment(Qt::AlignCenter);
    chkHex = new QCheckBox(this);
    chkHex->setChecked(true);

    CommandLayout->addWidget(lblCmd,0,0);
    CommandLayout->addWidget(lblAddr,0,1);
    CommandLayout->addWidget(lblData,0,2);
    CommandLayout->addWidget(lblHex,0,3);

    CommandLayout->addWidget(btnSend,1,0);
    CommandLayout->addWidget(editAddr,1,1);
    CommandLayout->addWidget(editData,1,2);
    CommandLayout->addWidget(chkHex,1,3);

    // 额外的信号发送
    connect(btnSend, &QPushButton::clicked, this, [=](){
        emit commandSent(editAddr->text(), editData->text(), chkHex->isChecked());
    });
}