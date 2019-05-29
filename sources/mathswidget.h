#ifndef MATHSWIDGET_H
#define MATHSWIDGET_H

#include <QWidget>

namespace Ui {
class MathsWidget;
}

class MathsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MathsWidget(QWidget *parent = nullptr);
    ~MathsWidget();

private:
    Ui::MathsWidget *ui;
};

#endif // MATHSWIDGET_H
