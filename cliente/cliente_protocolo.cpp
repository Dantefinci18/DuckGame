#include "cliente_protocolo.h"
#include <ostream>
#include <bitset>
#include <iostream>
#include <cstring>
#include <memory> 


ClienteProtocolo::ClienteProtocolo(Socket&& socket) : socket(std::move(socket)) {}


bool ClienteProtocolo::enviar_accion(ComandoAccion &accion) {
    bool was_closed = false;

    std::vector<uint8_t> buffer= serializador.serializar_accion(accion);

    socket.sendall(buffer.data(), buffer.size(), &was_closed);

    return !was_closed;  
}

int ClienteProtocolo::recibir_id() {
    bool was_closed = false;
    uint8_t data[32];
    socket.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        return -1;
    }
    return serializador.deserializar_id(data);
}

std::unique_ptr<Evento> ClienteProtocolo::recibir_evento() {
    bool was_closed = false;

    uint8_t tipo_evento[8];
    socket.recvall(tipo_evento, sizeof(tipo_evento), &was_closed);
    if (was_closed) {
        return nullptr;
    }

    Evento::TipoEvento tipo = serializador.deserializar_tipo_evento(tipo_evento);

    switch (tipo) {
        case Evento::EventoMovimiento: {
            uint8_t x[32];
            socket.recvall(x, sizeof(x), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t y[32];
            socket.recvall(y, sizeof(y), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t color[8];
            socket.recvall(color, sizeof(color), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            char is_flapping;
            socket.recvall(&is_flapping, sizeof(is_flapping), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            char reset;
            socket.recvall(&reset, sizeof(reset), &was_closed);
            if (was_closed) {
                return nullptr;
            }
            return serializador.deserializar_movimiento(id,color,x, y, is_flapping, reset);
        }
        case Evento::EventoMapa: {
            uint8_t cantidad[32];
            socket.recvall(cantidad, sizeof(cantidad), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            int cantidad_collidables = serializador.deserializar_cantidad(cantidad);
            std::vector<Collidable*> collidables;

            for (int i = 0; i < cantidad_collidables; i++) {
                uint8_t collidable_data[160];
                socket.recvall(collidable_data, sizeof(collidable_data), &was_closed);
                if (was_closed) {
                    return nullptr;
                }

                Collidable* collidable = serializador.deserializar_collidable(collidable_data);
                collidables.push_back(collidable);
            }

            uint8_t basic_leaderboard_fields[64];
            socket.recvall(basic_leaderboard_fields, sizeof(basic_leaderboard_fields), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            auto [round, set_of_rounds] = serializador.deserializar_tuple64(basic_leaderboard_fields);
            uint8_t cantidad_map[32];
            socket.recvall(cantidad_map, sizeof(cantidad_map), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            int cantidad_leaderboard = serializador.deserializar_cantidad(cantidad_map);
            std::unordered_map<int,int> leaderboard;
            for (int i = 0; i < cantidad_leaderboard; i++) {
                uint8_t leaderboard_tuple[64];
                socket.recvall(leaderboard_tuple, sizeof(leaderboard_tuple), &was_closed);
                if (was_closed) {
                    return nullptr;
                }

                auto [player, rounds_won] = serializador.deserializar_tuple64(leaderboard_tuple);
                leaderboard[player] = rounds_won;
            }
            Leaderboard lb(round, set_of_rounds, leaderboard);
            return std::make_unique<EventoMapa>(collidables, lb);
        }
        case Evento::EventoPickup: {
            uint8_t x[32];
            socket.recvall(x, sizeof(x), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t y[32];
            socket.recvall(y, sizeof(y), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t weapon_type[32];
            socket.recvall(weapon_type, sizeof(weapon_type), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_pickup(id, x, y, weapon_type);
        }
        case Evento::EventoSpawnArma: {
            uint8_t x[32];
            socket.recvall(x, sizeof(x), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t y[32];
            socket.recvall(y, sizeof(y), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t weapon_type[32];
            socket.recvall(weapon_type, sizeof(weapon_type), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_spawn_arma(x, y, weapon_type);
        }
        case Evento::EventoDisparo: {
            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_disparo(id);
        }
        case Evento::EventoMuerte: {
            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_muerte(id);
        }
        case Evento::EventoApuntar: {
            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t direccion[8];
            socket.recvall(direccion, sizeof(direccion), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_apuntar(id, direccion);
        }
        case Evento::EventoAgacharse: {
            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            int id_deserializado = serializador.deserializar_id(id);
            return std::make_unique<EventoAgacharse>(id_deserializado);
        }
        case Evento::EventoLevantarse: {
            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            int id_deserializado = serializador.deserializar_id(id);
            return std::make_unique<EventoLevantarse>(id_deserializado);
        }

        case Evento::EventoWinRound: {
            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }
            int id_deserializado = serializador.deserializar_id(id);
            return std::make_unique<EventoWinRound>(id_deserializado);
        }

        case Evento::EventoWinMatch: {
            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                return nullptr;
            }
            int id_deserializado = serializador.deserializar_id(id);
            return std::make_unique<EventoWinMatch>(id_deserializado);
        }

        case Evento::EventoBala: {
            uint8_t x[32];
            socket.recvall(x, sizeof(x), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t y[32];
            socket.recvall(y, sizeof(y), &was_closed);
            if (was_closed) {
                return nullptr;
            }
            return serializador.deserializar_bala(x, y);
        }
        default:
            return nullptr; 
    }
}

std::vector<Collidable*> ClienteProtocolo::recibir_mapa() {
    bool was_closed = false;

    uint8_t cantidad_data[32];
    socket.recvall(cantidad_data, sizeof(cantidad_data), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Conexión cerrada al recibir cantidad de collidables");
    }

    int cantidad = serializador.deserializar_id(cantidad_data);
    std::vector<Collidable*> collidables;

    for (int i = 0; i < cantidad; i++) {
        uint8_t collidable_data[160];
        socket.recvall(collidable_data, sizeof(collidable_data), &was_closed); 
        if (was_closed) {
            throw std::runtime_error("Conexión cerrada al recibir collidable");
        }

        Collidable* collidable = serializador.deserializar_collidable(collidable_data);
        collidables.push_back(collidable);
    }

    return collidables;
}
void ClienteProtocolo::cerrar_conexion() {
    socket.shutdown(2);
    socket.close();
}
