#ifndef OSCILLOWIDGET_H
#define OSCILLOWIDGET_H

#include <QVector>
#include <QColor>
#include "qcustomplot.h"
#include "xresticker.h"
class Cursor;
class Channel;

class OscilloWidget : public QCustomPlot{

    Q_OBJECT

public:
    OscilloWidget(QWidget *parent = 0);
    Cursor *triggerCursor();
    Cursor *hCursor1();
    Cursor *hCursor2();
    Cursor *vCursor1();
    Cursor *vCursor2();
    int currentChannelTrigger();
    void setCurrentChannelTrigger(int channel);
    void addChannel(Channel *channel);
    int activeChannel();
    void setActiveChannel(int channel);
    QVector<Channel *> channels();
    int hRes();

signals:
    void channelResChanged(int res, int index);
    void activeChannelChanged(int channel);
    void channelColorChanged(QColor color, int index);
    void hResChanged();

public slots:
    void toggleCursors(int toggle);
    void updateHRes(int res);

private:
    Cursor *m_triggerCursor;
    Cursor *m_vCursor1;
    Cursor *m_vCursor2;
    Cursor *m_hCursor1;
    Cursor *m_hCursor2;
    int m_channelTrigger;
    QCPItemStraightLine  *m_horizontalZeroLine;
    QCPItemStraightLine  *m_verticalZeroLine;
    QVector<Channel *> m_channels;
    int m_activeChannel;
    XResTicker *m_ticker;
    int m_hRes;
};

#endif // OSCILLOWIDGET_H
