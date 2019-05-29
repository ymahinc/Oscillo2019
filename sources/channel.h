#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QColor>

#include "oscillowidget.h"
#include "yresticker.h"

class Channel : public QObject
{
    Q_OBJECT

public:
    Channel(OscilloWidget *parent, int index);
    QColor color();
    int currentRes();
    bool isVisible();
    int index();

signals:
    void resChanged(int res, int index);

public slots:
    void updateColor(QColor color);
    void setVisible(bool visible);
    void setRes(int res);

private:
    QColor m_color;
    int m_res;
    OscilloWidget *m_plotter;
    QCPAxis *m_axis;
    YResTicker *m_ticker;
    int m_index;
    bool m_isVisible;
};

#endif // CHANNEL_H
