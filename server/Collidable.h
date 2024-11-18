#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Vector.h"
//#include "collision_utils.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <optional>

enum class CollidableType {
    Platform,
    Player,
    Box,
    SpawnPlace // Future types can be added here
};

enum class CollidableSide {
    Left,
    Right,
    Top,
    Bottom,
    None
};

class Collidable {
public:
    Vector position;
    float width;
    float height;

    float left() const {
        return position.x;
    }
    float right() const {
        return position.x + width;
    }
    float top() const {
        return position.y + height;
    }
    float bottom() const {
        return position.y;
    }

    bool isColliding(const Collidable& other) const {
        return (position.x < other.position.x + other.width && 
                position.x + width > other.position.x && 
                position.y < other.position.y + other.height && 
                position.y + height > other.position.y);
    }

    CollidableSide getCollisionSide(const Collidable& other) const {
        if (!isColliding(other)) {
            return CollidableSide::None;
        }
        float leftDistance = abs(other.left() - right());
        float rightDistance = abs(other.right() - left());
        float topDistance = abs(other.top() - bottom());
        float bottomDistance = abs(other.bottom() - top());

        float minDistance = std::min({leftDistance, rightDistance, bottomDistance, topDistance});
        if (minDistance == topDistance) {
            return CollidableSide::Top;
        } else if (minDistance == bottomDistance) {
            return CollidableSide::Bottom;
        } else if (minDistance == leftDistance) {
            return CollidableSide::Left;
        } else {
            return CollidableSide::Right;
        }
    }

    std::optional<Vector> line_intersects_line_with_point(const Vector& p1, const Vector& p2, 
                                                      const Vector& q1, const Vector& q2) const{
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

    std::optional<Vector> intersection_point(const Vector& start, const Vector& end) const {
    
        Vector top_left(left(), top());
        Vector top_right(right(), top());
        Vector bottom_left(left(), bottom());
        Vector bottom_right(right(), bottom());

        std::vector<std::pair<Vector, Vector>> edges = {
            {bottom_left, top_left},
            {top_left, top_right},
            {bottom_right, top_right},
            {bottom_left, bottom_right}
        };

        for (const auto& edge : edges) {
            auto intersection = line_intersects_line_with_point(start, end, edge.first, edge.second);
            if (intersection) {
                return intersection;
            }
        }

        return std::nullopt;
    }

    virtual void print_bounding_box() const = 0;
    virtual void print_position() const = 0;
    virtual CollidableType getType() const = 0;
    virtual bool onCollision(Collidable& other) = 0;
    virtual void update(std::vector<Collidable*> others) = 0;

    virtual ~Collidable() {}
    Collidable(const Vector& initialPosition, float width, float height)
        : position(initialPosition), width(width), height(height) {}
};

#endif
