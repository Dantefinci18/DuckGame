#ifndef SPAWN_WEAPON_BOX_H
#define SPAWN_WEAPON_BOX_H

#include "Collidable.h"
#include "../common/common_evento.h"
#include "../common/common_weapon_utils.h"
#include <optional>
#include <memory>
#include <iostream>
#include <random>  

class SpawnWeaponBox : public Collidable {
public:
    std::vector<std::shared_ptr<Evento>> eventos;

    enum class State { Appeared };
    
    SpawnWeaponBox(Vector position, float width, float height) : 
        Collidable(position, width, height), 
        state(State::Appeared) {

        weapon = std::unique_ptr<Weapon>(elegir_arma_aleatoria());
    }

    std::unique_ptr<Weapon> elegir_arma_aleatoria() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 3);

        WeaponType tipo_arma = static_cast<WeaponType>(dist(gen));
        return WeaponUtils::create_weapon(tipo_arma);
    }

    virtual CollidableType getType() const override {
        return CollidableType::SpawnWeaponBox;
    }

    virtual bool onCollision([[maybe_unused]] Collidable& other) override {
        return false;
    }

    virtual ~SpawnWeaponBox() {}

    void print_bounding_box() const override {
        std::cout << "SpawnWeaponBox box: (" 
            << "left: " << std::to_string(left()) << ", "
            << "right: " << std::to_string(right()) << ", "
            << "top: " << std::to_string(top()) << ", "
            << "bottom: " << std::to_string(bottom()) << std::endl;
    }
    void print_position() const override {
        std::cout << "SpawnWeaponBox position" << "(" << position.x << ", " << position.y << ")\n";
    }

    virtual void update([[maybe_unused]] std::vector<Collidable*> others) override {
    }

    virtual std::optional<std::unique_ptr<Weapon>> get_weapon() {
        if (state == State::Appeared && weapon) {
            std::cout << "Weapon picked!" << std::endl;
            std::unique_ptr<Weapon> picked_weapon = std::move(weapon);  
            weapon.reset(); 
            return picked_weapon;
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
        return weapon ? weapon->get_type() : WeaponType::None;
    }

    virtual bool has_weapon() {
        return weapon != nullptr;
    }

private:
    State state;  
    std::unique_ptr<Weapon> weapon; 
};

#endif
