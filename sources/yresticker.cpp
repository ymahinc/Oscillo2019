#include "yresticker.h"
#include <QDebug>

YResTicker::YResTicker()
    : QCPAxisTickerFixed(){
    m_res = 0;

    //setTickCount(9);
    //setTickStep(255.0/9.0);
   // setScaleStrategy(QCPAxisTickerFixed::ssNone);
}

void YResTicker::setRes(int res){
    m_res = res;
}

QVector<double> YResTicker::createTickVector(double tickStep, const QCPRange &range){
    QVector<double> vect;
    vect << 0 << 32 << 64 << 96 << 128 << 160 << 192 << 224 << 255;
    return vect;
}

QString YResTicker::getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision){
    return valueFromRes((int)tick);
}

QString YResTicker::valueFromRes(int tick){
    if ( tick == 255 ) tick = 256;
    switch(m_res){
    case 0:
        return QString::number(tick/32*100 - 400) + QObject::tr(" mV");
        break;
    case 1:
        return QString::number(tick/32*200 - 800) + QObject::tr(" mV");
        break;
    case 2:{
        int tmpTick = tick/32 * 500 - 2000;
        if ( tmpTick >= 1000 || tmpTick <= -1000 )
            return QString::number(tmpTick/1000.0) + QObject::tr(" V");
        else
            return QString::number(tmpTick) + QObject::tr(" mV");
        break;}
    case 3:
        return QString::number(tick/32*1 - 4) + QObject::tr(" V");
        break;
    case 4:
        return QString::number(tick/32*2 - 8) + QObject::tr(" V");
        break;
    case 5:
        return QString::number(tick/32*5 - 20) + QObject::tr(" V");
        break;
    case 6:
        return QString::number(tick/32*10 - 40) + QObject::tr(" V");
        break;
    case 7:
        return QString::number(tick/32*20 - 80) + QObject::tr(" V");
        break;
    case 8:
        return QString::number(tick/32*50 - 200) + QObject::tr(" V");
        break;
    }
}
