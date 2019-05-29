#include "channelsdock.h"

ChannelsDock::ChannelsDock(OscilloWidget *plotter, QWidget *parent, Qt::WindowFlags flags)
    : MYDock (parent,flags){
    m_tabWidget = new MYTabWidget(plotter, this);
    setWidget(m_tabWidget);
}

MYTabWidget *ChannelsDock::tabWidget(){
    return m_tabWidget;
}
