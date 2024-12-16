#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

#include "Collidable.h"
#include "../common_pistola_cowboy.h"
#include "../common_pistola_magnum.h"
#include "../common_pistola_duelos.h"
#include "../common_rifle_ak47.h"
#include "../common_escopeta.h"
#include "../common_evento.h"
#include "../common_weapon_utils.h"
#include <optional>
#include <random>
#include <memory>
#include <iostream>
#include <vector>

class SpawnPlace : public Collidable {
public:
    enum class State { Spawned, Respawning };

    SpawnPlace(Vector position, float width, float height);

    virtual CollidableType getType() const override;
    virtual bool onCollision([[maybe_unused]] Collidable& other) override;
    virtual void print_bounding_box() const override;
    virtual void print_position() const override;
    virtual void update([[maybe_unused]] std::vector<Collidable*> others) override;
    virtual std::unique_ptr<Weapon> elegir_arma_aleatoria();
    virtual std::optional<std::unique_ptr<Weapon>> get_weapon();
    virtual void set_weapon(std::unique_ptr<Weapon> set_weapon);
    virtual void clear_weapon();
    virtual WeaponType get_weapon_type();
    virtual bool has_weapon();

    std::vector<std::shared_ptr<Evento>> eventos;

private:
    int get_random_number();

private:
    int min_server_ticks;
    int countdown;
    State state;
    std::unique_ptr<Weapon> weapon;
    
};

#endif // SPAWN_PLACE_H
