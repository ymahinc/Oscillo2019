#include "maindock.h"

MainDock::MainDock(OscilloWidget *plotter, QWidget *parent, Qt::WindowFlags flags)
    : MYDock (parent,flags){
    m_mainWidget = new MainDockWidget(plotter,this);
    setWidget(m_mainWidget);
}

MainDockWidget *MainDock::mainWidget(){
    return m_mainWidget;
}

