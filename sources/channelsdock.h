#ifndef CHANNELSDOCK_H
#define CHANNELSDOCK_H

#include "mydock.h"
#include "mytabwidget.h"
class OscilloWidget;

class ChannelsDock : public MYDock
{
    Q_OBJECT

public:
    ChannelsDock(OscilloWidget *plotter, QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    MYTabWidget *tabWidget();

private:
    MYTabWidget *m_tabWidget;
};

#endif // CHANNELSDOCK_H
