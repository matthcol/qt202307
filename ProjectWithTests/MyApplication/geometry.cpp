#include "geometry.h"

#include <QtMath>
qreal triangle_area(qreal a, qreal b, qreal c){
    qreal s = 0.5 * (a + b + c);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
