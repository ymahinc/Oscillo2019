#ifndef MAINDOCKWIDGET_H
#define MAINDOCKWIDGET_H

#include <QWidget>

class OscilloWidget;

namespace Ui {
class MainDockWidget;
}

class MainDockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainDockWidget(OscilloWidget *plotter,  QWidget *parent = nullptr);
    ~MainDockWidget();

private slots:
    void updateTriggerChannel(int index);
    void onTriggerValueChanged(int value);
    void onTriggerValueChangedFromDial(int value);
    void onTrigCenter();
    void updateTrigLabel(int res, int index);
    void updateTrigLabel();
    void onColorChange(QColor color, int index);

private:
    Ui::MainDockWidget *ui;
    OscilloWidget *m_plotter;

    QString formatedString(double value, QString unit = " V");
};

#endif // MAINDOCKWIDGET_H
