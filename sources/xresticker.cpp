#include "xresticker.h"

#include <QDebug>

XResTicker::XResTicker()
    : QCPAxisTickerFixed(){
    m_res = 0;
}

void XResTicker::setRes(int res){
    m_res = res;
}

QString XResTicker::getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision){
    return valueFromRes((int)tick);
}

QVector<double> XResTicker::createTickVector(double tickStep, const QCPRange &range){
    QVector<double> vect;
    vect << 0 << 30 << 60 << 90 << 120 << 150 << 180 << 210 << 240 << 270 << 299;
    return vect;
}

QString XResTicker::valueFromRes(int tick){
    if ( tick == 299 ) tick = 300;
    switch(m_res){
    case 0:
        return QString::number(tick/30-5) + QObject::tr(" µs");
        break;
    case 1:
        return QString::number(tick/30 *2-10) + QObject::tr(" µs");
        break;
    case 2:
        return QString::number(tick/30 *5-25) + QObject::tr(" µs");
        break;
    case 3:
        return QString::number(tick/30 *10-50) + QObject::tr(" µs");
        break;
    case 4:
        return QString::number(tick/30 *20-100) + QObject::tr(" µs");
        break;
    case 5:
        return QString::number(tick/30 *50-250) + QObject::tr(" µs");
        break;
    case 6:
        return QString::number(tick/30 *100-500) + QObject::tr(" µs");
        break;
    case 7:{
        int tmpTick = tick/30 *200-1000;
        if ( tmpTick >= 1000 || tmpTick <= -1000 )
            return QString::number(tmpTick/1000.0) + QObject::tr(" ms");
        else
            return QString::number(tmpTick) + QObject::tr(" µs");
        break;}
    case 8:{
        int tmpTick = tick/30 *500-2500;
        if ( tmpTick >= 1000 || tmpTick <= -1000 )
            return QString::number(tmpTick/1000.0) + QObject::tr(" ms");
        else
            return QString::number(tmpTick) + QObject::tr(" µs");
        break;}
    case 9:
        return QString::number(tick/30 *1-5) + QObject::tr(" ms");
        break;
    case 10:
        return QString::number(tick/30 *2-10) + QObject::tr(" ms");
        break;
    case 11:
        return QString::number(tick/30 *5-25) + QObject::tr(" ms");
        break;
    case 12:
        return QString::number(tick/30 *10-50) + QObject::tr(" ms");
        break;
    case 13:
        return QString::number(tick/30 *20-100) + QObject::tr(" ms");
        break;
    case 14:
        return QString::number(tick/30 *50-250) + QObject::tr(" ms");
        break;
    case 15:
        return QString::number(tick/30 *100-500) + QObject::tr(" ms");
        break;
    case 16:{
        int tmpTick = tick/30 *200-1000;
        if ( tmpTick >= 1000 || tmpTick <= -1000 )
            return QString::number(tmpTick/1000.0) + QObject::tr(" s");
        else
            return QString::number(tmpTick) + QObject::tr(" ms");
        break;}
    case 17:{
        int tmpTick = tick/30 *500-2500;
        if ( tmpTick >= 1000 || tmpTick <= -1000 )
            return QString::number(tmpTick/1000.0) + QObject::tr(" s");
        else
            return QString::number(tmpTick) + QObject::tr(" ms");
        break;}
    }
    return QString::number(tick);
}

