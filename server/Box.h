#ifndef BOX_H
#define BOX_H
#include "Collidable.h"

class Box : public Collidable {
public:
    Box(Vector position, float width, float height)
        : Collidable(position, width, height), activa(true) {}

    virtual CollidableType getType() const override {
        return CollidableType::Box;
    }

    virtual bool onCollision([[maybe_unused]]Collidable& other) override {
        return false;
    }

    virtual ~Box() {}

    void print_bounding_box() const override {
        std::cout << "Box box: (" 
                  << "left: " << std::to_string(left()) << ", "
                  << "right: " << std::to_string(right()) << ", "
                  << "top: " << std::to_string(top()) << ", "
                  << "bottom: " << std::to_string(bottom()) << std::endl;
    }

    virtual void update([[maybe_unused]]std::vector<Collidable*> others) override {
        if (!activa) return;  
    }

    Vector get_position() const {
        return position; 
    }

    void print_position() const override {
        std::cout << "Box position" << "(" << position.x << ", " << position.y << ")\n";
    }

    void activar() { activa = true; }
    void desactivar() { activa = false; }

    bool esta_activa() const { return activa; }

private:
    bool activa;  
};

#endif
