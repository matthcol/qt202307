#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QDate>

//#include "dateutils.h"

// links
// primitives types: https://doc.qt.io/qt-6/qttypes.html
// strings: https://doc.qt.io/qt-6/qstring.html


QString welcomeMessage(){
    // call constructor QString(const char *str)
    QString day = "monday";

    qint64 bigNumber = 123123123123123123;

    // call QString(QString &&other)
    QString output = QString("day = %1; count = %2")
                         .arg(day)
                         .arg(bigNumber);
    return output;
}

bool isShortString(const QString& value){
    quint64 threshold = 10;
//    value.clear();
    return value.length() < threshold;
}

void playWithString(){
    QString city = u8"東京";
    const QString country("Japan");

    // method modifying QString
    city.append(" is a beautiful city of ")
        .append(country);
    qDebug() << city;

    // method reading QString
    bool question = city.contains(country);
    qDebug() << "Test contains: " << question;

    qDebug() << city << " is a short text: " << isShortString(city);
    qDebug() << country << " is a short text: " << isShortString(country);

    // check variables
    qDebug() << "variables: " << city << country;

    // Comparisons: <, <=, >, >=, ==, !=
    qDebug() << "Test < :" << (country < QString("Java"));

    // operator []
    qDebug() << country[0];
//    country[0] = 'Z'; // forbidden because data is const
    city[0] = 'Z'; // ok string is mutable
}

void playWithIntegers(){
    quint8 color = 255;
    quint32 count = 4000000000;
    quint64 bigCount = 18000000000000000000LL;
    qint32 solde = -2000000000;
    qDebug() << color << count << bigCount << solde;
    // numeric operators
    solde++; // ++solde, --solde, solde--
    solde += 3; // -= *= /=
    solde = ((-solde + 40) * 3 / 2) % 1000;
    qDebug() << solde;
    // binary operator: shift << >>, xor ^, not ~, or |, and &
    quint8 newColor = (color >> 4); // color << 2
    quint8 inversedColor = ~newColor;
    qDebug() << newColor  // 00001111
             << inversedColor  // 11110000
             << (newColor | 16) // 00011111
             << (newColor & 22); // 00000110
    // TODO: Comparisons: <, <=, >, >=, ==, !=
}

void playWithReals() {
    qreal temperature = 30.7;
    qreal bigDistance = 1E308;
    qreal verySmallData = -1.012E-308;
    qreal temperature2 = 1.37 * temperature;
    qreal x = 3.0;
    qreal y = 2.0;
    qDebug() << "Temperatures:"
             << temperature
             << temperature2
             << QString("%1").arg(temperature2,0,'f',2, u' ');
    qDebug() << "Big distance:" << bigDistance
             << bigDistance * 2
             << 0.0 / (x -y -1.0);
    qDebug() << "Small data:" << verySmallData;
    // TODO: Comparisons: <, <=, >, >=
    // WARNING: Comparison ==, != with caution => work with delta
}

void playWithQDates() {
    QDate aDate; // default constuctor
    QDate aDate2(2023, 7, 13);
    QDate aDate3(2023, 2, 29);
    QDate aDate4 = QDate::currentDate();
    QDate aDate5 = QDate::fromString("2023-07-14", "yyyy-MM-dd");
    qDebug() << aDate
             << aDate2
             << aDate3
             << aDate4 << aDate4.toString("dd/MM/yyyy")
             << aDate5;
    qDebug() << aDate4.addDays(7);
    qint64 diffDate = aDate5.toJulianDay() - aDate4.toJulianDay();
    qDebug() << diffDate
             // arithmetic QDate and qint64 (julianDay)
             << QDate::fromJulianDay(QDate(2024,1,1).toJulianDay() + diffDate);
    // see also QTime, QDateTime

    // operators
    qDebug() << "Precedence:" << (aDate4 < aDate5); // <=, >, >=, ==, !=

    // new overload of operator...
//    QDate aDate6 = aDate5 + 4;
//    qDebug() << aDate6;
//    aDate6 += 2;
//    qDebug() << aDate6;
}

void playWithQVariant(){
    QVariant magicVar1 = 12;
    QVariant magicVar2 = QString("QT is Magic");
    QList<QVariant> variants;
    variants << magicVar1 << magicVar2 << QVariant();

    for (const QVariant& variant: variants) {
        if (variant.convert<QString>()) {
            QString realString = variant.toString();
            qDebug() << "I have a string:" << realString;
        } else if (variant.convert<quint64>()) {
            quint64 realNumber = variant.toLonglong();
            qDebug() << "I've an integer": << realNumber
        } else {
            qDebug() << "I don't know what contains my variant";
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString message = welcomeMessage();
    qDebug() << message;
    playWithString();
    playWithIntegers();
    playWithReals();
    playWithQDates();
//    return a.exec(); // no event or server
    return 0;
}
