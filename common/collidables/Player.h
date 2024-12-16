#ifndef PLAYER_H
#define PLAYER_H

#include "../../server/Vector.h"
#include "Collidable.h"
#include "Platform.h"
#include "SpawnPlace.h"
#include "SpawnWeaponBox.h"
#include "SpawnBox.h"
#include "Box.h"

#include "../weapons/Weapon.h"
#include "../common_evento.h"
#include "../common_color.h"

#include <iostream>
#include <optional>
#include <memory>
#include <vector>

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
    std::unique_ptr<Proteccion> casco;
    std::unique_ptr<Proteccion> armadura;

    void apuntar(DireccionApuntada nueva_direccion);
    void enviar_direccion_apunte();

public:
    std::vector<std::shared_ptr<Evento>> eventos;

    Player(int id, ColorDuck color);

    void move();
    Vector get_direccion_apuntada() const;
    Vector get_posicion_arma() const;
    std::vector<Vector> disparar();
    void recibir_disparo();
    void morir();
    void iniciar_disparo();
    void dejar_disparar();
    bool esta_disparando() const;
    void apuntar_a_derecha();
    void apuntar_a_izquierda();
    void dejar_apuntar_derecha();
    void dejar_apuntar_izquierda();
    void set_x_direction(float x);
    void apuntar_arriba();
    void dejar_apuntar_arriba();
    void jump();
    bool is_duck_dead();

    virtual void update(std::vector<Collidable*> others) override;
    virtual CollidableType getType() const override;
    virtual bool onCollision(Collidable& other) override;
    void print_bounding_box() const override;
    void print_position() const override;

    Vector get_posicion();
    bool is_able_to_jump();
    void agacharse();
    bool is_agachado();
    bool is_flapping();
    bool has_weapon() const;
    void reload() const;
    int get_id();
    void levantarse();
    void reset();
};

#endif // PLAYER_H
