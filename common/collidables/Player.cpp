#include "Player.h"

void Player::apuntar(DireccionApuntada nueva_direccion) {
    direccion_apuntada = nueva_direccion;
    enviar_direccion_apunte();
}

void Player::enviar_direccion_apunte() {
    eventos.push_back(std::make_shared<EventoApuntar>(id, direccion_apuntada));
}

void Player::move() {
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

Vector Player::get_direccion_apuntada() const {
    return obtenerDireccion(direccion_apuntada);
}

Vector Player::get_posicion_arma() const {
    return position + Vector(0, 15);
}

std::vector<Vector> Player::disparar() {
    if (!weapon) {
        return {};
    }
    bool tiene_retroceso = false;
    auto destinos = weapon->shoot(get_posicion_arma(), get_direccion_apuntada(), tiene_retroceso);
    if (!weapon->es_automatica()) {
        shooting = false;
    }
    return destinos;
}

void Player::recibir_disparo() {
    if (casco && casco->en_condiciones()) {
        casco->impactar();
        casco = nullptr;
        eventos.push_back(std::make_shared<EventoPickupProteccion>(id, position.x, position.y, ProteccionType::NoCasco));
    } else if (armadura && armadura->en_condiciones()) {
        armadura->impactar();
        armadura = nullptr;
        eventos.push_back(std::make_shared<EventoPickupProteccion>(id, position.x, position.y, ProteccionType::NoArmadura));
    } else {
        morir();
    }
}

void Player::morir() {
    eventos.push_back(std::make_shared<EventoMuerte>(id));
    is_dead = true;
}

void Player::iniciar_disparo() {
    if (!weapon) {
        return;
    }
    shooting = true;
}

void Player::dejar_disparar() {
    if (shooting) {
        shooting = false;
    }
}

bool Player::esta_disparando() const {
    return shooting;
}

void Player::apuntar_a_derecha() {
    ultima_direccion_horizontal = DireccionApuntada::APUNTADO_DERECHA;
    apuntar(DireccionApuntada::APUNTADO_DERECHA);
}

void Player::apuntar_a_izquierda() {
    ultima_direccion_horizontal = DireccionApuntada::APUNTADO_IZQUIERDA;
    apuntar(DireccionApuntada::APUNTADO_IZQUIERDA);
}

void Player::dejar_apuntar_derecha() {
    if (direccion_apuntada == DireccionApuntada::APUNTADO_DERECHA) {
        apuntar(ultima_direccion_horizontal);
    }
}

void Player::dejar_apuntar_izquierda() {
    if (direccion_apuntada == DireccionApuntada::APUNTADO_IZQUIERDA) {
        apuntar(ultima_direccion_horizontal);
    }
}

void Player::set_x_direction(float x) {
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

void Player::apuntar_arriba() {
    if (direccion_apuntada != DireccionApuntada::APUNTADO_ARRIBA) {
        apuntar(DireccionApuntada::APUNTADO_ARRIBA);
    }
}

void Player::dejar_apuntar_arriba() {
    apuntar(ultima_direccion_horizontal);
}

void Player::jump() {
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

bool Player::is_duck_dead() {
    return is_dead;
}

void Player::update(std::vector<Collidable*> others) {
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

CollidableType Player::getType() const {
    return CollidableType::Player;
}

bool Player::onCollision(Collidable& other) {
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


    if (other.getType() == CollidableType::SpawnBox) {
        SpawnBox& spawnBox = static_cast<SpawnBox&>(other);
        CollidableSide side = getCollisionSide(spawnBox);

        // Verificar si hay colisión válida
        if (side == CollidableSide::None) {
            return false;
        }

        // Obtener el tipo de ítem de la caja
        auto item_type = spawnBox.get_item_type();

        switch (item_type) {
            case SpawnBox::ItemType::Weapon: {
                // Obtener y asignar el arma al jugador
                WeaponType weapon_type = spawnBox.get_weapon_type();
                auto new_item = spawnBox.recoger_item();
                if (new_item && std::holds_alternative<std::unique_ptr<Weapon>>(new_item.value())) {
                    weapon = std::move(std::get<std::unique_ptr<Weapon>>(new_item.value()));
                    eventos.push_back(std::make_shared<EventoPickup>(id, spawnBox.position.x, spawnBox.position.y, weapon_type));
                }
                break;
            }
            case SpawnBox::ItemType::Proteccion: {
                ProteccionType proteccion_type = spawnBox.get_proteccion_type();
                auto new_item = spawnBox.recoger_item();

                if (new_item && std::holds_alternative<std::unique_ptr<Proteccion>>(new_item.value())) {
                    auto proteccion = std::move(std::get<std::unique_ptr<Proteccion>>(new_item.value()));

                    if (proteccion_type == ProteccionType::Casco) {
                        casco = std::move(proteccion);
                        eventos.push_back(std::make_shared<EventoPickupProteccion>(id, spawnBox.position.x, spawnBox.position.y, ProteccionType::Casco));
                    } else if (proteccion_type == ProteccionType::Armadura) {
                        armadura = std::move(proteccion);
                        eventos.push_back(std::make_shared<EventoPickupProteccion>(id, spawnBox.position.x, spawnBox.position.y, ProteccionType::Armadura));
                    }
                }
                break;
            }
            case SpawnBox::ItemType::None:
                break;
        }
    }

    return false;
}



void Player::print_bounding_box() const {
    std::cout << "Bounding Box: (" << position.x << ", " << position.y << ", " << width << ", " << height << ")\n";
}

void Player::print_position() const {
    std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
}

Vector Player::get_posicion() {
    return position;
}

bool Player::is_able_to_jump() {
    return is_standing_on_something;
}

void Player::agacharse() {
    if (is_standing_on_something && !esta_agachado) {
        esta_agachado = true;
        eventos.push_back(std::make_shared<EventoAgacharse>(id));
    }
    }   

bool Player::is_agachado() {
    return esta_agachado;
}

bool Player::has_weapon() const {
    return weapon != nullptr;
}

void Player::reload() const {
    if (has_weapon()) {
        weapon->reload();
    }
}

int Player::get_id() {
    return id;
}

bool Player::is_flapping() {
    return velocity.y == gravity && ticks_to_reset_gravity > 0;
}

void Player::levantarse() {
        if (esta_agachado) {
            esta_agachado = false;
            eventos.push_back(std::make_shared<EventoLevantarse>(id));
        }
    }
    
void Player::reset() {
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
    casco = nullptr;
    armadura = nullptr;
    eventos.push_back(std::make_shared<EventoMovimiento>(id, color, position.x, position.y, is_flapping(), true));
}

Player::Player(int id, ColorDuck color)
        : Collidable({200.0f,300.0f}, 32.0f, 48.0f), 
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
          weapon(nullptr),
          casco(nullptr),
          armadura(nullptr) {}
