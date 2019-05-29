#ifndef MEASURESDOCK_H
#define MEASURESDOCK_H

#include "mydock.h"
#include "measuresdockwidget.h"

class OscilloWidget;

class MeasuresDock : public MYDock
{
    Q_OBJECT

public:
    MeasuresDock(OscilloWidget *plotter, QWidget *parent = nullptr, Qt::WindowFlags flags = 0);

private:
    MeasuresDockWidget *m_measuresWidget;
};

#endif // MEASURESDOCK_H
