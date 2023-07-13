#include <QCoreApplication>
#include <QtSql>

// https://doc.qt.io/qt-6/sql-programming.html
// https://doc.qt.io/qt-6/sql-connecting.html
// https://doc.qt.io/qt-6/sql-driver.html
// https://doc.qt.io/qt-6/sql-sqlstatements.html

// To Explore: transactions
// QSqlDatabase::database().transaction();
// QSqlDatabase::database().commit();

const QString SQL_ALL_MOVIES = "select id, title, year, duration from movies order by year desc, title";

const QString SQL_MOVIES_RANGE_YEAR = "select id, title, year, duration from movies where year between ? and ? order by year, title";
const QString SQL_MOVIES_RANGE_DURATION = "select id, title, year, duration from movies where duration between :duration1 and :duration2 order by duration, title";
const QString SQL_PERSONS_INSERT = "insert into persons (name, birthdate) values (:name, :birthdate) returning id";

void initDb(){
    // NB: by giving a name, we can use multiple bases
    // QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "dbmovie");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("password");
}

void playWithDbListTables(){
    // QSqlDatabase::database(name) => open=true
    QSqlDatabase db = QSqlDatabase::database("dbmovie");
    QStringList tables = db.tables();
    qDebug() << tables;
    qDebug();
    db.close();
}

void playWithDbReadMovies(){
    QSqlDatabase db = QSqlDatabase::database("dbmovie", false);
    if (!db.open()) {
        qDebug() << "Error while opening database";
        return;
    }
    qDebug() << "DB open ?" << db.isOpen();
    {
        QSqlQuery query(db);
        if (!query.exec(SQL_ALL_MOVIES)) {
            qDebug() << "Error while executing SELECT on table movies";
            db.close();
            return;
        }
        if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
            qDebug() << "Movie count:" << query.size();
        }
        // read the results (cursor)
        while (query.next()) {
            // each field is wrapped in a QVariant
            qint32 id = query.value("id").toInt();
            QString title = query.value("title").toString();
            qint16 year = query.value("year").value<qint16>();
            qint16 duration = query.value("duration").value<qint16>();
            qDebug() << id << title << year << duration;
        }
        qDebug() << "Inside block";
    } // destroy QSqlQuery and free resources (cursor)
    qDebug() << "Outside block";

    // TODO: fix Unable to free statement: connection pointer is NULL

    qDebug();
    db.close();
}

void playWithDbReadMoviesYear(){
    QSqlDatabase db = QSqlDatabase::database("dbmovie", false);
    if (!db.open()) {
        qDebug() << "Error while opening database";
        return;
    }
    qDebug() << "DB open ?" << db.isOpen();
    {
        QSqlQuery query(db);
        query.prepare(SQL_MOVIES_RANGE_YEAR);
        query.addBindValue(1982); // for 1st placeholder
        query.addBindValue(1984); // for 2nd placeholder
        if (!query.exec()) {
            qDebug() << "Error while executing SELECT on table movies";
            db.close();
            return;
        }
        if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
            qDebug() << "Movie count:" << query.size();
        }
        // read the results (cursor)
        while (query.next()) {
            // each field is wrapped in a QVariant
            qint32 id = query.value("id").toInt();
            QString title = query.value("title").toString();
            qint16 year = query.value("year").value<qint16>();
            qint16 duration = query.value("duration").value<qint16>();
            qDebug() << id << title << year << duration;
        }
    } // destroy QSqlQuery and free resources (cursor)
    qDebug();
    db.close();
}

void playWithDbReadMoviesDuration(){
    QSqlDatabase db = QSqlDatabase::database("dbmovie", false);
    if (!db.open()) {
        qDebug() << "Error while opening database";
        return;
    }
    qDebug() << "DB open ?" << db.isOpen();
    {
        QSqlQuery query(db);
        query.prepare(SQL_MOVIES_RANGE_DURATION);
        query.bindValue(":duration1", 120); // for named placeholder
        query.bindValue(":duration2", 135); // for named placeholder
        if (!query.exec()) {
            qDebug() << "Error while executing SELECT on table movies";
            db.close();
            return;
        }
        if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
            qDebug() << "Movie count:" << query.size();
        }
        // read the results (cursor)
        while (query.next()) {
            // each field is wrapped in a QVariant
            qint32 id = query.value("id").toInt();
            QString title = query.value("title").toString();
            qint16 year = query.value("year").value<qint16>();
            qint16 duration = query.value("duration").value<qint16>();
            qDebug() << id << title << year << duration;
        }
    } // destroy QSqlQuery and free resources (cursor)
    qDebug();
    db.close();
}

void playWithDbInsertPerson(){
    QSqlDatabase db = QSqlDatabase::database("dbmovie", false);
    if (!db.open()) {
        qDebug() << "Error while opening database";
        return;
    }
    qDebug() << "DB open ?" << db.isOpen();
    {
        QSqlQuery query(db);
        query.prepare(SQL_MOVIES_RANGE_DURATION);
    }
    {
        QSqlQuery query(db);
        query.prepare(SQL_PERSONS_INSERT);
        query.bindValue(":name", "Antony Starr");
        query.bindValue(":birthdate", QDate(1975,10,25));
        if (!query.exec()) {
            qDebug() << "Error while executing SELECT on table movies";
            db.close();
            return;
        }
        query.next(); // read 1st row
        qint32 id = query.value(0).toInt();
        qDebug() << "Person added with id:" << id;
    }
}

void playWithDbInsertPersons(){
    QVariantList names;
    names << "Antony Starr" << "Matthias" << "Alexandre";
    QVariantList birthdates;
    birthdates << QDate(1975,10,25) << QDate(1975,4,4) << QDate(1975,3,3);
    QSqlDatabase db = QSqlDatabase::database("dbmovie", false);
    if (!db.open()) {
        qDebug() << "Error while opening database";
        return;
    }
    qDebug() << "DB open ?" << db.isOpen();
    {
        QSqlQuery query(db);
        query.prepare(SQL_MOVIES_RANGE_DURATION);
    }
    {
        QSqlQuery query(db);
        query.prepare(SQL_PERSONS_INSERT);
        query.bindValue(":name", names);
        query.bindValue(":birthdate", birthdates);
        if (!query.execBatch()) {
            qDebug() << "Error while executing SELECT on table movies";
            db.close();
            return;
        }
        while (query.next()) { // only the last one :(
            qint32 id = query.value(0).toInt();
            qDebug() << "Person added with id:" << id;
        }
    }
}





int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    initDb();
    playWithDbListTables();
    playWithDbReadMovies();
    playWithDbReadMoviesYear();
    playWithDbReadMoviesDuration();
    playWithDbInsertPerson();
    playWithDbInsertPersons();
    // return a.exec();
    return 0;
}
