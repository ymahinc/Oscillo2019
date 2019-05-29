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

private:
    Ui::MeasuresDockWidget *ui;
    OscilloWidget *m_plotter;
};

#endif // MEASURESDOCKWIDGET_H
