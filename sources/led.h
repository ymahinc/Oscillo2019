#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class Led;
}

class Led : public QWidget
{
    Q_OBJECT

public:
    explicit Led(QWidget *parent = nullptr);
    ~Led();

public slots:
    void setOnOff(bool on);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::Led *ui;
    bool m_on;
};

#endif // LED_H
