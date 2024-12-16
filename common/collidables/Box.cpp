#include "Box.h"

Box::Box(Vector position, float width, float height)
    : Collidable(position, width, height), activa(true) {}

Box::~Box() {}

CollidableType Box::getType() const {
    return CollidableType::Box;
}

bool Box::onCollision(Collidable& other) {
    return false;
}

void Box::update(std::vector<Collidable*> others) {
    if (!activa) return;
}

void Box::print_bounding_box() const {
    std::cout << "Box box: (" 
              << "left: " << std::to_string(left()) << ", "
              << "right: " << std::to_string(right()) << ", "
              << "top: " << std::to_string(top()) << ", "
              << "bottom: " << std::to_string(bottom()) << ")\n";
}

Vector Box::get_position() const {
    return position;
}

void Box::print_position() const {
    std::cout << "Box position" << "(" << position.x << ", " << position.y << ")\n";
}

void Box::activar() {
    activa = true;
}

void Box::desactivar() {
    activa = false;
}

bool Box::esta_activa() const {
    return activa;
}
