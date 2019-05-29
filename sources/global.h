#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QStringList>

typedef struct{
    QString command;
    QStringList expectedReplies;
}Command;
/*
typedef struct{
    QString port;
    bool antiAliasing;
    QColor col1;
    QColor col2;
    OscilloChart::Interpolation interpolation;
}Settings;*/

#endif // GLOBAL_H
