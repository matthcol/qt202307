// include QT
#include <QCoreApplication>
#include <QList>
#include <QVariant>
#include <QObject>
#include <QThread>

// include C++ standard
#include <utility>

// include project
#include "point2d.h"
#include "point2dm.h"
#include "point2do.h"
#include "pointlogger.h"

void logNameChanged(QStringView name) {
    qDebug() << "logNameChanged:" << name;
}

void logCoordChanged(const QString& coordName, qreal value) {
    qDebug() << coordName << "has changed:" << value;
}

void playWithPoints(){
    qDebug().noquote() << "*** playWithPoints ***";
    Point2D ptA("A", 4.5, 2.25);
    Point2D ptB("B");
    QList<Point2D> points {ptA, ptB};
    for (const Point2D& pt: points) {
        qDebug() << pt.name() << pt.x() << pt.y();
        qDebug() << pt; // no overload of << with Point2D&
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
    qDebug().noquote() << "*** playWithPointsMeta ***";
    Point2DM ptA("A", 4.5, 2.25);
    Point2DM ptB("B");
    QList<Point2DM> points {ptA, ptB};
    for (const Point2DM& pt: points) {
        qDebug() << pt.name() << pt.x() << pt.y();
        qDebug() << "Point:" << pt << "#"; // no overload of << with Point2D&
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

void playWithPointsObject(){
    qDebug().noquote() << "*** playWithPointsObject ***";
    Point2DO ptA("A", 4.5, 2.25);
    Point2DO ptB("B");

    // example of a list containing directly Point2DO
    // use move constructor
//    QList<Point2DO> points2{ Point2DO("A"), Point2DO("B")};
//    points2.append(ptA);
//    points2.append( Point2DO("C"));

    // example of a list containing pointers Point2DO
    // use copy (of pointer)
    QList<Point2DO*> points {&ptA, &ptB};
    for (const Point2DO* pt: points) {
        qDebug() << pt->name() << pt->x() << pt->y();
        qDebug() << "Point:" << *pt << "#"; // no overload of << with Point2D&
        // pt.setX(10.0); // setter is forbidden with a const point
        QObject::connect(
            pt,
            &Point2DO::nameChanged,
            [](QStringView name) {
                qDebug() << "(lambda) Name has changed:" << name;
            }
        );
        QObject::connect(
            pt,
            &Point2DO::nameChanged,
            &logNameChanged
        );
        QObject::connect(
            pt,
            &Point2DO::xChanged,
            [](qreal value) { logCoordChanged("x", value); }
        );
        QObject::connect(
            pt,
            &Point2DO::yChanged,
            [](qreal value) { logCoordChanged("y", value); }
        );
    }
    for (Point2DO* pt: points) {
        pt->setName(pt->name().toString().toLower());
        pt->setX(10.0);
        pt->setY(pt->y() + 1.0);
        qDebug() << pt->name() << pt->x() << pt->y();
    }
    // following lines OK with a Q_DECLARE_META_TYPE
    QVariant variant = QVariant::fromValue(&ptA);
    qDebug() << variant << variant.isValid();
    Point2DO* ptV = variant.value<Point2DO*>();
    qDebug() << ptV->name() << ptV->x() << ptV->y();
    qDebug();
}

void playConnectSignalSlot2points(){
    qDebug().noquote() << "*** playConnectSignalSlot2points ***";
    Point2DO ptA("A", 4.5, 2.25);
    Point2DO ptMirror(ptA.name().toString(), ptA.y(), ptA.x());
    QObject::connect(
        &ptA,
        &Point2DO::xChanged,
        &ptMirror,
        &Point2DO::setY
    );
    QObject::connect(
        &ptA,
        &Point2DO::yChanged,
        &ptMirror,
        &Point2DO::setX
    );
    qDebug() << ptA << ptMirror;
    ptA.setX(5.5);
    ptA.setY(3.25);
    qDebug() << ptA << ptMirror;
//    qDebug() << ptA.objectName() << ptMirror.objectName();
    qDebug();
}

void playConnectSignalSlotPointLogger() {
    qDebug().noquote() << "*** playConnectSignalSlotPointLogger ***";
    // create a logger receiving pointChangedEvent
    // 1. log the change in the console
    // 2. memorize timestamp of the last modification
    //      Map(name, timestamp)
    PointLogger pointLogger;
    Point2DO ptA("A", 1.0, 3.0);
    Point2DO ptB("B", 2.0, 2.0);
    Point2DO ptC("C", 3.0, 1.0);
    for (const Point2DO* pt: QList({&ptA, &ptB, &ptC})) {
        QObject::connect(
            pt,
            &Point2DO::pointChanged,
            &pointLogger,
            qOverload<const Point2DO&>(&PointLogger::logPointChanged)
        );
    }
    ptA.setX(7.0);
    QThread::sleep(2);
    ptB.setX(8.0);
    QThread::sleep(2);
    ptA.setX(-7.0);
    QThread::sleep(2);
    ptC.setY(9.0);

    qDebug() << pointLogger.lastChangeSummary();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<Point2DM>();
    playWithPoints();
    playWithPointsMeta();
    playWithPointsObject();
    playConnectSignalSlot2points();
    playConnectSignalSlotPointLogger();
    //    return a.exec();
}
