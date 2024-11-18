#include "lobby.h"
#include <utility>
#include <stdexcept>
#include "cliente_protocolo.h"
Lobby::Lobby(const char* hostname, const char* servname) : socket(hostname, servname) {}

void Lobby::crear_partida(const std::string& mapa_seleccionado) {
    bool was_closed = false;
    ComandoAccion comando = ComandoAccion::NUEVA_PARTIDA;
    std::vector<uint8_t> accion_serializada = serializador.serializar_accion(comando);
    socket.sendall(accion_serializada.data(), accion_serializada.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar comando de nueva partida");
    }
    
}

int Lobby::recibir_id() {
    bool was_closed = false;
    uint8_t data[32];
    socket.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        throw std::runtime_error("Error al recibir ID: conexión cerrada");
    }
    return serializador.deserializar_id(data);
}

ColorDuck Lobby::recibir_color() {
    bool was_closed = false;
    uint8_t data[8];
    socket.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        throw std::runtime_error("Error al recibir color: conexión cerrada");
    }
    return serializador.deserializar_color(data);
}

std::unique_ptr<Evento> Lobby::recibir_evento() {
    bool was_closed = false;

    uint8_t tipo_evento[8];
    socket.recvall(tipo_evento, sizeof(tipo_evento), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al recibir el tipo de evento: conexión cerrada");
    }

    Evento::TipoEvento tipo = serializador.deserializar_tipo_evento(tipo_evento);

    switch (tipo) {
        case Evento::EventoMovimiento: {
            uint8_t x[32];
            socket.recvall(x, sizeof(x), &was_closed);
            if (was_closed) {
                throw std::runtime_error("Error al recibir coordenada X en evento de movimiento: conexión cerrada");
            }

            uint8_t y[32];
            socket.recvall(y, sizeof(y), &was_closed);
            if (was_closed) {
                throw std::runtime_error("Error al recibir coordenada Y en evento de movimiento: conexión cerrada");
            }

            uint8_t id[32];
            socket.recvall(id, sizeof(id), &was_closed);
            if (was_closed) {
                throw std::runtime_error("Error al recibir ID en evento de movimiento: conexión cerrada");
            }

            return serializador.deserializar_movimiento(id, x, y);
        }
        case Evento::EventoMapa: {
            uint8_t cantidad[32];
            socket.recvall(cantidad, sizeof(cantidad), &was_closed);
            if (was_closed) {
                throw std::runtime_error("Error al recibir cantidad de collidables en evento de mapa: conexión cerrada");
            }

            int cantidad_collidables = serializador.deserializar_cantidad(cantidad);
            std::vector<Collidable*> collidables;

            for (int i = 0; i < cantidad_collidables; i++) {
                uint8_t collidable_data[160];
                socket.recvall(collidable_data, sizeof(collidable_data), &was_closed);
                if (was_closed) {
                    throw std::runtime_error("Error al recibir datos de collidable en evento de mapa: conexión cerrada");
                }

                Collidable* collidable = serializador.deserializar_collidable(collidable_data);
                collidables.push_back(collidable);
            }
            return std::make_unique<EventoMapa>(collidables);
        }
        default:
            throw std::runtime_error("Error: Tipo de evento desconocido");
            
    }
}



Lobby::~Lobby() {}

Socket Lobby::get_socket() {
    return std::move(socket);
}