#include <QCoreApplication>
#include <QList>
#include <QHash>
#include <QMap>
#include <QQueue>
#include <QSet>
#include <QtMath>
#include <QDate>

// Containers: QList, QHash, QMap, QQueue, QSet
void playWithContainersOfReals() {
    QList<qreal> emptyList;

    QList<qreal> temperatures {12.5, 34.5, 22.3, 15.7};
    // i.e.:QList<qreal> temperatures = {12.5, 34.5, 22.3, 15.7};

    QList<qreal> temperatures2(temperatures);
    // i.e.: QList<qreal> temperatures2 = temperatures;

    QList<qreal> temperatures4 {15.1, 15.2};

    temperatures.append(25.3);
    temperatures.append(QList<qreal>({12.2, 12.3, 12.4})); // append by move
    temperatures.append(temperatures4); // append by copy
    temperatures << 33.1 << 33.2; // operator<< or operator+= eq append
    temperatures += -12.3; // or list ...
    temperatures += {12.3, 12.3, 12.3};
    temperatures.insert(3, 45.2); // + many overloads of this method
    qDebug() << emptyList;
    qDebug() << temperatures;
    qDebug() << temperatures2;

    qDebug() << "Delete values:";
    // at index i
    temperatures.removeAt(0);
    qDebug() << temperatures;
    // at index i, n values
    temperatures.remove(2, 3);
    qDebug() << temperatures;
    // first value found
    temperatures.removeOne(12.3);
    qDebug() << temperatures;
    // all value found
    temperatures.removeAll(12.3);
    qDebug() << temperatures;

    temperatures << (3*0.1); // 0.1 (base 10) = 0.00011001100.. (base 2)
    qDebug() << temperatures;
    temperatures.removeAll(0.3); // not found !!
    qDebug() << temperatures;

    temperatures.removeIf([](qreal v){
        return qFabs(v - 0.3) < 1E-4;
    });
    qDebug() << temperatures;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    playWithContainersOfReals();
    // return a.exec();
}
