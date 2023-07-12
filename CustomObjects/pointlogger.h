#ifndef POINTLOGGER_H
#define POINTLOGGER_H

#include <QObject>
#include "point2do.h"
#include "point2dm.h"


class PointLogger: public QObject
{
    Q_OBJECT
public:
    PointLogger();

public slots:
    void logPointChanged(const Point2DO& point);
//    void logPointChanged(const Point2DM& point);
};

#endif // POINTLOGGER_H
