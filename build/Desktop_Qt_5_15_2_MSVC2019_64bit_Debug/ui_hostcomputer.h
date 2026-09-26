/********************************************************************************
** Form generated from reading UI file 'hostcomputer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSTCOMPUTER_H
#define UI_HOSTCOMPUTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HostComputer
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HostComputer)
    {
        if (HostComputer->objectName().isEmpty())
            HostComputer->setObjectName(QString::fromUtf8("HostComputer"));
        HostComputer->resize(800, 600);
        centralwidget = new QWidget(HostComputer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        HostComputer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HostComputer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        HostComputer->setMenuBar(menubar);
        statusbar = new QStatusBar(HostComputer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HostComputer->setStatusBar(statusbar);

        retranslateUi(HostComputer);

        QMetaObject::connectSlotsByName(HostComputer);
    } // setupUi

    void retranslateUi(QMainWindow *HostComputer)
    {
        HostComputer->setWindowTitle(QCoreApplication::translate("HostComputer", "HostComputer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HostComputer: public Ui_HostComputer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSTCOMPUTER_H
