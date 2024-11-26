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
#include <memory>
class SpawnPlace : public Collidable {
    
    public:
    std::vector<std::shared_ptr<Evento>> eventos;
    enum class State {Spawned, Respawning};
    SpawnPlace(Vector position, float width, float height) : Collidable(position, width, height), 
        min_server_ticks(50), countdown(50), state(State::Spawned), weapon(std::make_unique<PistolaCowboy>()) {}

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
        if (state == State::Respawning) {
            if (countdown > 0) {
                --countdown;
            }

            if (countdown <= 0) {
                std::cout << "Spawned weapon!" << std::endl;
                state = State::Spawned;
                countdown = min_server_ticks + get_random_number();
                weapon = std::make_unique<PistolaCowboy>();
                eventos.push_back(std::make_shared<EventoSpawnArma>(position.x, position.y, weapon.get()->get_type()));
            }
        }
    }

    virtual std::optional<std::unique_ptr<Weapon>> get_weapon() {
        if (state == State::Spawned && weapon) {
            state = State::Respawning; // Mark as respawning
            countdown = min_server_ticks + get_random_number();
            return std::move(weapon); // Transfer ownership of the weapon
        }
        return std::nullopt; // Return empty optional if no weapon is present
    }

    virtual void set_weapon(std::unique_ptr<Weapon> set_weapon) {
        weapon = std::move(set_weapon);
    }

    virtual void clear_weapon() {
        weapon.reset();
    }

    virtual WeaponType get_weapon_type() {
        return weapon.get()->get_type();
    }

    virtual bool has_weapon() {
        if (weapon) {
            return true;
        }
        return false;
    }

    int get_random_number() {
        std::random_device rd; 

        // Create a Mersenne Twister generator
        std::mt19937 generator(rd()); 

        // Define a uniform integer distribution for the range [0, 100]
        std::uniform_int_distribution<int> distribution(0, 40); 

        // Generate a random number in the range
        return distribution(generator);
    }

    private:
    int min_server_ticks;
    int countdown;
    State state;
    std::unique_ptr<Weapon> weapon;
};
#endif
