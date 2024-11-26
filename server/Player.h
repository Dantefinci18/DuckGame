#ifndef PLAYER_H
#define PLAYER_H

#include "Vector.h"
#include "Collidable.h"
#include "Platform.h"
#include "SpawnPlace.h"
#include "SpawnWeaponBox.h"
#include "Box.h"
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
    DireccionApuntada direccion_apuntada;
    DireccionApuntada ultima_direccion_horizontal;
    std::unique_ptr<Weapon> weapon;

    void apuntar(DireccionApuntada nueva_direccion) {
        direccion_apuntada = nueva_direccion;
        enviar_direccion_apunte();
    }

    void enviar_direccion_apunte() {
        eventos.push_back(std::make_shared<EventoApuntar>(id, direccion_apuntada));
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


    Vector get_direccion_apuntada() const {
        return obtenerDireccion(direccion_apuntada);
    }

    std::vector<Vector> disparar() {
        if (!weapon) {
            return {};
        }
        shooting = true;
        eventos.push_back(std::make_shared<EventoDisparo>(id));
        return weapon->shoot(position, get_direccion_apuntada(), shooting);
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

    bool esta_disparando(){
        return shooting;
    }

    void apuntar_a_derecha() {
        ultima_direccion_horizontal = DireccionApuntada::APUNTADO_DERECHA;
        apuntar(DireccionApuntada::APUNTADO_DERECHA);
    }

    void apuntar_a_izquierda() {
        ultima_direccion_horizontal = DireccionApuntada::APUNTADO_IZQUIERDA;
        apuntar(DireccionApuntada::APUNTADO_IZQUIERDA);
    }

    void dejar_apuntar_derecha() {
        if (direccion_apuntada == DireccionApuntada::APUNTADO_DERECHA) {
            apuntar(ultima_direccion_horizontal);
        }
    }

    void dejar_apuntar_izquierda() {
        if (direccion_apuntada == DireccionApuntada::APUNTADO_IZQUIERDA) {
            apuntar(ultima_direccion_horizontal);
        }
    }

    void set_x_direction(float x) {
        velocity.x = x;
        if (x > 0) {
            ultima_direccion_horizontal = DireccionApuntada::APUNTADO_DERECHA;
            if (direccion_apuntada != DireccionApuntada::APUNTADO_ARRIBA) {
                apuntar_a_derecha();
            }
        } else if (x < 0) {
            ultima_direccion_horizontal = DireccionApuntada::APUNTADO_IZQUIERDA;
            if (direccion_apuntada != DireccionApuntada::APUNTADO_ARRIBA) {
                apuntar_a_izquierda();
            }
        }
    }

    void apuntar_arriba() {
        if (direccion_apuntada != DireccionApuntada::APUNTADO_ARRIBA) {
            apuntar(DireccionApuntada::APUNTADO_ARRIBA);
        }
    }

    void dejar_apuntar_arriba() {
        apuntar(ultima_direccion_horizontal);
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

        if (top() < 0) {
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

        if (other.getType() == CollidableType::Box) {
            Box& box = static_cast<Box&>(other);
            if (box.esta_activa()) {
                CollidableSide side = getCollisionSide(box);
                if (side == CollidableSide::Top) {
                    position.y = box.top();
                    velocity.y = 0;
                    is_standing_on_something = true;
                    return true;
                } else if (side == CollidableSide::Bottom) {
                    position.y = box.bottom() - height;
                    velocity.y = gravity;
                    return true;
                } else if (side == CollidableSide::Left || side == CollidableSide::Right) {
                    velocity.x = 0;
                    return true;
                }
            }
            
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
                eventos.push_back(std::make_shared<EventoPickup>(id, spawnPlace.position.x, spawnPlace.position.y, weapon->get_type()));
            }
        }

        if (other.getType() == CollidableType::SpawnWeaponBox) {
            SpawnWeaponBox& spawnWeaponBox = static_cast<SpawnWeaponBox&>(other);
            CollidableSide side = getCollisionSide(spawnWeaponBox);
            if (side == CollidableSide::None) {
                return false;
            }
            std::optional<std::unique_ptr<Weapon>> new_weapon = spawnWeaponBox.get_weapon();
            if (new_weapon) {
                weapon = std::move(new_weapon.value());
                eventos.push_back(std::make_shared<EventoPickup>(id, spawnWeaponBox.position.x, spawnWeaponBox.position.y, weapon->get_type()));
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
        std::cout << "Player position (" << position.x << ", " << position.y << ")\n";
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

    bool is_agachado() {
        return esta_agachado;
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
        weapon = nullptr;
        ticks_to_reset_gravity = 0;
        shooting = false;
        position = {200.0f, 300.0f};
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
          direccion_apuntada(DireccionApuntada::APUNTADO_DERECHA),
          ultima_direccion_horizontal(DireccionApuntada::APUNTADO_DERECHA),
          weapon(nullptr) {}
};

#endif
