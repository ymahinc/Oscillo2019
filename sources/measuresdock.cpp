#include "measuresdock.h"

MeasuresDock::MeasuresDock(OscilloWidget *plotter, QWidget *parent, Qt::WindowFlags flags)
    : MYDock (parent,flags){
    m_measuresWidget = new MeasuresDockWidget(plotter,this);
    setWidget(m_measuresWidget);
}
