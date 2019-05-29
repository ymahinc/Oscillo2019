#include "oscillowidget.h"

#include "cursor.h"
#include "channel.h"

OscilloWidget::OscilloWidget(QWidget *parent)
    : QCustomPlot(parent) {

    m_hRes = 0;

    setBackground(QBrush(Qt::black));

    yAxis2->setVisible(true);

    m_channelTrigger = 0;
    m_activeChannel = 0;

    QSharedPointer<XResTicker> ticker(new XResTicker);
    m_ticker = ticker.data();
    xAxis->setTicker(ticker);

    ticker->setScaleStrategy(QCPAxisTickerFixed::ssNone);

    xAxis->setRange(0,299);

    xAxis->setBasePen(QPen(Qt::white, 1));
    xAxis->setTickPen(QPen(Qt::white, 1));
    xAxis->setSubTickPen(QPen(Qt::white, 1));
    xAxis->setTickLabelColor(Qt::white);

    xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    xAxis->grid()->setSubGridVisible(true);

    m_horizontalZeroLine = new QCPItemStraightLine (this);
    m_horizontalZeroLine->setPen(QPen(Qt::white));
    m_horizontalZeroLine->point1->setCoords(0,128);
    m_horizontalZeroLine->point2->setCoords(300,128);
    m_horizontalZeroLine->setLayer("grid");

    m_verticalZeroLine = new QCPItemStraightLine (this);
    m_verticalZeroLine->setPen(QPen(Qt::white));
    m_verticalZeroLine->point1->setCoords(150,0);
    m_verticalZeroLine->point2->setCoords(150,255);
    m_verticalZeroLine->setLayer("grid");

    addLayer("CursorsLayer");

    m_triggerCursor = new Cursor(this,Cursor::Horizontal);
    m_triggerCursor->setPos(128);
    m_triggerCursor->setPen(QPen(Qt::white, 1.0, Qt::DashLine));
    m_triggerCursor->setAutoHide(true);
    m_triggerCursor->setLayer("CursorsLayer");

    m_vCursor1 = new Cursor(this);
    m_vCursor1->setPos(100);
    m_vCursor1->setPen(QPen(Qt::lightGray, 1.0, Qt::DashLine));
    m_vCursor1->setLayer("CursorsLayer");

    m_vCursor2 = new Cursor(this);
    m_vCursor2->setPos(200);
    m_vCursor2->setPen(QPen(Qt::lightGray, 1.0, Qt::DashLine));
    m_vCursor2->setLayer("CursorsLayer");

    m_hCursor1 = new Cursor(this,Cursor::Horizontal);
    m_hCursor1->setPos(64);
    m_hCursor1->setPen(QPen(Qt::lightGray, 1.0, Qt::DashLine));
    m_hCursor1->setLayer("CursorsLayer");

    m_hCursor2 = new Cursor(this,Cursor::Horizontal);
    m_hCursor2->setPos(196);
    m_hCursor2->setPen(QPen(Qt::lightGray, 1.0, Qt::DashLine));
    m_hCursor2->setLayer("CursorsLayer");
}

void OscilloWidget::updateHRes(int res){
    m_hRes = res;
    m_ticker->setRes(m_hRes);
    graph(0)->rescaleKeyAxis(true);
    replot();
    emit hResChanged();
}

int OscilloWidget::hRes(){
    return m_hRes;
}

int OscilloWidget::activeChannel(){
    return m_activeChannel;
}

void OscilloWidget::setActiveChannel(int channel){
    m_activeChannel = channel;
    emit activeChannelChanged(m_activeChannel);
}

void OscilloWidget::addChannel(Channel *channel){
    connect(channel, SIGNAL(resChanged(int,int)),this,SIGNAL(channelResChanged(int,int)));
    m_channels.append(channel);
    setActiveChannel(channel->index());
}

QVector<Channel *> OscilloWidget::channels(){
    return m_channels;
}

Cursor *OscilloWidget::triggerCursor(){
    return m_triggerCursor;
}

Cursor *OscilloWidget::hCursor1(){
    return m_hCursor1;
}

Cursor *OscilloWidget::hCursor2(){
    return m_hCursor2;
}

Cursor *OscilloWidget::vCursor1(){
    return m_vCursor1;
}

Cursor *OscilloWidget::vCursor2(){
    return m_vCursor2;
}

int OscilloWidget::currentChannelTrigger(){
    return m_channelTrigger;
}

void OscilloWidget::setCurrentChannelTrigger(int channel){
    m_channelTrigger = channel;
}

void OscilloWidget::toggleCursors(int toggle){
    m_vCursor1->setVisible(toggle);
    m_vCursor2->setVisible(toggle);
    m_hCursor1->setVisible(toggle);
    m_hCursor2->setVisible(toggle);
    replot();
}
