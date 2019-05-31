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
#include "settingsdialog.h"

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

private slots:
    void onSettingsDLG();

private:
    Ui::MainWindow *ui;

    ChannelsDock *m_channelsDock;
    MainDock *m_mainDock;
    MeasuresDock *m_measuresDock;
    QComboBox *m_portComboBox;    
    bool m_unefois = false;
};

#endif // MAINWINDOW_H
