#include "mytabwidget.h"

#include "channelwidget.h"
#include "oscillowidget.h"
#include "mathswidget.h"
#include "channel.h"

MYTabWidget::MYTabWidget(OscilloWidget *plotter, QWidget *parent)
    :   QTabWidget(parent), m_plotter(plotter){
    m_mathsWidget = new MathsWidget(this);
    addTab(m_mathsWidget,tr("Maths"));
}

ChannelWidget *MYTabWidget::channel(int index){
    if ( index >= m_channelsWidgets.count() )
        return nullptr;
    return m_channelsWidgets.at(index);
}

void MYTabWidget::addChannel(Channel *channel){
    int index = m_channelsWidgets.count();
    ChannelWidget *chanWidget = new ChannelWidget(channel, this);
    insertTab(channel->index(),chanWidget,tr("Channel ")+ QString::number(index+1));
    m_channelsWidgets.append(chanWidget);
}
