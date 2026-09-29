#include "src/ui/common_widgets.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

CommonWidgets::CommonWidgets(QWidget *parent)
    : QWidget(parent)
{

    this->setWindowTitle("多功能数据采集仪 -- NEFU -- LiuYang");

    initUI();

}

CommonWidgets::~CommonWidgets()
{

}

void CommonWidgets::initUI()
{

}