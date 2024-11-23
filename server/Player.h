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
    bool shooting;
    int jump_force;
    int id;
    int gravity;
    int ticks_to_reset_gravity;
    ColorDuck color;
    bool is_dead;
    bool esta_agachado;
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

    if (esta_agachado) {
        velocity.x = 0;  
        
    }

    if (velocity.y > gravity && jump_force == 0) {
        velocity.y -= 1;
    }
    if (jump_force > 0) {
        jump_force--;
        velocity.y += 1;
    }
    if (velocity.y < gravity) {
        velocity.y = gravity;
    }
    
    position.y += velocity.y;
    position.x += velocity.x * speed;  
}


    Vector get_direccion_mirada() const {
        return direccion_mirada;
    }

    std::vector<Vector> disparar() {
        if (!weapon) {
            return {};
        }
        shooting = true;
        std::cout << "Disparó el pato id " << id << std::endl;
        eventos.push_back(std::make_shared<EventoDisparo>(id));
        return weapon->shoot(position, direccion_mirada, shooting);
    }

    void morir() {
        eventos.push_back(std::make_shared<EventoMuerte>(id));
        is_dead = true;
    }

    void dejar_disparar() {
        if (shooting) {
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
        if (esta_agachado) {
            return;
        }

        if (is_able_to_jump()) {
            is_on_ground = false;
            jump_force = 15;
        } else {
            gravity = -2;
            ticks_to_reset_gravity = 5;
    }
}


    bool is_duck_dead() {
        return is_dead;
    }

    virtual void update(std::vector<Collidable*> others) override {
        if (is_duck_dead()) {
            return;
        }
        if (ticks_to_reset_gravity > 0) {
            --ticks_to_reset_gravity;
        }
        if (ticks_to_reset_gravity == 0) {
            gravity = -8;
        }
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
            eventos.push_back(std::make_shared<EventoMovimiento>(id, color, position.x, position.y, is_flapping(), false));
        }

        if(top() < 0) {
            morir();
        }
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
            } else if (side == CollidableSide::Bottom) {
                position.y = platform.bottom() - height;
                velocity.y = gravity;
                return true;
            } else if (side == CollidableSide::Left || side == CollidableSide::Right) {
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
                  << "left: " << std::to_string(left()) << ", "
                  << "right: " << std::to_string(right()) << ", "
                  << "top: " << std::to_string(top()) << ", "
                  << "bottom: " << std::to_string(bottom()) << std::endl;
    }

    void print_position() const override {
        std::cout << "Player position" << "(" << position.x << ", " << position.y << ")\n";
    }

    Vector get_posicion() {
        return position;
    }

    bool is_able_to_jump() {
        return is_on_ground || is_standing_on_something;
    }

    void agacharse() {
        if (is_standing_on_something && !esta_agachado) {
            esta_agachado = true;
            eventos.push_back(std::make_shared<EventoAgacharse>(id));
    }
}


    void levantarse() {
        if (esta_agachado) {
            esta_agachado = false;
            eventos.push_back(std::make_shared<EventoLevantarse>(id));
        }
    }

    void reset() {
        gravity = -8;
        velocity = Vector(0,0);
        is_on_ground = false;
        is_standing_on_something = false;
        jump_force = 0;
        is_dead = false; 
        esta_agachado = false;
        direccion_mirada = Vector(0, 0); 
        weapon = nullptr;
        ticks_to_reset_gravity = 0;
        shooting = false;
        eventos.push_back(std::make_shared<EventoMovimiento>(id, color, position.x, position.y, is_flapping(), true));
        
    }
    bool has_weapon() const {
        return weapon != nullptr;
    }

    bool is_flapping() {
        return velocity.y == gravity && ticks_to_reset_gravity > 0;
    }

    void reload() const {
        if (has_weapon()) {
            weapon->reload();
        }
    }

    int get_id() { return id; }

    virtual ~Player() {}

    Player(int id, ColorDuck color)
        : Collidable({200.0f,300.0f}, 32.0f, 64.0f), 
          velocity(Vector(0, 0)), 
          speed(6.0f), 
          is_on_ground(false), 
          is_standing_on_something(false), 
          shooting(false), 
          jump_force(0), 
          id(id), 
          gravity(-8),
          ticks_to_reset_gravity(0),
          color(color), 
          is_dead(false), 
          esta_agachado(false),
          direccion_mirada(Vector(0, 0)), 
          weapon(nullptr) {}
};

#endif
