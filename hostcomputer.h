#ifndef HOSTCOMPUTER_H
#define HOSTCOMPUTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class HostComputer;
}
QT_END_NAMESPACE

class HostComputer : public QMainWindow
{
    Q_OBJECT

public:
    explicit HostComputer(QWidget *parent = nullptr);
    ~HostComputer() override;

private:
    Ui::HostComputer *ui;
};
#endif // HOSTCOMPUTER_H
