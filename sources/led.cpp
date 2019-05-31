#include "led.h"
#include "ui_led.h"

Led::Led(QWidget *parent)
    : QWidget(parent), ui(new Ui::Led){
    ui->setupUi(this);
    m_on = true;
}

Led::~Led(){
    delete ui;
}

void Led::setOnOff(bool on){
    m_on = on;
    update();
}

void Led::paintEvent(QPaintEvent *event){
    QRadialGradient gr(8,8,8,4,4);
    gr.setColorAt(0, Qt::white);

    gr.setColorAt(1, Qt::black);

    QPainter painter(this);
    QPen p;
    QBrush b;
    b.setStyle(Qt::SolidPattern);
    if ( isEnabled() ){
        p.setColor(Qt::black);
        if ( m_on )
            gr.setColorAt(0.5, Qt::green);
        else {
            gr.setColorAt(0.5, Qt::darkGray);
        }
    }else{
        p.setColor(Qt::darkGray);
        gr.setColorAt(0.5, Qt::gray);
    }

    painter.setPen(p);
    painter.setBrush(gr);

    painter.drawEllipse(event->rect().adjusted(1,1,-1,-1));
}
