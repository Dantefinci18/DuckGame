#ifndef PLAYER_H
#define PLAYER_H
#include "Vector.h"
#include "Collidable.h"
#include "Platform.h"
#include "SpawnPlace.h"
#include <iostream>
#include <optional>
#include <memory>
#include "../common/common_weapon.h"
#include "../common/common_evento.h"
#include "../common/common_color.h"

class Player : public Collidable {
    private:
        Vector velocity;
        float speed;
        bool is_on_ground;
        bool is_standing_on_something;
        int jump_force;
        int id;
        ColorDuck color;
    public:
        std::vector<std::shared_ptr<Evento>> eventos;
    void move() {
        std::cout << "Velocity y: " << velocity.y << std::endl;
        std::cout << "Jump force: " << jump_force << std::endl;
        std::cout << "Position y: " << position.y << std::endl;
        std::cout << "--------------------------" << std::endl;
        if (velocity.y > -8 && jump_force == 0) {
            velocity.y -= 1;
        }
        if (jump_force > 0) {
            jump_force--;
            velocity.y += 1;
        }
        position.y += velocity.y;
        position.x += velocity.x * speed;
        if (position.y < 0) {
            position.y = 0;
            velocity.y = 0;
            is_on_ground = true;
        }
        
    }

    void set_x_direction(float x) {
        velocity.x = x;
    }

    void jump() {
        if (is_able_to_jump()) {
            is_on_ground = false;
            jump_force = 15;
        }
    }

    virtual void update(std::vector<Collidable*> others) override {
        
        int x_before = position.x;
        int y_before = position.y;
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

        if (x_before != position.x || y_before != position.y) {
            eventos.push_back(std::make_shared<EventoMovimiento>(id,color,position.x, position.y));
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
                velocity.x = 0;
                return true;
            }
            return false;
        }

        if (other.getType() == CollidableType::SpawnPlace) {
            SpawnPlace& spawnPlace = static_cast<SpawnPlace&>(other);
            CollidableSide side = getCollisionSide(spawnPlace);
            if (side == CollidableSide::None) {
                return false;
            }
            std::optional<std::unique_ptr<Weapon>> weapon = spawnPlace.get_weapon();
            if (weapon) {
                std::cout << "picked up weapon!" << std::endl;
                eventos.push_back(std::make_shared<EventoPickup>(id, spawnPlace.position.x, spawnPlace.position.y, weapon.value().get()->get_type()));
            }
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
        return is_on_ground || is_standing_on_something;
    }
    virtual ~Player() {}
    Player(Vector initialPosition, int id,ColorDuck color) : Collidable(initialPosition, 32.0f, 64.0f), velocity(Vector(0,0)), speed(3.0f), is_on_ground(false), is_standing_on_something(false), jump_force(0), id(id),color(color) {}
};
#endif