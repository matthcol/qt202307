#include <QCoreApplication>
#include <QList>
#include <QVariant>
#include "point2d.h"
#include "point2dm.h"

void playWithPoints(){
    Point2D ptA("A", 4.5, 2.25);
    Point2D ptB("B");
    QList<Point2D> points {ptA, ptB};
    for (const Point2D& pt: points) {
        qDebug() << pt.name() << pt.x() << pt.y();
        // qDebug() << pt; // no overload of << with Point2D&
        // pt.setX(10.0); // setter is forbidden with a const point
    }
    for (Point2D& pt: points) {
        pt.setName(pt.name().toString().toLower());
        pt.setX(10.0);
        pt.setY(pt.y() + 1.0);
        qDebug() << pt.name() << pt.x() << pt.y();
    }
    // Following is not possible according to official documentation
    QVariant variant = QVariant::fromValue(ptA);
    qDebug() << variant << variant.isValid();
    Point2D ptV = variant.value<Point2D>();
    qDebug();
}

void playWithPointsMeta(){
    Point2DM ptA("A", 4.5, 2.25);
    Point2DM ptB("B");
    QList<Point2DM> points {ptA, ptB};
    for (const Point2DM& pt: points) {
        qDebug() << pt.name() << pt.x() << pt.y();
        // qDebug() << pt; // no overload of << with Point2D&
        // pt.setX(10.0); // setter is forbidden with a const point
    }
    for (Point2DM& pt: points) {
        pt.setName(pt.name().toString().toLower());
        pt.setX(10.0);
        pt.setY(pt.y() + 1.0);
        qDebug() << pt.name() << pt.x() << pt.y();
    }
    // following lines OK with a Q_DECLARE_META_TYPE
    QVariant variant = QVariant::fromValue(ptA);
    qDebug() << variant << variant.isValid();
    Point2DM ptV = variant.value<Point2DM>();
    qDebug() << ptV.name() << ptV.x() << ptV.y();
    qDebug();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<Point2DM>();
    playWithPoints();
    playWithPointsMeta();
    //    return a.exec();
}
