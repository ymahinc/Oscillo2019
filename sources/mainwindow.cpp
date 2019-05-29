#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mytabwidget.h"
#include "channel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    m_channelsDock = new ChannelsDock(ui->plotter, this);
    m_channelsDock->setWindowTitle(tr("Channels"));
    m_channelsDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,m_channelsDock);

    Channel *chan1 = new Channel(ui->plotter,0);
    chan1->updateColor(Qt::yellow);
    ui->plotter->addChannel(chan1);
    m_channelsDock->tabWidget()->addChannel(chan1);

    Channel *chan2 = new Channel(ui->plotter,1);
    chan2->updateColor(Qt::blue);
    ui->plotter->addChannel(chan2);
    m_channelsDock->tabWidget()->addChannel(chan2);

    m_channelsDock->tabWidget()->setCurrentIndex(0);

    m_mainDock = new MainDock(ui->plotter, this);
    m_mainDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,m_mainDock);

    m_measuresDock = new MeasuresDock(ui->plotter, this);
    m_measuresDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::BottomDockWidgetArea,m_measuresDock);
}

MainWindow::~MainWindow(){
    delete ui;
}
