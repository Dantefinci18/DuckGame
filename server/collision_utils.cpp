#include "collision_utils.h"

std::optional<Vector> line_intersects_line_with_point(const Vector& p1, const Vector& p2, 
                                                      const Vector& q1, const Vector& q2) {
    float x1 = p1.x, y1 = p1.y;
    float x2 = p2.x, y2 = p2.y;
    float x3 = q1.x, y3 = q1.y;
    float x4 = q2.x, y4 = q2.y;

    float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (denom == 0.0f) {
        if ((y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1)) {
            float min_x1 = std::min(x1, x2), max_x1 = std::max(x1, x2);
            float min_y1 = std::min(y1, y2), max_y1 = std::max(y1, y2);
            float min_x2 = std::min(x3, x4), max_x2 = std::max(x3, x4);
            float min_y2 = std::min(y3, y4), max_y2 = std::max(y3, y4);

            if (max_x1 >= min_x2 && max_x2 >= min_x1 && 
                max_y1 >= min_y2 && max_y2 >= min_y1) {
                float inter_x = std::max(min_x1, min_x2);
                float inter_y = std::max(min_y1, min_y2);
                return Vector(inter_x, inter_y);
            }
        }

        return std::nullopt;
    }

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;

    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
        float inter_x = x1 + t * (x2 - x1);
        float inter_y = y1 + t * (y2 - y1);
        return Vector(inter_x, inter_y);
    }

    return std::nullopt;
}