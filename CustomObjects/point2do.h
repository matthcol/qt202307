#ifndef POINT2DO_H
#define POINT2DO_H

#include <QString>
#include <QDebug>
#include <QObject>

class Point2DO: public QObject
{
    Q_OBJECT

private:
    QString m_name;
    qreal m_x;
    qreal m_y;
public:
    Point2DO(const QString& name=QString(), qreal x=0.0, qreal y=0.0, QObject* parent=nullptr);
    // gifts constructor by move
    // gifts operator move
    // copy constructor/operator are deleted
    virtual ~Point2DO();

    QStringView name() const;
    qreal x() const;
    qreal y() const;

public slots:
    void setName(const QString& name);
    void setX(qreal x);
    void setY(qreal y);

private slots:
    void attributeChanged();

    // Point2D operator+(const Point2D& other) const; // this + other
signals:
//    void pointChanged();
    void pointChanged(const Point2DO&);
    void nameChanged(QStringView);
    void xChanged(qreal);
    void yChanged(qreal);
};

// qDebug() << pt
QDebug operator<<(QDebug out, const Point2DO& point);

#endif // POINT2DO_H
