#ifndef SPAWN_BOX_H
#define SPAWN_BOX_H

#include <iostream>
#include <memory>
#include <optional>
#include <variant>
#include <random>
#include "../common_weapon_utils.h"
#include "../common_proteccion.h"
#include "Collidable.h"

class SpawnBox : public Collidable {
public:
    enum class State { Appeared };
    enum class ItemType { Weapon, Proteccion, None };

    SpawnBox(Vector position, float width, float height);

    virtual CollidableType getType() const override;
    virtual bool onCollision(Collidable& other) override;
    virtual void print_bounding_box() const override;
    virtual void print_position() const override;
    virtual void update(std::vector<Collidable*> others) override;
    virtual ~SpawnBox();

    void generar_item_aleatorio();
    std::optional<std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>>> recoger_item();
    void set_item(std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>> nuevo_item);
    void limpiar_item();
    bool tiene_item() const;
    ItemType get_item_type() const;
    WeaponType get_weapon_type() const;
    ProteccionType get_proteccion_type() const;
    void imprimir_estado() const;

private:
    State state;
    std::optional<std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>>> item;

    std::unique_ptr<Weapon> generar_arma();
    std::unique_ptr<Proteccion> generar_proteccion();
};

#endif