#ifndef ADC_SELECT_H
#define ADC_SELECT_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>

class ADCSelectDialog : public QDialog
{
    Q_OBJECT

public :
    explicit ADCSelectDialog(QWidget *parent = nullptr);
    ~ADCSelectDialog();

    QString getSelectADC() const;

private :
    void initDialog();

    QListWidget *adcList;
    QLabel *InformationLbl;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

signals :
    void onSelectADCCahenged();

};

#endif // ADC_SELECT_H
