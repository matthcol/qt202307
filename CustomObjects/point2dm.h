#ifndef POINT2DM_H
#define POINT2DM_H

#include <QString>
#include <QMetaType>

class Point2DM
{
private:
    QString m_name;
    qreal m_x;
    qreal m_y;
public:
    Point2DM() = default;
    Point2DM(const QString& name, qreal x=0.0, qreal y=0.0);
    // gifts constructor by copy/move
    // fifts operator copy/move
    virtual ~Point2DM();

    QStringView name() const;
    void setName(const QString& name);
    qreal x() const;
    void setX(qreal x);
    qreal y() const;
    void setY(qreal y);
};

Q_DECLARE_METATYPE(Point2DM)

#endif // POINT2DM_H
