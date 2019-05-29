#include "cursor.h"

#include <QDebug>

Cursor::Cursor(OscilloWidget *plotter, Cursor::Orientation orientation)
    : QCPItemLine (plotter), m_plotter(plotter), m_orientation(orientation){
    m_autoHide = false;
    m_tempShow = false;

    setPen(QPen(Qt::white, 1.0, Qt::DashLine));
    setTail(QCPLineEnding::esSquare);
    setClipToAxisRect(false);
}

double Cursor::value(){
    if ( m_orientation == Horizontal )
        return start->coords().y();
    else
        return start->coords().x();
}

void Cursor::toggleTempShow(){
   m_tempShow = !m_tempShow;
   if ( m_autoHide && !m_tempShow ){
        if ( m_orientation == Horizontal )
            end->setCoords(0,start->coords().y());
        else
            end->setCoords(start->coords().x(),255);
   }else{
        if ( m_orientation == Horizontal )
            end->setCoords(299,start->coords().y());
        else
            end->setCoords(start->coords().x(),0);
   }
   m_plotter->replot();
}

bool Cursor::autoHide(){
    return m_autoHide;
}

void Cursor::setAutoHide(bool autoHide){
    m_autoHide = autoHide;
    if ( m_autoHide ){
        if ( m_orientation == Horizontal )
            end->setCoords(0,start->coords().y());
        else
            end->setCoords(start->coords().x(),255);
    }else{
        if ( m_orientation == Horizontal )
            end->setCoords(299,start->coords().y());
        else
            end->setCoords(start->coords().x(),0);
    }
    m_plotter->replot();
}

Cursor::Orientation Cursor::orientation(){
    return m_orientation;
}

void Cursor::setOrientation(Cursor::Orientation orientation){
    m_orientation = orientation;
    m_plotter->replot();
}

void Cursor:: mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details){
    if ( m_orientation == Horizontal ){
        setPos(128);
        emit valueChanged(128);
    }else{
        setPos(150);
        emit valueChanged(150);
    }
    m_plotter->replot();
}

void Cursor::mousePressEvent(QMouseEvent *event, const QVariant &details){
    if ( m_autoHide ){
        m_tempShow = true;
        if ( m_orientation == Horizontal )
            end->setCoords(299,start->coords().y());
        else
            end->setCoords(start->coords().x(),0);
        m_plotter->replot();
    }
}

void Cursor::mouseMoveEvent(QMouseEvent *event, const QPointF &startPos){
    if ( m_orientation == Horizontal ) {
        double endX = 0;

        if ( m_autoHide ){
            if ( m_tempShow )
                endX = 299;
        }else{
            endX = 299;
        }

        double pos = m_plotter->yAxis->pixelToCoord(event->pos().y());
        if ( pos < 0 ) pos = 0;
        if ( pos > 255 ) pos = 255;
        start->setCoords(-1.5,pos);
        end->setCoords(endX,pos);
        m_plotter->replot();
        emit valueChanged(qRound(pos));
    }else{
        double endY = 255;

        if ( m_autoHide ){
            if ( m_tempShow )
                endY = 0;
        }else{
            endY = 0;
        }

        double pos = m_plotter->xAxis->pixelToCoord(event->pos().x());

        if ( pos < 0 ) pos = 0;
        if ( pos > 299 ) pos = 299;
        start->setCoords(pos, 256.5);
        end->setCoords(pos, endY);
        m_plotter->replot();
        emit valueChanged(qRound(pos));
    }
}

void Cursor::setPos(double pos){
    if ( m_orientation == Horizontal ) {
        double endX = 0;
        if ( m_autoHide ){
            if ( m_tempShow )
                endX = 299;
        }else{
            endX = 299;
        }
        start->setCoords(-1.5,pos);
        end->setCoords(endX,pos);
        m_plotter->replot();
    }else{
        double endY = 255;
        if ( m_autoHide ){
            if ( m_tempShow )
                endY = 0;
        }else{
            endY = 0;
        }
        start->setCoords(pos,256.5);
        end->setCoords(pos,endY);
        m_plotter->replot();
    }
}

void Cursor::mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos){
    if ( m_autoHide ){
        m_tempShow = false;
        if ( m_orientation == Horizontal )
            end->setCoords(0,start->coords().y());
        else
            end->setCoords(start->coords().x(),255);
        m_plotter->replot();
    }
}
