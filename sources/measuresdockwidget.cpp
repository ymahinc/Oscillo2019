#include "measuresdockwidget.h"
#include "ui_measuresdockwidget.h"

#include <QDebug>
#include "oscillowidget.h"
#include "cursor.h"

MeasuresDockWidget::MeasuresDockWidget(OscilloWidget *plotter, QWidget *parent)
    : QWidget(parent), ui(new Ui::MeasuresDockWidget), m_plotter(plotter){
    ui->setupUi(this);
    for (int i = 0; i < 4; i++){
        ui->channel1Table->setRowHeight(i,15);
        ui->channel2Table->setRowHeight(i,15);
        ui->mathsTable->setRowHeight(i,15);
        if ( i < 2 )
            ui->cursor1Table->setRowHeight(i,15);
        ui->cursor2Table->setRowHeight(i,15);
    }

    connect(m_plotter->vCursor1(),SIGNAL(valueChanged(int)),this,SLOT(updateVCursorsTable()));
    connect(m_plotter->vCursor2(),SIGNAL(valueChanged(int)),this,SLOT(updateVCursorsTable()));
}

MeasuresDockWidget::~MeasuresDockWidget(){
    delete ui;
}

void MeasuresDockWidget::updateVCursorsTable(){
    qDebug() << "iji";
}
