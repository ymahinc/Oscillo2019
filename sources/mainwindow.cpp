#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mytabwidget.h"
#include "channel.h"

#include <QSerialPort>
#include <QSerialPortInfo>

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

    m_portComboBox = new QComboBox(this);
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        m_portComboBox->addItem(info.portName());
    ui->connectionToolBar->addWidget(m_portComboBox);

    setUiEnable(false);

    connect(ui->plotter,SIGNAL(newCommunicationMessage(QString)), ui->statusBar,SLOT(showMessage(QString)));
    connect(ui->plotter,SIGNAL(setUiEnabled(bool)), this,SLOT(setUiEnable(bool)));
    connect(m_portComboBox,SIGNAL(currentIndexChanged(QString)),ui->plotter,SLOT(connectHardWare(QString)));
    connect(ui->actionOptions,SIGNAL(triggered()),this,SLOT(onSettingsDLG()));

    ui->plotter->connectHardWare("COM9");
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::onSettingsDLG(){
    SettingsDialog *dlg = new SettingsDialog(this);
    if ( dlg->exec() == QDialog::Accepted ){
        int ls = dlg->interpolation();
        for (int i = 0; i < ui->plotter->channels().count(); i++){
            ui->plotter->graph(i)->setScatterStyle(QCPScatterStyle::ssNone);
            switch(ls){
            case 0:
                ui->plotter->graph(i)->setLineStyle(QCPGraph::lsLine);
                break;
            case 1:
                ui->plotter->graph(i)->setLineStyle(QCPGraph::lsNone);
                ui->plotter->graph(i)->setScatterStyle(QCPScatterStyle::ssDot);
                break;
            case 2:
                ui->plotter->graph(i)->setLineStyle(QCPGraph::lsStepLeft);
                break;
            case 3:
                ui->plotter->graph(i)->setLineStyle(QCPGraph::lsStepRight);
                break;
            case 4:
                ui->plotter->graph(i)->setLineStyle(QCPGraph::lsStepCenter);
                break;
            case 5:
                ui->plotter->graph(i)->setLineStyle(QCPGraph::lsLine);
                break;
            }
        }
        if ( dlg->antiAliasing() ){
            ui->plotter->setNotAntialiasedElements(QCP::aeNone);
            ui->plotter->setAntialiasedElements(QCP::aeAll);
        }else{
            ui->plotter->setAntialiasedElements(QCP::aeNone);
            ui->plotter->setNotAntialiasedElements(QCP::aeAll);
        }
        ui->plotter->replot();
    }
}

void MainWindow::setUiEnable(bool enable){
    ui->plotter->setEnabled(enable);
    m_mainDock->setEnabled(enable);
    m_channelsDock->setEnabled(enable);
    m_measuresDock->setEnabled(enable);
    ui->menuBar->setEnabled(enable);
    ui->mainToolBar->setEnabled(enable);
}
