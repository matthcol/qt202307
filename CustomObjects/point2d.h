#ifndef POINT2D_H
#define POINT2D_H

#include <QString>
#include <QDebug>

class Point2D
{
private:
    QString m_name;
    qreal m_x;
    qreal m_y;
public:
    Point2D() = default;
    Point2D(const QString& name, qreal x=0.0, qreal y=0.0);
    // gifts constructor by copy/move
    // fifts operator copy/move
    virtual ~Point2D();

    QStringView name() const;
    void setName(const QString& name);
    qreal x() const;
    void setX(qreal x);
    qreal y() const;
    void setY(qreal y);

    // Point2D operator+(const Point2D& other) const; // this + other
};

// qDebug() << pt
QDebug operator<<(QDebug out, const Point2D& point);

#endif // POINT2D_H
