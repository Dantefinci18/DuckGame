#ifndef PLATFORM_H
#define PLATFORM_H
#include "Collidable.h"
#include <iostream>
class Platform : public Collidable {
    public:
    Platform(Vector position, float width, float height) : Collidable(position, width, height) {}

    virtual CollidableType getType() const override {
        return CollidableType::Platform;
    }

    virtual void onCollision([[maybe_unused]]Collidable& other) override {
        return;
    }
    virtual ~Platform() {}
    void print_bounding_box() const {
        std::cout << "Platform position:" << "\n" 
            << "left: " <<  std::to_string(left()) << ", "
            << "right: " <<  std::to_string(right()) << ", "
            << "top: " <<  std::to_string(top()) << ", "
            << "bottom: " <<  std::to_string(bottom()) << std::endl;
    }

    void print_position() const {
        std::cout << "Platform position" << "(" << position.x << ", " << position.y << ")\n";
    }
};
#endif
