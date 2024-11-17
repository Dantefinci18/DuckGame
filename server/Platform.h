#ifndef PLATFORM_H
#define PLATFORM_H
#include "Collidable.h"

class Platform : public Collidable {
    public:
    Platform(Vector position, float width, float height) : Collidable(position, width, height) {}

    virtual CollidableType getType() const override {
        return CollidableType::Platform;
    }

    virtual bool onCollision([[maybe_unused]]Collidable& other) override {
        return false;
    }
    virtual ~Platform() {}
    void print_bounding_box() const override {
        std::cout << "Platform box: (" 
            << "left: " <<  std::to_string(left()) << ", "
            << "right: " <<  std::to_string(right()) << ", "
            << "top: " <<  std::to_string(top()) << ", "
            << "bottom: " <<  std::to_string(bottom()) << std::endl;
    }

    virtual void update([[maybe_unused]]std::vector<Collidable*> others) override {
    
    }
    
    void print_position() const override {
        std::cout << "Platform position" << "(" << position.x << ", " << position.y << ")\n";
    }
};
#endif
