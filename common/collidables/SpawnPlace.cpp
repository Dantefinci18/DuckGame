#include "SpawnPlace.h"

SpawnPlace::SpawnPlace(Vector position, float width, float height)
    : Collidable(position, width, height),
      min_server_ticks(50), countdown(50), state(State::Spawned) {
    weapon = std::make_unique<PistolaCowboy>();
}

CollidableType SpawnPlace::getType() const {
    return CollidableType::SpawnPlace;
}

bool SpawnPlace::onCollision([[maybe_unused]] Collidable& other) {
    return false;
}

void SpawnPlace::print_bounding_box() const {
    std::cout << "SpawnPlace box: ("
              << "left: " << std::to_string(left()) << ", "
              << "right: " << std::to_string(right()) << ", "
              << "top: " << std::to_string(top()) << ", "
              << "bottom: " << std::to_string(bottom()) << std::endl;
}

void SpawnPlace::print_position() const {
    std::cout << "SpawnPlace position" << "(" << position.x << ", " << position.y << ")\n";
}

void SpawnPlace::update([[maybe_unused]] std::vector<Collidable*> others) {
    if (state == State::Respawning) {
        if (countdown > 0) {
            --countdown;
        }

        if (countdown <= 0) {
            std::cout << "Spawned weapon!" << std::endl;
            state = State::Spawned;
            countdown = min_server_ticks + get_random_number();
            weapon = elegir_arma_aleatoria();
            eventos.push_back(std::make_shared<EventoSpawnArma>(position.x, position.y, weapon.get()->get_type()));
        }
    }
}

std::unique_ptr<Weapon> SpawnPlace::elegir_arma_aleatoria() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4);

    WeaponType tipo_arma = static_cast<WeaponType>(dist(gen));
    return WeaponUtils::create_weapon(tipo_arma);
}

std::optional<std::unique_ptr<Weapon>> SpawnPlace::get_weapon() {
    if (state == State::Spawned && weapon) {
        state = State::Respawning; // Mark as respawning
        countdown = min_server_ticks + get_random_number();
        return std::move(weapon); // Transfer ownership of the weapon
    }
    return std::nullopt; // Return empty optional if no weapon is present
}

void SpawnPlace::set_weapon(std::unique_ptr<Weapon> set_weapon) {
    weapon = std::move(set_weapon);
}

void SpawnPlace::clear_weapon() {
    weapon.reset();
}

WeaponType SpawnPlace::get_weapon_type() {
    return weapon.get()->get_type();
}

bool SpawnPlace::has_weapon() {
    return weapon != nullptr;
}

int SpawnPlace::get_random_number() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 40);

    return distribution(generator);
}
