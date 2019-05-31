#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

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

public slots:
    void setUiEnable(bool enable);

private:
    Ui::MainWindow *ui;

    ChannelsDock *m_channelsDock;
    MainDock *m_mainDock;
    MeasuresDock *m_measuresDock;
    QComboBox *m_portComboBox;    
};

#endif // MAINWINDOW_H
