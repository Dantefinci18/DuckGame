#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include "Vector.h"
#include <algorithm>
enum class CollidableType {
    Platform,
    Player // Future types can be added here
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
        };
        float right() const {
            return position.x + width;
        };
        float top() const {
            return position.y + height;
        };
        float bottom() const {
            return position.y;
        };

        bool isColliding(const Collidable& other) const {
            return (position.x < other.position.x + other.width && 
                    position.x + width > other.position.x && 
                    position.y < other.position.y + other.height && 
                    position.y + height > other.position.y);
        }

        // Determine which side of the box was collided with
        CollidableSide getCollisionSide(const Collidable& other) const {
            if (!isColliding(other)) {
                return CollidableSide::None;
            }

            // Calculate the distances to determine the side of collision
            float leftDistance = (other.position.x + other.width) - position.x;   // Distance to the left side of 'this'
            float rightDistance = (other.position.x - (position.x + width));      // Distance to the right side of 'this'
            float bottomDistance = (other.position.y + other.height) - position.y; // Distance to the bottom side of 'this'
            float topDistance = (other.position.y - (position.y + height));        // Distance to the top side of 'this'

            // Find the smallest distance
            float minDistance = std::min({leftDistance, rightDistance, bottomDistance, topDistance});

            if (minDistance == leftDistance) {
                return CollidableSide::Left;
            } else if (minDistance == rightDistance) {
                return CollidableSide::Right;
            } else if (minDistance == bottomDistance) {
                return CollidableSide::Bottom;
            } else {
                return CollidableSide::Top;
            }
        }

        virtual CollidableType getType() const = 0;

        virtual void onCollision(Collidable& other) = 0;

        virtual ~Collidable() {}
        Collidable(const Vector& initialPosition, float width, float height) : position(initialPosition), width(width), height(height) {}
};
#endif
