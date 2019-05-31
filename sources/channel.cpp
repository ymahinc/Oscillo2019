#include "channel.h"

#include "cursor.h"

Channel::Channel(OscilloWidget *parent, int index)
    : QObject(parent), m_plotter(parent), m_index(index){

    m_couplingMode = 0;

    for (int i =0; i < 1024; i++)
        yData << 0;

    QVector<double> x;
    for (int i = 0; i < 300; i++)
        x << i;

    m_color = Qt::white;
    m_res = 0;

    int axisIndex = m_index/2;

    QSharedPointer<YResTicker> axisTicker(new YResTicker);
    m_ticker=axisTicker.data();

    if ( m_index % 2 )
        m_axis = m_plotter->axisRect()->axis(QCPAxis::atRight, axisIndex);
    else
        m_axis = m_plotter->axisRect()->axis(QCPAxis::atLeft, axisIndex);

    m_axis->setRange(0,255);
    m_axis->setTicker(axisTicker);

    if ( m_index == 0 ){
        m_axis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
        m_axis->grid()->setSubGridVisible(true);
    }

    m_plotter->addGraph();
    m_plotter->graph(m_index)->setData(x, yData.mid(512-150,300));

    updateColor(m_color);
}

void Channel::setInverted(bool inverted){
    m_inverted = inverted;
}

bool Channel::isInverted(){
    return m_inverted;
}

void Channel::setDX(int dx){
    m_dX = dx;
}

int Channel::dX(){
    return m_dX;
}

void Channel::setDY(int dY){
    m_dY = dY;
}

int Channel::dY(){
    return m_dY;
}

int Channel::Channel::couplingMode(){
    return m_couplingMode;
}

void Channel::onChannelCoulpingChanged(int mode){
    m_couplingMode = mode;
    emit channelCouplingChanged(mode,m_index);
}

int Channel::index(){
    return m_index;
}

void Channel::updateColor(QColor color){
    m_color = color;
    m_plotter->graph(m_index)->setPen(QPen(color));
    m_axis->setBasePen(QPen(color, 1));
    m_axis->setTickPen(QPen(color, 1));
    m_axis->setSubTickPen(QPen(color, 1));
    m_axis->setTickLabelColor(color);
    if ( m_plotter->currentChannelTrigger() == m_index )
        m_plotter->triggerCursor()->setPen(QPen(color, 1.0, Qt::DashLine));
    m_plotter->replot();
    emit m_plotter->channelColorChanged(color, m_index);
}

QColor Channel::color(){
    return m_color;
}

void Channel::setRes(int res){
    m_res = res;
    m_ticker->setRes(m_res);
    m_plotter->graph(m_index)->rescaleValueAxis(true,true);
    m_plotter->replot();
    emit m_plotter->channelResChanged(res, m_index);
}

int Channel::currentRes(){
    return m_res;
}

void Channel::setVisible(bool visible){
    m_plotter->graph(m_index)->setVisible(visible);
    m_plotter->replot();
    m_isVisible = visible;
}

bool Channel::isVisible(){
    return m_isVisible;
}
