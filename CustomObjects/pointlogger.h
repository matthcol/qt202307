#ifndef POINTLOGGER_H
#define POINTLOGGER_H

#include <QObject>
#include <QMap>
#include <QDateTime>

#include "point2do.h"
#include "point2dm.h"


class PointLogger: public QObject
{
    Q_OBJECT

public:
    PointLogger(QObject* parent=nullptr);
    virtual ~PointLogger();
    QString lastChangeSummary() const;

public slots:
    void logPointChanged(const Point2DO& point);
    void logPointChanged(const Point2DM& point);

private:
    // default value: empty map
    QMap<QString, QDateTime> m_lastChangeMap;
};


#endif // POINTLOGGER_H
