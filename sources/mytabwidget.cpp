#include "mytabwidget.h"

#include "channelwidget.h"
#include "oscillowidget.h"
#include "channel.h"

MYTabWidget::MYTabWidget(OscilloWidget *plotter, QWidget *parent)
    :   QTabWidget(parent), m_plotter(plotter){

}

ChannelWidget *MYTabWidget::channel(int index){
    if ( index >= m_channelsWidgets.count() )
        return nullptr;
    return m_channelsWidgets.at(index);
}

void MYTabWidget::addChannel(Channel *channel){
    int index = m_channelsWidgets.count();
    ChannelWidget *chanWidget = new ChannelWidget(channel, this);
    if ( channel->isMathChannel() ){
        insertTab(channel->index(),chanWidget,tr("Maths"));
        chanWidget->setMathMode(true);
        chanWidget->setChecked(false);
    }else{
        insertTab(channel->index(),chanWidget,tr("Channel ")+ QString::number(index+1));
        m_channelsWidgets.append(chanWidget);
    }
}
