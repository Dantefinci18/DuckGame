#include "cliente_protocolo.h"
#include <ostream>
#include <bitset>
#include <iostream>
#include <cstring>
#include <memory> 


ClienteProtocolo::ClienteProtocolo(Socket&& socket) : socket(std::move(socket)) {}

bool ClienteProtocolo::crear_partida(const std::string& nombre_partida,
        const std::string& mapa_seleccionado, const unsigned int cantidad_de_jugadores) {
    
    (void)mapa_seleccionado;
    bool was_closed = false;
    std::vector<uint8_t> partida_serializada = serializador.serializar_accion(std::make_unique<AccionNuevaPartida>(cantidad_de_jugadores,nombre_partida,1));
    socket.sendall(partida_serializada.data(), partida_serializada.size(), &was_closed);
    if (was_closed) {
        return false;
    }

    return true;
    
}

bool ClienteProtocolo::cargar_partida(int id, const std::string& nombre_partida){
    bool was_closed = false;

    auto partida_serializada = serializador.serializar_accion(std::make_unique<AccionCargarPartida>(id,nombre_partida));
    socket.sendall(partida_serializada.data(), partida_serializada.size(), &was_closed);
    
    if (was_closed) {
        return false;
    }

    return true;
}

bool ClienteProtocolo::enviar_accion(ComandoAccion &comando_accion) {
    bool was_closed = false;
    std::vector<uint8_t> buffer= serializador.serializar_accion(std::make_unique<Accion>(comando_accion));

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
        case Evento::EventoPickupProteccion: {
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

            uint8_t proteccion_type[32];
            socket.recvall(proteccion_type, sizeof(proteccion_type), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_pickup_proteccion(id, x, y, proteccion_type);
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

        case Evento::EventoCajaDestruida: {
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

            return serializador.deserializar_caja_destruida(x, y);
        }

        case Evento::EventoSpawnArmaBox: {
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

            uint8_t width[32];
            socket.recvall(width, sizeof(width), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t height[32];
            socket.recvall(height, sizeof(height), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            uint8_t weapon_type[32];
            socket.recvall(weapon_type, sizeof(weapon_type), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_spawn_arma_box(x, y, width, height, weapon_type);

        }case Evento::EventoEspera: {
            return std::make_unique<EventoEspera>();
        }


        case Evento::EventoSpawnProteccionBox: {
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

            uint8_t proteccion_type[32];
            socket.recvall(proteccion_type, sizeof(proteccion_type), &was_closed);
            if (was_closed) {
                return nullptr;
            }

            return serializador.deserializar_spawn_proteccion_box(x, y, proteccion_type);

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

std::list<Partida> ClienteProtocolo::recibir_partidas(){
    bool was_closed = false;
    std::list<Partida> partidas;
    uint8_t tamanio_partidas_bits[32];
    socket.recvall(tamanio_partidas_bits,sizeof(tamanio_partidas_bits),&was_closed);

    std::cout << "cantidad de partidas\n";
    serializador.imprimir_uint8_t_array(tamanio_partidas_bits,sizeof(tamanio_partidas_bits));

    if(was_closed)
        return std::list<Partida>();

    int tamanio_partidas = serializador.deserializar_numero_entero(tamanio_partidas_bits);

    std::cout << "tamanio partidas: " << tamanio_partidas << std::endl;  
    
    for(int i = 0; i < tamanio_partidas; i++){
        uint8_t id_bits[32];
        socket.recvall(id_bits,sizeof(id_bits),&was_closed);

        std::cout << "id partida:\n";
        serializador.imprimir_uint8_t_array(id_bits,sizeof(id_bits));

        if(was_closed)
            return std::list<Partida>();
        
        uint8_t tamanio_nombre_bits[32];
        socket.recvall(tamanio_nombre_bits,sizeof(tamanio_nombre_bits),&was_closed);

        std::cout << "tamanio_nombre partida:\n";
        serializador.imprimir_uint8_t_array(tamanio_nombre_bits,sizeof(tamanio_nombre_bits));


        if(was_closed)
            return std::list<Partida>();
        
        int tamanio_nombre = serializador.deserializar_numero_entero(tamanio_nombre_bits);
        uint8_t nombre_bits[tamanio_nombre];
        socket.recvall(nombre_bits,sizeof(nombre_bits),&was_closed);

        std::cout << "nombre partida\n";
        serializador.imprimir_uint8_t_array(nombre_bits,sizeof(nombre_bits));

        if(was_closed)
            return std::list<Partida>();
        
        Partida partida = serializador.deserializar_partida(id_bits,nombre_bits,tamanio_nombre);
        partidas.push_back(partida);
    }

    return partidas;
}

void ClienteProtocolo::cerrar_conexion() {
    socket.shutdown(2);
    socket.close();
}