#ifndef GALVOWIDGET_H
#define GALVOWIDGET_H

#include <QWidget>

class GalvoWidget : public QWidget
{
    Q_OBJECT

public :
    explicit GalvoWidget(QWidget *parent = nullptr);
    ~GalvoWidget();

protected :


private :

    void initUI();

};

#endif // GALVOWIDGET_H