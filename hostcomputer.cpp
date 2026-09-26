#include "hostcomputer.h"
#include "ui_hostcomputer.h"

HostComputer::HostComputer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HostComputer)
{
    ui->setupUi(this);
}

HostComputer::~HostComputer()
{
    delete ui;
}
