#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>

#include "portthread.h"
#include "channelsdock.h"
#include "maindock.h"
#include "measuresdock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    PortThread m_communicationThread;
    ChannelsDock *m_channelsDock;
    MainDock *m_mainDock;
    MeasuresDock *m_measuresDock;
};

#endif // MAINWINDOW_H
