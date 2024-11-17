#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Vector.h"
#include <vector>
#include <algorithm>
#include <iostream>
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
