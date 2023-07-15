#include <QCoreApplication>
#include <QThreadPool>
#include <QtConcurrent>
#include <numeric> // C++ std
#include <functional>

void longComputation() {
    quint64 cpt = 0;
    for (quint64 i=0; i<1000000000LL; i++) {
        cpt = (2*(cpt+3)) % 10999999LL;
    }
    qDebug() << "Computation finished:" << cpt;
}

void playWithThreadPool() {
    QThreadPool* pool = QThreadPool::globalInstance();
    int threadCount = pool->maxThreadCount();
    qDebug() << "Number of threads in the pool:" << threadCount;
    pool->setMaxThreadCount(3);
    qDebug() << "Number of threads in the pool:" << pool->maxThreadCount();
    for (int i=0; i<7; i++) pool->start(&longComputation);
    qDebug() << "Task(s) started. Waiting for results";
    pool->waitForDone();
}

void partialSum(
    qsizetype first, qsizetype last,
    const QList<qreal>* source,
    qsizetype index,
    QList<qreal>* destination)
{
    qreal res = std::accumulate(
        source->cbegin()+first,
        source->cbegin()+last,
        0.0
        //, std::plus<qreal>()
        );
    qDebug() << first << last << res << source->sliced(first,3);
    (*destination)[index] = res;
}

void playSplitComputation(){
    qsizetype size = 1000000;
    qsizetype workerCount = 10;
    qsizetype chunk = size / workerCount;
    // source and destination are in the shared memory between threads
    QList<qreal>* data = new QList<qreal>(size);
    QList<qreal>* results = new QList<qreal>(workerCount);
    // TODO: use #include QRandomGenerator
    qDebug() << "Sums (before computation):" << *results;
    for (qsizetype i=0; i<size; i++) (*data)[i] = i;
    qDebug() << "Data (extracts):"
             << data->sliced(0,5)
             << data->sliced(size-5,5);
    QThreadPool* pool = QThreadPool::globalInstance();
    pool->setMaxThreadCount(3);
    for (qsizetype i=0; i<workerCount; i++) {
        pool->start([=]{
            partialSum(
                i*chunk,
                (i+1)*chunk,
                data,
                i,
                results);
        });
    }
    pool->waitForDone();
    qDebug() << "Sums:" << *results;
    delete data;
    delete results;
}

// TODO: same example with a Runnable with signal

class MyError{};

void playWithQtConcurrent() {
    // Documentation of Map/Filter/Reduce
    // https://doc.qt.io/qt-6/qtconcurrentmap.html
    qsizetype size = 1000000;
    QList<qreal> data = QList<qreal>(size);
    for (qsizetype i=0; i<size; i++) (data)[i] = i;

    // NB: map function (in place) must have following signature
    // U function(T &t);
    // PS: return value is not used (might be void)
    QtConcurrent::blockingMap(
        data.begin(),
        data.end(),
        [](qreal& x){ x = 2.0*x; });
    qDebug() << "Data (*2):"
             << data.sliced(0,5)
             << data.sliced(size-5,5);

    // NB: mapped function must have following signature
    // U function(const T &t);
    QList<qreal> results = QtConcurrent::blockingMapped<QList<qreal>>(
        data.begin(),
        data.end(),
        [](const qreal& x){ return x+0.5; });
    qDebug() << "Data (+0.5):"
             << results.sliced(0,5)
             << results.sliced(size-5,5);

    // NB: reduce function must have following signature
    // V function(T &result, const U &intermediate)
    // PS: V is not used (might be void)
    qreal result = QtConcurrent::blockingMappedReduced(
        data.begin(),
        data.end(),
        [](const qreal& x){ return x*x; },
        [](qreal& acc, const qreal& x){ acc += x; }
        //    OK:  acc += x
        //    NOK: std::plus<qreal>() // (x1,x2) => x1+x2
    );
    qDebug() << "Square sum: " << result;
    QFuture<qreal> futureResult = QtConcurrent::mappedReduced(
        data.begin(),
        data.end(),
        [](const qreal& x){ return x*x; },
        [](qreal& acc, const qreal& x){ acc += x; }
        , 999.99 // init value
        );
//    qreal result2 = futureResult.result();
//    qDebug() << "Square sum: " << result2;
    futureResult
        .then([](qreal x) {
            qDebug() << "Result is finally here:" << x;
        }).onCanceled([] {
            qDebug() << "Computation has been canceled";
        }).onFailed([](const MyError &e) {
           // Handle exceptions of type MyError
           qDebug() << "Computation has failed (1)";
        }).onFailed([] {
            // Handle all other types of errors
            qDebug() << "Computation has failed (2)";
        });
    QThreadPool::globalInstance()->waitForDone();
}

// See also: filteredReduce, QFutureWatcher, QPromise

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    playWithThreadPool();
//    playSplitComputation();
    playWithQtConcurrent();
    //    return a.exec();
    return 0;
}
