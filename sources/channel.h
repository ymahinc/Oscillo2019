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
    Channel(OscilloWidget *parent, int index, bool mathChannel = false);
    QColor color();
    int currentRes();
    bool isVisible();
    int index();
    QVector<double> yData;
    int couplingMode();
    bool isInverted();
    int dX();
    int dY();
    void setMathChannel(bool mathChannel);
    bool isMathChannel();

signals:
    void resChanged(int res, int index);
    void channelCouplingChanged(int mode, int index);

public slots:
    void updateColor(QColor color);
    void setVisible(bool visible);
    void setRes(int res);
    void onChannelCoulpingChanged(int mode);
    void setInverted(bool inverted);
    void setDX(int dx);
    void setDY(int dY);

private:
    QColor m_color;
    int m_res;
    OscilloWidget *m_plotter;
    QCPAxis *m_axis;
    YResTicker *m_ticker;
    int m_index;
    bool m_isVisible;
    int m_couplingMode;
    bool m_inverted;
    int m_dX;
    int m_dY;
    bool m_mathChannel;
};

#endif // CHANNEL_H
