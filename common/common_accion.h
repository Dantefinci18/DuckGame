#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <cstdint>
#include <memory>

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
    ESTABLECER_PARTIDAS,
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

        virtual ~Accion() = default;
};

class AccionCargarPartida : public Accion {
    public:
        int id_partida;
        const std::string& nombre_partida;

        explicit AccionCargarPartida(int id_partida, const std::string& nombre_partida):
            Accion(ComandoAccion::CARGAR_PARTIDA),id_partida(id_partida), nombre_partida(nombre_partida){}
};

class AccionNuevaPartida : public Accion {
    public:
        int cantidad_de_jugadores;
        std::string nombre_partida;
        int mapa;

        explicit AccionNuevaPartida(int cantidad_de_jugadores, 
            const std::string &nombre_partida, int mapa):
            
            Accion(ComandoAccion::NUEVA_PARTIDA),
            cantidad_de_jugadores(cantidad_de_jugadores),
            mapa(mapa),nombre_partida(nombre_partida){}
};


#endif // COMMON_ACCION_H
