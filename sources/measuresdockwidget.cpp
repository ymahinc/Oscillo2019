#include "measuresdockwidget.h"
#include "ui_measuresdockwidget.h"

#include <QDebug>
#include "oscillowidget.h"
#include "cursor.h"
#include "channel.h"

MeasuresDockWidget::MeasuresDockWidget(OscilloWidget *plotter, QWidget *parent)
    : QWidget(parent), ui(new Ui::MeasuresDockWidget), m_plotter(plotter){
    ui->setupUi(this);
    for (int i = 0; i < 4; i++){
        ui->channel1Table->setRowHeight(i,15);
        ui->channel2Table->setRowHeight(i,15);
        ui->mathsTable->setRowHeight(i,15);
        if ( i < 2 )
            ui->cursor1Table->setRowHeight(i,15);
        if ( i < 3 ){
            ui->cursor2Table1->setRowHeight(i,15);
            ui->cursor2Table2->setRowHeight(i,15);
        }
    }

    connect(m_plotter->vCursor1(),SIGNAL(valueChanged(int)),this,SLOT(updateVCursorsTable()));
    connect(m_plotter->vCursor2(),SIGNAL(valueChanged(int)),this,SLOT(updateVCursorsTable()));
    connect(m_plotter,SIGNAL(hResChanged()),this,SLOT(updateVCursorsTable()));

    connect(m_plotter->hCursor1(),SIGNAL(valueChanged(int)),this,SLOT(updateHCursorsTable()));
    connect(m_plotter->hCursor2(),SIGNAL(valueChanged(int)),this,SLOT(updateHCursorsTable()));
    connect(m_plotter,SIGNAL(channelResChanged(int,int)),this,SLOT(updateHCursorsTable()));

    updateVCursorsTable();
    updateHCursorsTable();
}

MeasuresDockWidget::~MeasuresDockWidget(){
    delete ui;
}

void MeasuresDockWidget::updateHCursorsTable(){
    int absVal = qAbs(m_plotter->hCursor2()->value() - m_plotter->hCursor1()->value());

    double v1 = voltValue(absVal,0);
    double v2 = voltValue(absVal,1);
    ui->cursor2Table1->item(0,0)->setText(formatedVoltage(v1));
    ui->cursor2Table2->item(0,0)->setText(formatedVoltage(v2));

    int vmax1, vmin1, vmax2, vmin2;
    if ( m_plotter->hCursor2()->value() > m_plotter->hCursor1()->value() ){
        vmax1 = voltValue(m_plotter->hCursor2()->value()-127.5,0);
        vmin1 = voltValue(m_plotter->hCursor1()->value()-127.5,0);
        vmax2 = voltValue(m_plotter->hCursor2()->value()-127.5,1);
        vmin2 = voltValue(m_plotter->hCursor1()->value()-127.5,1);
    }else{
        vmax1 = voltValue(m_plotter->hCursor1()->value()-127.5,0);
        vmin1 = voltValue(m_plotter->hCursor2()->value()-127.5,0);
        vmax2 = voltValue(m_plotter->hCursor1()->value()-127.5,1);
        vmin2 = voltValue(m_plotter->hCursor2()->value()-127.5,1);
    }

    ui->cursor2Table1->item(1,0)->setText(formatedVoltage(vmax1));
    ui->cursor2Table2->item(1,0)->setText(formatedVoltage(vmax2));
    ui->cursor2Table1->item(2,0)->setText(formatedVoltage(vmin1));
    ui->cursor2Table2->item(2,0)->setText(formatedVoltage(vmin2));
}

QString MeasuresDockWidget::formatedVoltage(double value){
    QString unit = " mV";
    if ( value >= 1000.0 ){
        value = value / 1000.0;
        unit = " V";
    }
    if ( value <= -1000.0 ){
        value = value / 1000.0;
        unit = " V";
    }

    return QString::number(value,'f',2) + unit;
}

double MeasuresDockWidget::voltValue(double absVal, int channel){
    int res = m_plotter->channels().at(channel)->currentRes();
    double val = 0.0;

    switch(res){
        case 0:
        val = 100.0 * absVal / 31.875;
        break;
        case 1:
        val = 200.0 * absVal / 31.875;
        break;
        case 2:
        val = 500.0 * absVal / 31.875;
        break;
        case 3:
        val = 1000.0 * absVal / 31.875;
        break;
        case 4:
        val = 2000.0 * absVal / 31.875;
        break;
        case 5:
        val = 5000.0 * absVal / 31.875;
        break;
        case 6:
        val = 10000.0 * absVal / 31.875;
        break;
        case 7:
        val = 20000.0 * absVal / 31.875;
        break;
        case 8:
        val = 50000.0 * absVal / 31.875;
        break;
    }
    return val;
}

void MeasuresDockWidget::updateVCursorsTable(){
    double period;
    QString unit = " µs";

    int absVal = qAbs(m_plotter->vCursor2()->value() - m_plotter->vCursor1()->value());

    int hRes = m_plotter->hRes();

    switch(hRes){
        case 0:
        period = 1.0 * absVal / 29.9;
        break;
        case 1:
        period = 2.0 * absVal / 29.9;
        break;
        case 2:
        period = 5.0 * absVal / 29.9;
        break;
        case 3:
        period = 10.0 * absVal / 29.9;
        break;
        case 4:
        period = 20.0 * absVal / 29.9;
        break;
        case 5:
        period = 50.0 * absVal / 29.9;
        break;
        case 6:
        period = 100.0 * absVal / 29.9;
        break;
        case 7:
        period = 200.0 * absVal / 29.9;
        break;
        case 8:
        period = 500.0 * absVal / 29.9;
        break;
        case 9:
        period = 1.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 10:
        period = 2.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 11:
        period = 5.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 12:
        period = 10.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 13:
        period = 20.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 14:
        period = 50.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 15:
        period = 100.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 16:
        period = 200.0 * absVal / 29.9;
        unit = " ms";
        break;
        case 17:
        period = 500.0 * absVal / 29.9;
        unit = " ms";
        break;
    }

    ui->cursor1Table->item(0,0)->setText(formatedPeriod(period,unit));
    ui->cursor1Table->item(1,0)->setText(formatedFrequency(period,unit));
}

QString MeasuresDockWidget::formatedPeriod(double value, QString unit){
    while( value >= 1000 ){
        value = value / 1000;
        if ( unit == " ms" )
            unit = " s";
        if ( unit == " µs")
            unit = " ms";
    }
    return QString::number(value,'f',2) + unit;
}

QString MeasuresDockWidget::formatedFrequency(double value, QString unit){
    if ( unit == " ms" )
        value *= 1000;

    double valSec = value / 1000000.0;

    double freq = 1.0/valSec;

    QString freqUnit = " Hz";

    int stop = 0;
    while( freq >= 1000 ){
        stop++;
        freq = freq / 1000.0;
        if ( freqUnit == " kHz")
            freqUnit = " MHz";
        if ( freqUnit == " Hz" )
            freqUnit = " kHz";
        if ( stop == 3 )
            break;
    }

    return QString::number(freq,'f',2) + freqUnit;
}
