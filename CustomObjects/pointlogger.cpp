#include "pointlogger.h"
#include <QDebug>

PointLogger::PointLogger()
{

}

void PointLogger::logPointChanged(const Point2DO& point){
    qDebug() << "A Point (QObject) has changed:" << point;
}

//void PointLogger::logPointChanged(const Point2DM& point) {
//    qDebug() << "A Point (META TYPE) has changed):" << point;
//}
