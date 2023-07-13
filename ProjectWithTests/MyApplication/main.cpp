#include <QCoreApplication>
#include "geometry.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "hello";
    qDebug() << triangle_area(3, 4, 5);

//    return a.exec();
}
