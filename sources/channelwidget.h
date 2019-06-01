#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include <QWidget>

#include "qcustomplot.h"
#include "yresticker.h"

class OscilloWidget;
class Channel;

namespace Ui {
class ChannelWidget;
}

class ChannelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelWidget(Channel *channel, QWidget *parent = nullptr);
    ~ChannelWidget();
    int currentRes();
    void setMathMode(bool mathMode);
    void setChecked(bool checked);

private slots:
    void updateColor(QColor color);

private:
    Ui::ChannelWidget *ui;
    Channel *m_channel;
};

#endif // CHANNELWIDGET_H
