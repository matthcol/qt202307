#include <QCoreApplication>
#include <QLocalSocket>
#include <QDataStream>
#include <QByteArray>

void readResponse(QLocalSocket* socket){
    qDebug() << "Read data from server";
    QDataStream in;
    in.setDevice(socket);
    QString title;
    qint16 year;
    qsizetype titleSize;

    // check socket->bytesAvailable() and in.atEnd()
    in >> titleSize;
    qDebug() << "Receive title size:" << titleSize;
    in >> title;
    qDebug() << "Receive title:" << title;
    in >> year;
    qDebug() << "Receive year:" << year;
}

void handleError(QLocalSocket::LocalSocketError socketError){
    qDebug() << "Error in the dialog:" << socketError;
}

void talkWithServer(){
    QString socketName = "movies";
    QLocalSocket* socket = new QLocalSocket();
    QObject::connect(
        socket,
        &QLocalSocket::readyRead,
        [socket]{
            readResponse(socket);
        });
    QObject::connect(
        socket,
        &QLocalSocket::errorOccurred,
        &handleError);
    // Repeat
    socket->connectToServer(socketName);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    talkWithServer();
    return a.exec();
}
