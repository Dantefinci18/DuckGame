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
class Player : public Collidable {
    private:
        Vector velocity;
        float speed;
        bool is_on_ground;
        bool is_standing_on_something;
        bool shooting;
        int id;
        Vector direccion_mirada;
        std::unique_ptr<Weapon> weapon;
        
        void mirar_a_derecha() {
            direccion_mirada = Vector(1, 0);
        }

        void mirar_a_izquierda() {
            direccion_mirada = Vector(-1, 0);
        }

    public:
        std::vector<std::shared_ptr<Evento>> eventos;
    void move() {
        if (velocity.y > -5) {
            velocity.y -= 1;
        }
        position.y += velocity.y;
        position.x += velocity.x * speed;
        if (position.y < 0) {
            position.y = 0;
            velocity.y = 0;
            is_on_ground = true;
        }
        
    }

    Vector get_direccion_mirada() const {
        return direccion_mirada;
    }

    std::vector<Vector> disparar() {
        if (!weapon) {
            return {};
        }
        shooting = true;
        std::cout << "Disaparó el pato id "<< id << std::endl;
        eventos.push_back(std::make_shared<EventoDisparo>(id));
        return weapon->shoot(position, direccion_mirada, shooting);
    }

    void morir(){
        // falta logica acá o que se hace cuando se muere y donde
        std::cout << "Murió el pato id "<< id << std::endl;
        eventos.push_back(std::make_shared<EventoMuerte>(id));
    }

    void dejar_disparar(){
        if(shooting){
            shooting = false;
        }
    }

    void set_x_direction(float x) {
        velocity.x = x;
        if (x > 0) {
            mirar_a_derecha();
        } else if (x < 0) {
            mirar_a_izquierda();
        }
    }

    void jump() {
        if (is_able_to_jump()) {
            std::cout << "is_able" << std::endl;
            is_on_ground = false;
            velocity.y = 10.0f;
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
            eventos.push_back(std::make_shared<EventoMovimiento>(id, position.x, position.y));
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
            std::optional<std::unique_ptr<Weapon>> new_weapon = spawnPlace.get_weapon();
            if (new_weapon) {
                weapon = std::move(new_weapon.value());
                std::cout << "picked up weapon!" << std::endl;
                eventos.push_back(std::make_shared<EventoPickup>(id, spawnPlace.position.x, spawnPlace.position.y, weapon->get_type()));
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
        std::cout << is_on_ground << is_standing_on_something << std::endl;
        return is_on_ground || is_standing_on_something;
    }

    bool has_weapon() const {
        return weapon != nullptr;
    }

    void reload() const {
        if(has_weapon()){
            weapon->reload();
        }
    }

    int get_id(){return id;} // para ver noamas

    virtual ~Player() {}
    Player(Vector initialPosition, int id) : Collidable(initialPosition, 10.0f, 20.0f), velocity(Vector(0,0)), speed(3.0f), is_on_ground(false), is_standing_on_something(false), shooting(false), id(id), direccion_mirada(Vector(0, 0)), weapon(nullptr) {}

};
#endif