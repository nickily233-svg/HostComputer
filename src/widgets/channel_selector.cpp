#include "src/widgets/channel_selector.h"

ChannelSelectorWidget::ChannelSelectorWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *chLayout = new QGridLayout(this);
    chLayout->setContentsMargins(0,0,0,0);
    chLayout->setSpacing(5);

    for(int i = 0;i < CHANNEL_COUNT;i++)
    {
        chxCheckBox[i] = new QCheckBox(QString("CH%1").arg(i + 1),this);
        chLayout->addWidget(chxCheckBox[i],i / 4,i % 4);

        connect(chxCheckBox[i],&QCheckBox::toggled,this,[=](bool checked){
            emit channelVisibilityChanged(i, checked);
        });
    }

    chxCheckBox[0]->setChecked(true);

    selectAllCheckBox = new QCheckBox("全选",this);
    chLayout->addWidget(selectAllCheckBox,0,5);

    connect(selectAllCheckBox,&QCheckBox::toggled,this,[=](bool checked){
        for(int i = 0;i < CHANNEL_COUNT;i++)
        {
            chxCheckBox[i] ->setChecked(checked);
        }
    });
}