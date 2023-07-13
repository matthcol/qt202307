#include <QCoreApplication>
#include <QLocalSocket>


void readResponse(QLocalSocket* socket){
    qDebug() << "Read data from server";
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
