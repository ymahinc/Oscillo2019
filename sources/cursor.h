#ifndef CURSOR_H
#define CURSOR_H

#include "oscillowidget.h"

class Cursor : public QCPItemLine
{
    Q_OBJECT

public:
    enum Orientation{Horizontal, Vertical};

    Cursor(OscilloWidget *plotter, Orientation orientation = Vertical);
    Orientation orientation();
    void setOrientation(Orientation orientation);
    bool autoHide();
    void setAutoHide(bool autoHide);
    void setPos(double pos);
    double value();

public slots:
    void toggleTempShow();

signals:
    void valueChanged(int value);

protected:
    virtual void mousePressEvent(QMouseEvent *event, const QVariant &details);
    virtual void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos);
    virtual void mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details);

private:
    OscilloWidget *m_plotter;
    Orientation m_orientation;
    bool m_autoHide;
    bool m_tempShow;
};

#endif // CURSOR_H
