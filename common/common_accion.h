#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <cstdint>
#include <optional>

enum ComandoAccion : uint8_t {
    DERECHA,
    IZQUIERDA,
    QUIETO,
    SALTAR,
    NONE,
    DISPARAR,
    DEJAR_DISPARAR,
    RECARGAR,
    AGACHARSE,
    LEVANTARSE,
    NUEVA_PARTIDA_ACCION,
    APUNTAR_ARRIBA,
    DEJAR_APUNTAR_ARRIBA,
    NUEVA_PARTIDA,
    CARGAR_PARTIDA,
    UNIRSE_PARTIDA,
    NONE_ACCION
};

class Accion {
private:
    int player_id;
    ComandoAccion command;
    int cantidad_jugadores; 

public:
    explicit Accion(int player_id, ComandoAccion command)
        : player_id(player_id), command(command), cantidad_jugadores(-1) {}

    explicit Accion(int player_id, ComandoAccion command, int cantidad_jugadores)
        : player_id(player_id), command(command), cantidad_jugadores(cantidad_jugadores) {}

    explicit Accion() : player_id(-1), command(ComandoAccion::NONE_ACCION), cantidad_jugadores(-1) {}

    ComandoAccion get_command() const {
        return command;
    }

    int get_player_id() const {
        return player_id;
    }

    int get_cantidad_jugadores() const {
        return cantidad_jugadores;
    }
};

#endif // COMMON_ACCION_H
