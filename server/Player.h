#ifndef PLAYER_H
#define PLAYER_H
#include "Vector.h"
#include "Collidable.h"
#include "Platform.h"
#include <iostream>
class Player : public Collidable {
    private:
        Vector velocity;
        float speed;
        bool is_on_ground;
        bool is_standing_on_something;
    public:
    void move() {
        velocity.y -= 0.2;
        position.y += velocity.y;
        position.x += velocity.x * speed;
        if (position.y < 0) {
            position.y = 0;
            velocity.y = 0;
            is_on_ground = true;
        }
        
    }

    void set_direction(const Vector& dir) {
        velocity = dir;
    }

    void jump() {
        if (is_able_to_jump()) {
            std::cout << "is_able" << std::endl;
            is_on_ground = false;
            velocity.y = 10.0f;
        }
    }

    void update(std::vector<Collidable*> others) {
        move();
        bool collide = false;
        for (auto collidable : others) {
            bool did_collide = onCollision(*collidable);
            if (did_collide) {
                collide = did_collide;
            }
        }

        if (!collide) {
            is_standing_on_something = false;
        } 

        //std::cout << velocity.to_string() << ", isOnGround" << std::to_string(is_on_ground) << std::endl;
        //std::cout << velocity.to_string() << std::endl;
    }

    

    virtual CollidableType getType() const override {
        return CollidableType::Player;
    }

    virtual bool onCollision(Collidable& other) override {
        if (other.getType() == CollidableType::Platform) {
            Platform& platform = static_cast<Platform&>(other);
            
            CollidableSide side = getCollisionSide(platform);
            if (side == CollidableSide::Top) {
                position.y = platform.top();
                velocity.y = 0;
                is_standing_on_something = true;
                return true;  
            }

            else if (side == CollidableSide::Bottom) {
                position.y = platform.bottom() - height;
                velocity.y = -velocity.y;
                return true;
            }

            else if (side == CollidableSide::Left || side == CollidableSide::Right) {
                velocity.x = -velocity.x;
                return true;
            }
            return false;
        }
        return false;
    }

    void print_bounding_box() const override {
        std::cout << "Player box: ("
            << "left: " <<  std::to_string(left()) << ", "
            << "right: " <<  std::to_string(right()) << ", "
            << "top: " <<  std::to_string(top()) << ", "
            << "bottom: " <<  std::to_string(bottom()) << std::endl;;
    }

    void print_position() const override {
        std::cout << "Player position" << "(" << position.x << ", " << position.y << ")\n";
    }

    Vector get_posicion(){
        return position;
    }

    bool is_able_to_jump() {
        std::cout << is_on_ground << is_standing_on_something << std::endl;
        return is_on_ground || is_standing_on_something;
    }
    virtual ~Player() {}
    Player(Vector initialPosition) : Collidable(initialPosition, 10.0f, 20.0f), velocity(Vector(0,0)), speed(3.0f), is_on_ground(false), is_standing_on_something(false) {}
};
#endif