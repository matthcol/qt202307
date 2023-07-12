#include "point2d.h"



Point2D::Point2D(const QString& name, qreal x, qreal y):
    m_name(name), m_x(x), m_y(y)
{

}

Point2D::~Point2D(){

}

QStringView Point2D::name() const {
    return m_name; // QStringView(m_name)
}

void Point2D::setName(const QString& name) {
    m_name = name; // i.e. this->m_name
}

qreal Point2D::x() const {
    return m_x;
}

void Point2D::setX(qreal x) {
    m_x = x;
}

qreal Point2D::y() const {
    return m_y;
}

void Point2D::setY(qreal y) {
    m_y = y;
}

QDebug operator<<(QDebug out, const Point2D& point){
    QDebugStateSaver saver(out);
    return out.nospace() << "Point2D("
                << point.name()
                << " ; x="
                << point.x()
                << " ; y="
                << point.y()
                << ")";
}
