#include <QCoreApplication>
#include <QDebug>
#include <QString>

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
    qDebug() << newColor  // 00001111
             << ((quint8) ~newColor)  // 11110000
             << (newColor | 16) // 00011111
             << (newColor & 22); // 00000110
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString message = welcomeMessage();
    qDebug() << message;
    playWithString();
    playWithIntegers();
    return a.exec();
}
