#include "maindockwidget.h"
#include "ui_maindockwidget.h"

#include "oscillowidget.h"
#include "cursor.h"
#include "channel.h"

#include <QDebug>

MainDockWidget::MainDockWidget(OscilloWidget *plotter, QWidget *parent) :
    QWidget(parent), ui(new Ui::MainDockWidget),m_plotter(plotter){
    ui->setupUi(this);

    connect(ui->triggerCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(updateTriggerChannel(int)));
    connect(ui->triggerDial,SIGNAL(valueChanged(int)),this,SLOT(onTriggerValueChangedFromDial(int)));
    connect(ui->triggerDial,SIGNAL(mousePressed()),m_plotter->triggerCursor(),SLOT(toggleTempShow()));
    connect(ui->triggerDial,SIGNAL(mouseReleased()),m_plotter->triggerCursor(),SLOT(toggleTempShow()));
    connect(ui->triggerDial,SIGNAL(mouseDoubleClicked()),this,SLOT(onTrigCenter()));
    connect(m_plotter->triggerCursor(),SIGNAL(valueChanged(int)),this,SLOT(onTriggerValueChanged(int)));

    for (int i = m_plotter->graphCount(); i > 0; i--)
        ui->triggerCombo->insertItem(0,tr("Channel ") + QString::number(i));
    ui->triggerCombo->setCurrentIndex(0);

    QSharedPointer<XResTicker> ticker(new XResTicker);
    m_ticker = ticker.data();
    m_plotter->xAxis->setTicker(ticker);

    ticker->setTickStep(30);
    ticker->setScaleStrategy(QCPAxisTickerFixed::ssNone);

    m_plotter->xAxis->setRange(0,299);

    m_plotter->xAxis->setBasePen(QPen(Qt::white, 1));
    m_plotter->xAxis->setTickPen(QPen(Qt::white, 1));
    m_plotter->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_plotter->xAxis->setTickLabelColor(Qt::white);

    m_plotter->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_plotter->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_plotter->xAxis->grid()->setSubGridVisible(true);

    connect(ui->xResDial,SIGNAL(resChanged(int)),this,SLOT(onResChanged(int)));
    connect(m_plotter,SIGNAL(channelResChanged(int,int)),this,SLOT(updateTrigLabel(int,int)));
    connect(m_plotter,SIGNAL(channelColorChanged(QColor,int)),this,SLOT(onColorChange(QColor,int)));
    connect(ui->cursorsCheckBox,SIGNAL(stateChanged(int)),m_plotter,SLOT(toggleCursors(int)));

    updateTrigLabel();
}

void MainDockWidget::onColorChange(QColor color, int index){
    if ( ui->triggerCombo->currentIndex() == index )
        ui->triggerDial->setColor(color);
}

void MainDockWidget::updateTrigLabel(int res, int index){
    if ( index == ui->triggerCombo->currentIndex() )
        updateTrigLabel();
}

void MainDockWidget::updateTrigLabel(){
    if ( ui->triggerCombo->currentIndex() == ui->triggerCombo->count() - 1 ||
         ui->triggerCombo->currentIndex() == ui->triggerCombo->count() - 2 ){
        ui->triggerLabel->setText("----");
        return;
    }

    if ( ! m_plotter->channels().count() )
        return;

    double val = m_plotter->triggerCursor()->value();

    int res = m_plotter->channels().at(ui->triggerCombo->currentIndex())->currentRes();

    QString str;
    switch(res){
    case 0:
        str = formatedString(800*val/255.0-400," mV");
        break;
    case 1:
        str = formatedString(1600*val/255.0-800," mV");
        break;
    case 2:
        str = formatedString(4000*val/255.0-2000," mV");
        break;
    case 3:
        str = formatedString(8*val/255.0-4);
        break;
    case 4:
        str = formatedString(16*val/255.0-8);
        break;
    case 5:
        str = formatedString(40*val/255.0-20);
        break;
    case 6:
        str = formatedString(80*val/255.0-40);
        break;
    case 7:
        str = formatedString(160*val/255.0-80);
        break;
    case 8:
        str = formatedString(400*val/255.0-200);
        break;
    }
    ui->triggerLabel->setText(str);
}

QString MainDockWidget::formatedString(double value, QString unit){
    if ( unit == " V" )
        return QString::number(value,'f',2) + QObject::tr(" V");
    if ( value >= 1000 || value <= -1000 )
        return QString::number(value/1000.0,'f',2) + QObject::tr(" V");
    else
        return QString::number(value,'f',2) + QObject::tr(" mV");
}

void MainDockWidget::onTrigCenter(){
    ui->triggerDial->setValue(128);
    updateTrigLabel();
}

void MainDockWidget::onTriggerValueChanged(int value){
    ui->triggerDial->setValue(value);
    updateTrigLabel();
}

void MainDockWidget::onTriggerValueChangedFromDial(int value){
    m_plotter->triggerCursor()->setPos(value);
    updateTrigLabel();
}

void MainDockWidget::updateTriggerChannel(int index){
    m_plotter->setActiveChannel(index);
    if ( index == ui->triggerCombo->count() - 1 || index == ui->triggerCombo->count() - 2 ){
        m_plotter->triggerCursor()->setVisible(false);
        m_plotter->replot();
        ui->triggerDial->setColor(QColor());
        updateTrigLabel();
    }else{
        m_plotter->triggerCursor()->setVisible(true);
        m_plotter->triggerCursor()->setPen(QPen(m_plotter->graph(index)->pen().color(), 1.0, Qt::DashLine));
        m_plotter->replot();
        ui->triggerDial->setColor(m_plotter->graph(ui->triggerCombo->currentIndex())->pen().color());
        updateTrigLabel();
    }
}

MainDockWidget::~MainDockWidget(){
    delete ui;
}

void MainDockWidget::onResChanged(int newRes){
    m_ticker->setRes(newRes);
    m_plotter->graph(0)->rescaleKeyAxis(true);
    m_plotter->replot();
}
