#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QDate>
#include <QVariant>

#include "dateutils.h"
#include "memutils.h"

// links
// primitives types: https://doc.qt.io/qt-6/qttypes.html
// QString: https://doc.qt.io/qt-6/qstring.html
// QDate: https://doc.qt.io/qt-6/qdate.html
// QVariant:


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
    qsizetype threshold = 10;
    // value.clear(); // forbidden with const
    return value.length() < threshold;
}

void playWithString(){
    qDebug().noquote() << "** PLAY WITH STRINGS **";

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
    qDebug() << city;
    qDebug();
}

void playWithIntegers(){
    qDebug().noquote() << "** PLAY WITH INTEGERS **";

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
    qDebug();
}

void playWithReals() {
    qDebug().noquote() << "** PLAY WITH REALS **";

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
    qDebug();
}

void playWithQDates() {
    qDebug().noquote() << "** PLAY WITH QDATE **";
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
    QDate aDate6 = aDate5 + 4;
    qDebug() << aDate6;
    aDate6 += 2;
    qDebug() << aDate6;
    qDebug();
}

void playWithQVariant(){
    qDebug().noquote() << "** PLAY WITH QVARIANT **";
    QVariant magicVar1 = 12; // constructor QVariant(int)
    QVariant magicVar2 = QString("QT is Magic"); // constructor QVariant(QString)
    QVariant magicVar3; // default constructor: invalid variant
    magicVar3.setValue(12.5);
    QList<QVariant> variants;
    variants << magicVar1
             << magicVar2
             << magicVar3
             << QVariant()
             << QVariant::fromValue(QDate::currentDate()); // T = QDate
    qDebug() << variants;

    // C++ 11 "foreach"
    for (const QVariant& variant: variants) {
        qDebug() << " - type id:"
                 << variant.typeId()
                 << "; type name:"
                 << variant.typeName()
                 << "; valid:"
                 << variant.isValid();
        if (variant.canConvert<quint64>()) {
            quint64 realNumber = variant.toLongLong();
            qDebug() << "I've an integer:" << realNumber;
        }
        if (variant.canConvert<QString>()) {
            QString realString = variant.toString();
            qDebug() << "I have a string:" << realString;
        }
        if (variant.canConvert<QDate>()) {
            QDate aDate = variant.value<QDate>();
            qDebug() << "I have a date:" << aDate;
        }
    }
    qDebug();
}

class NotCopyable {
public:
    NotCopyable()=default;
    NotCopyable(const NotCopyable& other)=delete;
    NotCopyable operator=(const NotCopyable& other)=delete;
};

void playWithTemplates(){
    quint8 a = 12;
    quint8 b = 107;
    QDate d1(2023, 7, 14);
    QDate d2(2021, 8, 15);

    qDebug() << a << b;
    swap(a, b); // instantiate template with T=quint8
    qDebug() << a << b;
    swap(a, b); // template is already instantiated with quint8
    qDebug() << a << b;

    qDebug() << d1 << d2;
    swap(d1, d2); // instantiate template with T=QDate
    qDebug() << d1 << d2;

    NotCopyable nc1;
    NotCopyable nc2;
    // instantiate template with T=NotCopyable:
    // Compilation error with copy constructor and operator
    // swap(nc1,nc2);

    qDebug();
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
    playWithQVariant();
    playWithTemplates();
//    return a.exec(); // no event or server
    return 0;
}
