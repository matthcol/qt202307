#include "point2dm.h"



Point2DM::Point2DM(const QString& name, qreal x, qreal y):
    m_name(name), m_x(x), m_y(y)
{

}

Point2DM::~Point2DM(){

}

QStringView Point2DM::name() const {
    return m_name; // QStringView(m_name)
}

void Point2DM::setName(const QString& name) {
    m_name = name; // i.e. this->m_name
}

qreal Point2DM::x() const {
    return m_x;
}

void Point2DM::setX(qreal x) {
    m_x = x;
}

qreal Point2DM::y() const {
    return m_y;
}

void Point2DM::setY(qreal y) {
    m_y = y;
}
