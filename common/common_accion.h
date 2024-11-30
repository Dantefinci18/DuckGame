#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <cstdint>

enum ComandoAccion : uint8_t{
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
    NONE_ACCION
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

        void set_player_id(int id){
            player_id = id;
        }

        explicit Accion(ComandoAccion command) : player_id(-1), command(command) {}
        explicit Accion() : player_id(-1), command(ComandoAccion::NONE_ACCION) {}
};

class AccionNuevaParida : public Accion {
    public:
        const unsigned int cantidad_de_jugadores;
        const unsigned int mapa;

        explicit AccionNuevaParida(const unsigned int cantidad_de_jugadores,const unsigned int mapa):
            
            Accion(ComandoAccion::NUEVA_PARTIDA),
            cantidad_de_jugadores(cantidad_de_jugadores),
            mapa(mapa){}
};


#endif // COMMON_ACCION_H
