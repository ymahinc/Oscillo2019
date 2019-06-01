#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>
class ChannelWidget;
class OscilloWidget;
class Channel;

class MYTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    MYTabWidget(OscilloWidget *plotter, QWidget *parent = nullptr);
    void addChannel(Channel *channel = 0);
    ChannelWidget *channel(int index);

signals:
    void resChanged(int index);
    void colorChanged(QColor color, int index);

private:
    QVector<ChannelWidget *> m_channelsWidgets;
    OscilloWidget *m_plotter;
    ChannelWidget *m_mathsWidget;
};

#endif // MYTABWIDGET_H
