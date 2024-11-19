#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <optional>
#include "Vector.h"

std::optional<Vector> line_intersects_line_with_point(
    const Vector& p1, const Vector& p2, 
    const Vector& q1, const Vector& q2);

#endif // COLLISION_UTILS_H
