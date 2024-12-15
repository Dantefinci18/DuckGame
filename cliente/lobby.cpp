#include "lobby.h"
#include <utility>
#include <stdexcept>
#include "cliente_protocolo.h"

Lobby::Lobby(const char* hostname, const char* servname) : socket(hostname, servname) {}

void Lobby::crear_partida(const std::string& mapa_seleccionado, const int cantidad_jugadores) {
    (void)mapa_seleccionado;
    bool was_closed = false;
    ComandoAccion comando = NUEVA_PARTIDA;
    std::vector<uint8_t> partida_serializada = serializador.serializar_accion(comando);
    socket.sendall(partida_serializada.data(), partida_serializada.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar comando de nueva partida");
    }

    std::vector<uint8_t> cantidad_jugadores_serializada = serializador.serializar_num_jugadores(cantidad_jugadores);
    socket.sendall(cantidad_jugadores_serializada.data(), cantidad_jugadores_serializada.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar cantidad de jugadores");
    }
    
    
}

void Lobby::cargar_partida(){
    bool was_closed = false;
    ComandoAccion comando = CARGAR_PARTIDA;
    std::vector<uint8_t> accion_serializada = serializador.serializar_accion(comando);
    socket.sendall(accion_serializada.data(), accion_serializada.size(), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al enviar comando de cargar partida");
    }
}

int Lobby::recibir_id() {
    bool was_closed = false;
    uint8_t data[16];
    socket.recvall(data, sizeof(data), &was_closed);

    if (was_closed) {
        throw std::runtime_error("Error al recibir ID: conexión cerrada");
    }
    return serializador.deserializar_id(data);
}

std::unique_ptr<Evento> Lobby::recibir_evento() {
    bool was_closed = false;

    uint8_t tipo_evento[8];
    socket.recvall(tipo_evento, sizeof(tipo_evento), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error al recibir el tipo de evento: conexión cerrada");
    }

    serializador.imprimir_uint8_t_array(tipo_evento,sizeof(tipo_evento));
    Evento::TipoEvento tipo = serializador.deserializar_tipo_evento(tipo_evento);


    switch (tipo) {
        case Evento::EventoMovimiento: {
            uint8_t evento_movimiento[46];
            socket.recvall(evento_movimiento, sizeof(evento_movimiento), &was_closed);
            if (was_closed) {
                return nullptr;
            }
            return serializador.deserializar_movimiento(evento_movimiento);
        }
        case Evento::EventoMapa: {
            uint8_t cantidad[6];
            socket.recvall(cantidad, sizeof(cantidad), &was_closed);
            if (was_closed) {
                throw std::runtime_error("Error al recibir cantidad de collidables en evento de mapa: conexión cerrada");
            }

            int cantidad_collidables = serializador.deserializar_cantidad_collidables(cantidad);
            std::vector<Collidable*> collidables;

            for (int i = 0; i < cantidad_collidables; i++) {
                uint8_t collidable_data[52];
                socket.recvall(collidable_data, sizeof(collidable_data), &was_closed);
                if (was_closed) {
                    throw std::runtime_error("Error al recibir datos de collidable en evento de mapa: conexión cerrada");
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
        
        case Evento::EventoEspera: {
            return std::make_unique<EventoEspera>();
        }

        default:
            throw std::runtime_error("Error: Tipo de evento desconocido");
            
    }
}



Lobby::~Lobby() {}

Socket Lobby::get_socket() {
    return std::move(socket);
}