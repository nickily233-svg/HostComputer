#ifndef RULER_WIDGET_H
#define RULER_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class RulerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RulerWidget(QWidget *parent = nullptr);

private:
    QTreeWidget *RulerTree;
    int groupCount = 0;
};

#endif // RULER_WIDGET_H