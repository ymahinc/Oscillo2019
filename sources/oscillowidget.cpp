#include "oscillowidget.h"

#include "cursor.h"
#include "channel.h"

OscilloWidget::OscilloWidget(QWidget *parent)
    : QCustomPlot(parent) {
    m_trigOnFallingEdge = false;
    m_trigMode = 1;

    for (int i = 0; i < 300; i++)
        xVector << i;

    m_comPort = "COM1";

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

    connect(m_triggerCursor,SIGNAL(valueChanged(int)),this,SLOT(updateTrigValue()));

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

    connect(&m_communicationThread,SIGNAL(result(bool,QString,int)),this,SLOT(onCommandResult(bool,QString,int)));
    connect(&m_communicationThread,SIGNAL(newDataAvailable(QByteArray,int)),this,SLOT(updateData(QByteArray,int)));
}

void OscilloWidget::updateData(QByteArray data,int channel){
    for (int i =0; i < 1024; i++ ){
        quint8 val = data.at(i);
        if ( channels().at(channel-1)->isInverted() )
            val = 255 - val;
        channels().at(channel-1)->yData[i] = val + channels().at(channel-1)->dY();//(double)data.at(i)+128;
    }
    int dX = channels().at(channel-1)->dX();
    graph(channel-1)->setData(xVector, channels().at(channel-1)->yData.mid(512-150+dX,300));
    replot();
}

void OscilloWidget::updateTrigMode(int trigMode){
    m_trigMode = trigMode;
    Command cmd { "TRIGMOD\n",QStringList("WAIT\r\n")};
    Command cmd2 { QString("%1\n").arg(trigMode+1),QStringList("OK\r\n")};
    m_queue.clear();
    m_queue.enqueue(cmd);
    m_queue.enqueue(cmd2);
    m_communicationThread.transaction(1000,m_queue,99);
}

void OscilloWidget::updateTrigValue(){
    quint8 val = 255-qRound(m_triggerCursor->value());
    Command cmd { "TRIGV\n",QStringList("WAIT\r\n")};
    Command cmd2 {QString("%1\n").arg(val),QStringList("OK\r\n")};
    m_queue.clear();
    m_queue.enqueue(cmd);
    m_queue.enqueue(cmd2);
    m_communicationThread.transaction(1000,m_queue,99);
}

void OscilloWidget::updateYRes(int res, int channel){
    Command cmd { "YRES\n",QStringList("WAIT\r\n")};
    Command cmd2 {QString("%1\n").arg(channel+1),QStringList("WAIT\r\n")};
    Command cmd3 {QString("%1\n").arg(res+1),QStringList("OK\r\n")};
    m_queue.clear();
    m_queue.enqueue(cmd);
    m_queue.enqueue(cmd2);
    m_queue.enqueue(cmd3);
    m_communicationThread.transaction(1000,m_queue,99);
}

void OscilloWidget::changeTrigMode(bool fallingEdge){
    m_trigOnFallingEdge = fallingEdge;
    Command cmd { "INVTRIG\n",QStringList("WAIT\r\n")};
    Command cmd2 { QString("%1\n").arg(((int)!fallingEdge)+1),QStringList("OK\r\n")};
    m_queue.clear();
    m_queue.enqueue(cmd);
    m_queue.enqueue(cmd2);

    m_communicationThread.transaction(1000,m_queue,99);
}

void OscilloWidget::connectHardWare(QString port){
    m_comPort = port;
    emit newCommunicationMessage(tr("Trying to connect to %1...").arg(m_comPort));
    m_communicationThread.setPort(m_comPort);
    Command cmd { "HELLO\n",QStringList("HELLO\r\n")};
    m_queue.clear();
    m_queue.enqueue(cmd);

    m_communicationThread.transaction(1000,m_queue,1);

    //updateParams();
}

void OscilloWidget::onCommandResult(bool success, QString error, int type){
    if ( !success )
        emit newCommunicationMessage(error);
    switch ( type ){
        case 0:  // error not linked to a command
            connectHardWare(m_comPort);
        break;
        case 1:  // result from connect command
            if ( success ){
                emit newCommunicationMessage(tr("Connected on %1").arg(m_comPort));
                for (int i = 0; i < channels().count(); i++){
                     updateChannelCoupling(channels().at(i)->couplingMode(), i);
                     updateYRes(channels().at(i)->currentRes(), i);
                }
                void updateTrigValue();
                updateTrigMode(m_trigMode);
                updateHRes(m_hRes);
                changeTrigMode(m_trigOnFallingEdge);
            }else{
                connectHardWare(m_comPort);
            }
            emit setUiEnabled(success);
            break;
        case 2:  // Y1Res get value
            if ( success ){
               // m_Y1Res = error.toInt() - 1;
               //ui->YRes1Dial->setCurrentRes(m_Y1Res);
            }
            break;
        case 3:  // Y2Res get value
            if ( success ){
               // m_Y2Res = error.toInt() - 1;
               // ui->YRes2Dial->setCurrentRes(m_Y2Res);
            }
            break;
        case 4:  // XRes get value
            if ( success ){
                //m_XRes = error.toInt() - 1;
                //ui->xResDial->setCurrentRes(m_XRes);
            }
            break;
        case 5:  // TRIGMOD get value
            if ( success ){
               // m_trig = error.toInt() - 1;
               // ui->triggerCombo->setCurrentIndex(m_trig);
            }
            break;
        case 6:  // INVTRIG get value
            if ( success ){
               // m_invTrig = (bool)error.toInt();
                //ui->invertTrigCheckBox->setChecked(m_invTrig);
            }
            break;
        case 99:  // result from command with no user feedback
            break;
    }
}

void OscilloWidget::updateHRes(int res){
    Command cmd { "XRES\n",QStringList("WAIT\r\n")};
    Command cmd2 {QString("%1\n").arg(res+1),QStringList("OK\r\n")};
    m_queue.clear();
    m_queue.enqueue(cmd);
    m_queue.enqueue(cmd2);
    m_communicationThread.transaction(1000,m_queue,99);

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
    connect(this, SIGNAL(channelResChanged(int,int)),this,SLOT(updateYRes(int,int)));
    connect(channel, SIGNAL(channelCouplingChanged(int,int)),this,SLOT(updateChannelCoupling(int,int)));
    m_channels.append(channel);
    setActiveChannel(channel->index());
}

void OscilloWidget::updateChannelCoupling(int mode, int channel){
    QString strMode = "DC";
    switch(mode){
    case 0:
        strMode = "DC";
        break;
    case 1:
        strMode = "AC";
        break;
    case 2:
        strMode = "GND";
    }
    Command cmd {"COUP\n",QStringList("WAIT\r\n")};
    Command cmd2 {QString("%1\n").arg(channel+1),QStringList("WAIT\r\n")};
    Command cmd3 {QString("%1\n").arg(strMode),QStringList("OK\r\n")};
    m_queue.clear();
    m_queue.enqueue(cmd);
    m_queue.enqueue(cmd2);
    m_queue.enqueue(cmd3);
    m_communicationThread.transaction(1000,m_queue,99);
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
