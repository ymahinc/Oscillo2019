#ifndef XRESTICKER_H
#define XRESTICKER_H

#include "qcustomplot.h"

class XResTicker : public QCPAxisTickerFixed
{
public:
    XResTicker();

public slots:
    void setRes(int res);

protected:
    QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision);
    virtual QVector<double> createTickVector(double tickStep, const QCPRange &range);

private:
    QString valueFromRes(int tick);
    int m_res;
};

#endif // XRESTICKER_H
