#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H
#include "Collidable.h"
#include "../common/common_weapon.h"
#include <optional>
class SpawnPlace : public Collidable {
    private:
    int minTime;
    std::optional<Weapon> weapon;
    
    public:
    SpawnPlace(Vector position, float width, float height) : Collidable(position, width, height) {}

    virtual CollidableType getType() const override {
        return CollidableType::SpawnPlace;
    }

    virtual bool onCollision([[maybe_unused]]Collidable& other) override {
        return false;
    }

    virtual ~SpawnPlace() {}
    void print_bounding_box() const override {
        std::cout << "SpawnPlace box: (" 
            << "left: " <<  std::to_string(left()) << ", "
            << "right: " <<  std::to_string(right()) << ", "
            << "top: " <<  std::to_string(top()) << ", "
            << "bottom: " <<  std::to_string(bottom()) << std::endl;
    }

    void print_position() const override {
        std::cout << "SpawnPlace position" << "(" << position.x << ", " << position.y << ")\n";
    }

    virtual void update([[maybe_unused]] std::vector<Collidable*> others) override {

    }
};
#endif
