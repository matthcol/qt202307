#include "dateutils.h"

QDate operator+(const QDate& lhs, quint64 rhs) {
    return QDate();
}

QDate& operator+=(QDate& lhs, quint64 rhs) {
    // TODO: increment lhs whith rhs days
    return lhs;
}
