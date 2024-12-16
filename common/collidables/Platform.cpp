#include "Platform.h"

Platform::Platform(Vector position, float width, float height) 
    : Collidable(position, width, height) {}

CollidableType Platform::getType() const {
    return CollidableType::Platform;
}

bool Platform::onCollision([[maybe_unused]] Collidable& other) {
    return false;
}

Platform::~Platform() {}

void Platform::print_bounding_box() const {
    std::cout << "Platform box: (" 
              << "left: " << std::to_string(left()) << ", "
              << "right: " << std::to_string(right()) << ", "
              << "top: " << std::to_string(top()) << ", "
              << "bottom: " << std::to_string(bottom()) << ")" 
              << std::endl;
}

void Platform::update([[maybe_unused]] std::vector<Collidable*> others) {
    // Implementation for updating the platform
}

void Platform::print_position() const {
    std::cout << "Platform position: (" << position.x << ", " << position.y << ")\n";
}
