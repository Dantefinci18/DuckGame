#include "SpawnBox.h"

SpawnBox::SpawnBox(Vector position, float width, float height)
    : Collidable(position, width, height), state(State::Appeared) {
    generar_item_aleatorio();
}

CollidableType SpawnBox::getType() const {
    return CollidableType::SpawnBox;
}

bool SpawnBox::onCollision([[maybe_unused]] Collidable& other) {
    return false;
}

void SpawnBox::print_bounding_box() const {
    std::cout << "Bounding Box: (" << left() << ", " << top() << ") - (" 
              << right() << ", " << bottom() << ")\n";
}

void SpawnBox::print_position() const {
    std::cout << "SpawnBox Position: (" << position.x << ", " << position.y << ")\n";
}

void SpawnBox::update([[maybe_unused]] std::vector<Collidable*> others) {
    // Update logic for SpawnBox, if needed
}

SpawnBox::~SpawnBox() {}

void SpawnBox::generar_item_aleatorio() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1); // 0: Weapon, 1: Proteccion

    if (dist(gen) == 0) {
        item = generar_arma();
    } else {
        item = generar_proteccion();
    }
}

std::optional<std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>>> SpawnBox::recoger_item() {
    if (state == State::Appeared && item) {
        auto contenido = std::move(item);
        item.reset();
        return contenido;
    }
    return std::nullopt;
}

void SpawnBox::set_item(std::variant<std::unique_ptr<Weapon>, std::unique_ptr<Proteccion>> nuevo_item) {
    limpiar_item();
    item = std::move(nuevo_item);
}

void SpawnBox::limpiar_item() {
    item.reset();
}

bool SpawnBox::tiene_item() const {
    return item.has_value();
}

SpawnBox::ItemType SpawnBox::get_item_type() const {
    if (!item) {
        return ItemType::None;
    }

    if (std::holds_alternative<std::unique_ptr<Weapon>>(item.value())) {
        return ItemType::Weapon;
    } else if (std::holds_alternative<std::unique_ptr<Proteccion>>(item.value())) {
        return ItemType::Proteccion;
    }
    return ItemType::None;
}

WeaponType SpawnBox::get_weapon_type() const {
    if (item && std::holds_alternative<std::unique_ptr<Weapon>>(item.value())) {
        const auto& weapon = std::get<std::unique_ptr<Weapon>>(item.value());
        return weapon ? weapon->get_type() : WeaponType::None;
    }
    return WeaponType::None;
}

ProteccionType SpawnBox::get_proteccion_type() const {
    if (item && std::holds_alternative<std::unique_ptr<Proteccion>>(item.value())) {
        const auto& proteccion = std::get<std::unique_ptr<Proteccion>>(item.value());
        return proteccion ? proteccion->get_type() : ProteccionType::None;
    }
    return ProteccionType::None;
}

void SpawnBox::imprimir_estado() const {
    if (!tiene_item()) {
        std::cout << "\033[43;31m(SPAWNBOX) - La caja está vacía\033[0m" << std::endl;
        return;
    }

    auto tipo = get_item_type();
    switch (tipo) {
        case ItemType::Weapon:
            std::cout << "\033[43;31m(SPAWNBOX) - La caja tiene un arma\033[0m" << std::endl;
            break;
        case ItemType::Proteccion:
            std::cout << "\033[43;31m(SPAWNBOX) - La caja tiene una protección\033[0m" << std::endl;
            break;
        case ItemType::None:
            std::cout << "\033[43;31m(SPAWNBOX) - La caja está vacía por caso None\033[0m" << std::endl;
            break;
    }
}

std::unique_ptr<Weapon> SpawnBox::generar_arma() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4); // Número de tipos de armas

    WeaponType tipo_arma = static_cast<WeaponType>(dist(gen));
    return WeaponUtils::create_weapon(tipo_arma);
}

std::unique_ptr<Proteccion> SpawnBox::generar_proteccion() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1); // 0: Casco, 1: Armadura

    ProteccionType tipo_proteccion = static_cast<ProteccionType>(dist(gen));
    return std::make_unique<Proteccion>(tipo_proteccion);
}
