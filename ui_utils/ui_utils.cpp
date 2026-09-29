#include "ui_utils.h"

QFrame *createVerticalSeparator(QWidget* parent){

    QFrame *Line = new QFrame(parent);
    Line->setFrameShape(QFrame::VLine);
    Line->setFrameShadow(QFrame::Plain);
    Line->setStyleSheet("background-color:#000000; max-width:0.5px;");

    return Line;

}