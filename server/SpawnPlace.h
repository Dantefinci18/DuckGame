#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

#include "Collidable.h"
#include "../common/common_pistola_cowboy.h"
#include "../common/common_pistola_magnum.h"
#include "../common/common_pistola_duelos.h"
#include "../common/common_rifle_ak47.h"
#include "../common/common_evento.h"
#include <optional>
#include <random>
#include <memory>
#include <iostream>

class SpawnPlace : public Collidable {
public:
    std::vector<std::shared_ptr<Evento>> eventos;
    enum class State { Spawned, Respawning };

    SpawnPlace(Vector position, float width, float height)
        : Collidable(position, width, height),
          min_server_ticks(50),
          countdown(50),
          state(State::Spawned),
          weapon(crear_arma_aleatoria()) {}

    virtual CollidableType getType() const override {
        return CollidableType::SpawnPlace;
    }

    virtual bool onCollision([[maybe_unused]] Collidable& other) override {
        return false;
    }

    virtual ~SpawnPlace() {}

    void print_bounding_box() const override {
        std::cout << "SpawnPlace box: ("
                  << "left: " << std::to_string(left()) << ", "
                  << "right: " << std::to_string(right()) << ", "
                  << "top: " << std::to_string(top()) << ", "
                  << "bottom: " << std::to_string(bottom()) << ")\n";
    }

    void print_position() const override {
        std::cout << "SpawnPlace position (" << position.x << ", " << position.y << ")\n";
    }

    virtual void update([[maybe_unused]] std::vector<Collidable*> others) override {
        if (state == State::Respawning) {
            if (countdown > 0) {
                --countdown;
            }

            if (countdown <= 0) {
                std::cout << "Spawned weapon!" << std::endl;
                state = State::Spawned;
                countdown = min_server_ticks + get_random_number();

                weapon = crear_arma_aleatoria();

                eventos.push_back(std::make_shared<EventoSpawnArma>(
                    position.x, position.y, weapon->get_type()));
            }
        }
    }

    virtual std::optional<std::unique_ptr<Weapon>> get_weapon() {
        if (state == State::Spawned && weapon) {
            state = State::Respawning;
            countdown = min_server_ticks + get_random_number();
            return std::move(weapon);
        }
        return std::nullopt;
    }

    virtual void set_weapon(std::unique_ptr<Weapon> set_weapon) {
        weapon = std::move(set_weapon);
    }

    virtual void clear_weapon() {
        weapon.reset();
    }

    virtual WeaponType get_weapon_type() {
        return weapon->get_type();
    }

    virtual bool has_weapon() {
        return static_cast<bool>(weapon);
    }

private:
    int min_server_ticks;
    int countdown;
    State state;
    std::unique_ptr<Weapon> weapon;

    int get_random_number() {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, 40);
        return distribution(generator);
    }

    std::unique_ptr<Weapon> crear_arma_aleatoria() {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, 3); // agregar rango cuando agregue armas
        int random_index = distribution(generator);
        switch (random_index) {
            case 0: return std::make_unique<PistolaCowboy>();
            case 1: return std::make_unique<PistolaMagnum>();
            case 2: return std::make_unique<PistolaDuelos>();
            case 3: return std::make_unique<RifleAK47>();
            default: return std::make_unique<PistolaDuelos>(); 
        }
    }
};
#endif