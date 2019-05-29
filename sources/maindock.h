#ifndef MAINDOCK_H
#define MAINDOCK_H

#include "mydock.h"
#include "maindockwidget.h"

class OscilloWidget;

class MainDock : public MYDock
{
    Q_OBJECT

public:
    MainDock(OscilloWidget *plotter, QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
    MainDockWidget *mainWidget();

private:
    MainDockWidget *m_mainWidget;
};


#endif // MAINDOCK_H
