#include <QCoreApplication>
#include <QList>
#include <QHash>
#include <QMap>
#include <QQueue>
#include <QSet>
#include <QtMath>
#include <QDate>
#include <QVariant>
#include <iterator> // C++ standard iterator tools
#include <vector> // C++ standard std::vector
#include <algorithm> // C++ functional/iterator tools


bool isNegative(qreal v){
    return v < 0.0;
}

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

    qreal valueToDelete = 12.0;
    qreal precision = 0.5;
    temperatures.removeIf(
        [valueToDelete, precision](qreal v){
            return qFabs(v - valueToDelete) < precision;
        }
    );
    qDebug() << temperatures;

    temperatures.removeIf(&isNegative);
    qDebug() << temperatures;

    // iterations
    // QT foreach
    qDebug() << "Temperatures iteration (QT)";
    foreach(qreal t, temperatures) {
        qDebug().noquote() << "\t-" << t;
    }
    // C+11 foreach
    qDebug() << "Temperatures iteration (C++11)";
    for (qreal t: temperatures) {
        qDebug().noquote() << "\t*" << t;
    }
    // explicit iterator
    qDebug() << "Temperatures iteration (explicit iterator)";
    QList<qreal>::iterator it = temperatures.begin();
    QList<qreal>::iterator end = temperatures.end();
    while (it != end) {
        qreal t = *it;
        qDebug().noquote() << "\t#" << t;
        ++it;
    }

    QSet<qreal> temperatureSet(
        temperatures.cbegin(),
        temperatures.cend()
    );
    qDebug() << temperatureSet;
    temperatureSet << 22.3 << 22.4; // 22.3 is already there, not added
    qDebug() << temperatureSet;

    qDebug() << "Source list:" << temperatures;
    QList<qreal> temperatureSlice1(
        temperatures.cbegin() + 2,
        temperatures.cbegin() + 5
    );
    qDebug() << "Slice(begin+2, begin+5):" << temperatureSlice1;
    QList<qreal> temperatureSlice2(
        temperatures.cbegin() + 2,
        temperatures.cend() - 2
    );
    qDebug() << "Slice(begin+2, end-2):" <<  temperatureSlice2;

    // NB: an iterator on QSet is not a LegacyRandomIterator
    // or a LegacyBidirectionalIterator
//    QList<qreal> temperatureSlice3(
//        temperatureSet.cbegin() + 2,
//        temperatureSet.cend() - 2
//    );
    QList<qreal> temperatureSlice3(
        std::next(temperatureSet.cbegin(), 2),
        std::next(temperatureSet.cbegin(), 5)
    );
    qDebug() << "Slice on a set:" <<  temperatureSlice3;

    std::vector<qreal> temperatureVector(
        temperatures.cbegin(),
        temperatures.cend()
    );
    // NB: std::vector, std::list are registered in QT
    // => qDebug, QVariant
    qDebug() << temperatureVector;
    QVariant variant = QVariant::fromValue(temperatureVector);
    qDebug() << variant;

    QList<qreal> temperatureReversed(
        temperatureVector.crbegin(),
        temperatureVector.crend()
    );
    qDebug() << temperatureReversed;
    qDebug();
}

void playWithStringList() {
    QList<QString> cityList {"Pau", "Bordeaux", "Toulouse"};
    // 1. transfer into a QListString
    QStringList cityStringList(cityList);
    // 2. display with qDebug
    qDebug() << cityStringList;
    // 3. transform into a string with separator  '->'
    qDebug() << cityStringList.join(" -> ");
    // 4. add paris
    cityStringList << "paris";
    qDebug() << cityStringList;
    // 5. sort cities (case insensitive)
    cityList.sort();
    qDebug() << cityStringList;
    cityStringList.sort(Qt::CaseInsensitive);
    qDebug() << cityStringList;
    // misc
    qDebug() << "PAU in the list: "
             << cityStringList.contains("PAU", Qt::CaseInsensitive);
    cityStringList << "Thau" << "Aubagne";
    cityStringList.replaceInStrings("au", "o", Qt::CaseInsensitive);
    qDebug() << cityStringList;
    QStringList filteredList = cityStringList.filter("PO", Qt::CaseInsensitive);
    qDebug() << filteredList;
    qDebug();

    // api algorithm of standard C++
    // filter cities starting with T: copy_if, find_if
    QStringList filteredListT;
    std::copy_if(
        cityStringList.cbegin(),
        cityStringList.cend(),
        std::back_inserter(filteredListT),
        [](auto& city){ return city.startsWith('T');}
    );
    qDebug() << filteredList;
    // transform all cities in upperCase: transform
    QStringList citiesUppercase(cityStringList.size());
    std::transform(
        cityStringList.cbegin(),
        cityStringList.cend(),
        citiesUppercase.begin(),
        [](auto & city){ return city.toUpper();}
    );
    qDebug() << citiesUppercase;
    qDebug();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    playWithContainersOfReals();
    playWithStringList();
    // return a.exec();
}
