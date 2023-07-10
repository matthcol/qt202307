#include "dateutils.h"

QDate operator+(const QDate& lhs, quint64 rhs) {
    // NB: can be written in a single instruction:
    // return lhs.addDays(rhs);
    QDate newDate = lhs.addDays(rhs);
    return newDate;
}

QDate& operator+=(QDate& lhs, quint64 rhs) {
    // TODO: increment lhs whith rhs days
    QDate tmpDate = lhs.addDays(rhs);
    lhs.setDate(tmpDate.year(), tmpDate.month(), tmpDate.days());
    return lhs;
}
