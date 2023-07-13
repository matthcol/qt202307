#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QDataStream>
#include <QByteArray>

QByteArray movieToBlock(QString title, qint16 year) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << title.size();
    out << title;
    out << year;
    return block;
} // QDataStream closed

void sendMovie(QLocalServer* localServer) {
    qDebug() << "Connection client established";
    qDebug() << "Send movie to client...";

    QLocalSocket *clientConnection = localServer->nextPendingConnection();
    QObject::connect(
            clientConnection,
            &QLocalSocket::disconnected,
            clientConnection,
            &QLocalSocket::deleteLater
    );
    QByteArray block = movieToBlock("The Covenant", 2023);
    clientConnection->write(block);
    clientConnection->flush();
    clientConnection->disconnectFromServer();
    qDebug() << "Movie sent";
    qDebug();
}

void initServer(){
    QLocalServer* localServer = new QLocalServer();
    if (!localServer->listen("movies")) {
        qDebug() << "Unable to start local server";
        return;
    }
    QObject::connect(
        localServer,
        &QLocalServer::newConnection,
        [localServer]{
            sendMovie(localServer);
        });
    qDebug() << "Local server started";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    initServer();
    return a.exec();
}
