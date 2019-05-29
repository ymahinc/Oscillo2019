#ifndef YRESTICKER_H
#define YRESTICKER_H

#include "qcustomplot.h"

class YResTicker : public QCPAxisTickerFixed
{
public:
    YResTicker();

public slots:
    void setRes(int res);

protected:
    QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision);
    virtual QVector<double> createTickVector(double tickStep, const QCPRange &range);

private:
    QString valueFromRes(int tick);
    int m_res;
};

#endif // YRESTICKER_H
