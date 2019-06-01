#ifndef OSCILLOWIDGET_H
#define OSCILLOWIDGET_H

#include <QVector>
#include <QColor>

#include "qcustomplot.h"
#include "xresticker.h"
#include "portthread.h"

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
    void newCommunicationMessage(QString message);
    void setUiEnabled(bool enable);
    void signalChanged(int vmin, int vmax, int channel);
    void newTrigStateAvailable(bool);

public slots:
    void connectHardWare(QString port);
    void toggleCursors(int toggle);
    void updateHRes(int res);
    void changeTrigMode(bool fallingEdge);
    void updateChannelCoupling(int mode, int channel);
    void updateYRes(int res, int channel);
    void updateTrigValue();
    void updateTrigMode(int trigMode);
    void updateData(QByteArray data,int channel);
    void setMathChannelColor(QColor color);
    void toggleMathAxes(bool toggle);
    void toggleAxes(bool toggle);

private slots:
    void onCommandResult(bool success, QString error, int type);

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
    QQueue<Command> m_queue;
    PortThread m_communicationThread;
    QString m_comPort;
    QVector<double> xVector;
    bool m_trigOnFallingEdge;
    int m_trigMode;
    QCPAxis *m_mathYAxis;
    QCPAxis *m_mathXAxis;
    bool m_showAxes;
    bool m_mathAxesVisibles;
};

#endif // OSCILLOWIDGET_H
