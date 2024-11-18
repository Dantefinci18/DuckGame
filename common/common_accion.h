#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <cstdint>

enum ComandoAccion : uint8_t{
    NUEVA_PARTIDA,
    DERECHA,
    IZQUIERDA,
    QUIETO,
    SALTAR,
    NONE,
    DISPARAR,
    DEJAR_DISPARAR,
    RECARGAR
};

class Accion {
    private:
        int player_id;
        ComandoAccion command;
    public:
        ComandoAccion get_command() {
            return command;
        }

        int get_player_id() {
            return player_id;
        }
        explicit Accion(int player_id, ComandoAccion command) : player_id(player_id), command(command) {}
        explicit Accion() : player_id(-1), command(ComandoAccion::NONE) {}
};
#endif // COMMON_ACCION_H
