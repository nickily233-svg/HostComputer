#ifndef CHANNEL_SELECTOR_WIDGET_H
#define CHANNEL_SELECTOR_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>

#ifndef CHANNEL_COUNT
#define CHANNEL_COUNT 4
#endif

class ChannelSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChannelSelectorWidget(QWidget *parent = nullptr);

signals:
    void channelVisibilityChanged(int index, bool checked);

private:
    QCheckBox *chxCheckBox[CHANNEL_COUNT];
    QCheckBox *selectAllCheckBox;
};

#endif // CHANNEL_SELECTOR_WIDGET_H