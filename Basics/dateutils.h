#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <QDate>

QDate operator+(const QDate& lhs, quint64 rhs);
QDate& operator+=(QDate& lhs, quint64 rhs);

#endif // DATEUTILS_H
