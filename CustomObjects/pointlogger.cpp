#include "pointlogger.h"
#include <QDebug>
#include <algorithm>

PointLogger::PointLogger(QObject* parent):
    QObject(parent)
{

}

PointLogger::~PointLogger(){}

QString PointLogger::lastChangeSummary() const {
    auto first = m_lastChangeMap.constKeyValueBegin(); // iter std::pair
    auto last = m_lastChangeMap.constKeyValueEnd();
    QStringList outputs;
    std::transform(
        first,
        last,
        std::back_inserter(outputs),
        // [](const std::pair<QString, QDateTime>& keyValue) -> QString {
        [](const auto& keyValue) {
            return QString("%1=%2")
                .arg(keyValue.first)
                .arg(keyValue.second.toString("yyyy-MM-ddThh:mm:ss.z"));
        }
    );
    return QString("[%1]").arg(outputs.join(", "));
}

void PointLogger::logPointChanged(const Point2DO& point){
    qDebug() << "A Point (QObject) has changed:" << point;
    m_lastChangeMap[point.name().toString()] = QDateTime::currentDateTime();
}

void PointLogger::logPointChanged(const Point2DM& point) {
    qDebug() << "A Point (META TYPE) has changed):" << point;
    m_lastChangeMap[point.name().toString()] = QDateTime::currentDateTime();
}
