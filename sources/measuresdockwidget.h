#ifndef MEASURESDOCKWIDGET_H
#define MEASURESDOCKWIDGET_H

#include <QWidget>

class OscilloWidget;

namespace Ui {
class MeasuresDockWidget;
}

class MeasuresDockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeasuresDockWidget(OscilloWidget *plotter, QWidget *parent = nullptr);
    ~MeasuresDockWidget();

private slots:
    void updateVCursorsTable();
    void updateHCursorsTable();
    void onsignalChanged(int vmin, int vmax, int channel);

private:
    Ui::MeasuresDockWidget *ui;
    OscilloWidget *m_plotter;

    QString formatedPeriod(double value, QString unit);
    QString formatedFrequency(double value, QString unit);
    QString formatedVoltage(double value);
    double voltValue(double absVal, int channel);
};

#endif // MEASURESDOCKWIDGET_H
