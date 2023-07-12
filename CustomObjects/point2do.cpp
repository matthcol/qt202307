#include "point2do.h"

// Example of partial constructor calling all args constructor
//Point2DO::Point2DO(const QString& name):
//    Point2DO(name, 0.0, 0.0, nullptr) {}

Point2DO::Point2DO(const QString& name, qreal x, qreal y, QObject* parent):
    QObject(parent), m_name(name), m_x(x), m_y(y)
{
    QObject::connect(this, &Point2DO::xChanged, this, &Point2DO::attributeChanged);
    QObject::connect(this, &Point2DO::yChanged, this, &Point2DO::attributeChanged);
    QObject::connect(this, &Point2DO::nameChanged, this, &Point2DO::attributeChanged);
}

Point2DO::~Point2DO(){

}

QStringView Point2DO::name() const {
    return m_name; // QStringView(m_name)
}

void Point2DO::setName(const QString& name) {
    m_name = name; // i.e. this->m_name
    emit nameChanged(m_name);
}

qreal Point2DO::x() const {
    return m_x;
}

void Point2DO::setX(qreal x) {
    m_x = x;
    emit xChanged(m_x);
}

qreal Point2DO::y() const {
    return m_y;
}

void Point2DO::setY(qreal y) {
    m_y = y;
    emit yChanged(m_y);
}

void Point2DO::attributeChanged() {
    emit pointChanged(*this);
}

QDebug operator<<(QDebug out, const Point2DO& point){
    QDebugStateSaver saver(out);
    return out.nospace() << "Point2DO("
                << point.name()
                << " ; x="
                << point.x()
                << " ; y="
                << point.y()
                << ")";
}
