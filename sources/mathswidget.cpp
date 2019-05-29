#include "mathswidget.h"
#include "ui_mathswidget.h"

MathsWidget::MathsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MathsWidget){
    ui->setupUi(this);
}

MathsWidget::~MathsWidget(){
    delete ui;
}
