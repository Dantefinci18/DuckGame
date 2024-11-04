#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include "Vector.h"
#include <iostream>
#include <algorithm>
enum class CollidableType {
    Platform,
    Player,
    Box // Future types can be added here
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
            print_bounding_box();
            //print_position();
            other.print_bounding_box();
            float leftDistance = abs(other.left() - right());
            float rightDistance = abs(other.right() - left());
            float topDistance = abs(other.top() - bottom());
            float bottomDistance = abs(other.bottom() - top());

            float minDistance = std::min({leftDistance, rightDistance, bottomDistance, topDistance});
            //std::cout << std::to_string(leftDistance) << ", " << std::to_string(rightDistance) << ", " << std::to_string(bottomDistance) << ", " << std::to_string(topDistance) << ")" << std::endl;
            //std::cout << "--------------------------------------------";
            if (minDistance == leftDistance) {
                std::cout << "left\n";
                return CollidableSide::Left;
            } else if (minDistance == rightDistance) {
                std::cout << "right\n";
                return CollidableSide::Right;
            } else if (minDistance == bottomDistance) {
                std::cout << "bottom\n";
                return CollidableSide::Bottom;
            } else {
                std::cout << "top\n";
                return CollidableSide::Top;
            }
        }

        virtual void print_bounding_box() const = 0;

        virtual void print_position() const = 0;
        virtual CollidableType getType() const = 0;

        virtual void onCollision(Collidable& other) = 0;

        virtual ~Collidable() {}
        Collidable(const Vector& initialPosition, float width, float height) : position(initialPosition), width(width), height(height) {}
};
#endif
