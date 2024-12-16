#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "../../server/Vector.h"
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
enum class CollidableType {
    Platform,
    Player,
    Box,
    SpawnPlace,
    SpawnWeaponBox,
    SpawnBox
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

    Collidable(const Vector& initialPosition, float width, float height);
    virtual ~Collidable();

    float left() const;
    float right() const;
    float top() const;
    float bottom() const;

    bool isColliding(const Collidable& other) const;
    CollidableSide getCollisionSide(const Collidable& other) const;

    std::optional<Vector> line_intersects_line_with_point(
        const Vector& p1, const Vector& p2,
        const Vector& q1, const Vector& q2) const;

    std::optional<Vector> intersection_point(const Vector& start, const Vector& end) const;

    virtual void print_bounding_box() const = 0;
    virtual void print_position() const = 0;
    virtual CollidableType getType() const = 0;
    virtual bool onCollision(Collidable& other) = 0;
    virtual void update(std::vector<Collidable*> others) = 0;
};

#endif
