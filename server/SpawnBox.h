#ifndef SPAWN_BOX_H
#define SPAWN_BOX_H

#include <iostream>
#include <memory>
#include <optional>
#include <variant>
#include <random>
#include "../common/common_weapon_utils.h"
#include "../common/common_proteccion.h"
#include "Collidable.h"

class SpawnBox : public Collidable {
public:
    enum class State { Appeared }; // Estado de la caja
    enum class ItemType { Weapon, Proteccion, None }; // Tipos posibles de ítems

    // Constructor
    SpawnBox(Vector position, float width, float height)
        : Collidable(position, width, height), state(State::Appeared) {
        generar_item_aleatorio();
    }

    // Devuelve el tipo de colisionable
    virtual CollidableType getType() const override {
        return CollidableType::SpawnBox;
    }

    // Lógica de colisión (vacía por ahora)
    virtual bool onCollision([[maybe_unused]] Collidable& other) override {
        return false;
    }

    // Implementación de los métodos virtuales puros
    virtual void print_bounding_box() const override {
        std::cout << "Bounding Box: (" << left() << ", " << top() << ") - (" 
                  << right() << ", " << bottom() << ")\n";
    }

    virtual void print_position() const override {
        std::cout << "SpawnBox Position: (" << position.x << ", " << position.y << ")\n";
    }

    virtual void update([[maybe_unused]] std::vector<Collidable*> others) override {
        // No realiza ninguna acción específica en la actualización
    }

    // Destructor virtual
    virtual ~SpawnBox() {}

    // Genera aleatoriamente un arma o una protección
    void generar_item_aleatorio() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1); // 0: Weapon, 1: Proteccion

        if (dist(gen) == 0) {
            item = generar_arma();
        } else {
            item = generar_proteccion();
        }
    }

    // Retorna el ítem de la caja, moviéndolo fuera
    std::optional<std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>>> recoger_item() {
        if (state == State::Appeared && item) {
            auto contenido = std::move(item);
            item.reset();
            return contenido;
        }
        return std::nullopt;
    }

    // Establece un ítem nuevo en la caja
    void set_item(std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>> nuevo_item) {
        limpiar_item();
        item = std::move(nuevo_item);
    }

    // Limpia el contenido de la caja
    void limpiar_item() {
        item.reset();
    }

    // Verifica si la caja tiene algún ítem
    bool tiene_item() const {
        return item.has_value();
    }

    // Devuelve el tipo del ítem actual (arma, protección, o vacío)
    ItemType get_item_type() const {
        if (!item) {
            return ItemType::None; // La caja está vacía
        }

        if (std::holds_alternative<std::unique_ptr<Weapon>>(item.value())) {
            return ItemType::Weapon; // Contiene un arma
        } else if (std::holds_alternative<std::unique_ptr<Proteccion>>(item.value())) {
            return ItemType::Proteccion; // Contiene una protección
        }

        return ItemType::None; // Caso por defecto (no debería suceder)
    }

    // Devuelve el tipo de arma en la caja (o None si no es un arma)
    WeaponType get_weapon_type() const {
        if (item && std::holds_alternative<std::unique_ptr<Weapon>>(item.value())) {
            const auto& weapon = std::get<std::unique_ptr<Weapon>>(item.value());
            return weapon ? weapon->get_type() : WeaponType::None;
        }
        return WeaponType::None; // No hay arma
    }

    // Devuelve el tipo de protección en la caja (o None si no es una protección)
    ProteccionType get_proteccion_type() const {
        if (item && std::holds_alternative<std::unique_ptr<Proteccion>>(item.value())) {
            const auto& proteccion = std::get<std::unique_ptr<Proteccion>>(item.value());
            return proteccion ? proteccion->get_type() : ProteccionType::None;
        }
        return ProteccionType::None; // No hay protección
    }

    // Imprime el estado de la caja (para debugging)
    void imprimir_estado() const {
        if (!tiene_item()) {
            std::cout << "La caja está vacía" << std::endl;
            return;
        }

        auto tipo = get_item_type();
        switch (tipo) {
            case ItemType::Weapon:
                std::cout << "La caja contiene un arma.\n";
                break;
            case ItemType::Proteccion:
                std::cout << "La caja contiene una protección.\n";
                break;
            case ItemType::None:
                std::cout << "Error: Caja en estado inesperado.\n";
                break;
        }
    }

private:
    State state; // Estado de la caja
    std::optional<std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>>> item; // Contenido de la caja

    // Genera un arma aleatoria
    std::unique_ptr<Weapon> generar_arma() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 3); // Número de tipos de armas

        WeaponType tipo_arma = static_cast<WeaponType>(dist(gen));
        return WeaponUtils::create_weapon(tipo_arma);
    }

    // Genera una protección aleatoria
    std::unique_ptr<Proteccion> generar_proteccion() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1); // 0: Casco, 1: Armadura

        ProteccionType tipo_proteccion = static_cast<ProteccionType>(dist(gen));
        return std::make_unique<Proteccion>(tipo_proteccion);
    }
};

#endif
