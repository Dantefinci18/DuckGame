#ifndef COMMON_PARTIDA_H
#define COMMON_PARTIDA_H

#include <cstdint>

class ComandoPartida{
    public:
        enum TipoComandoPartida{
            NUEVA_PARTIDA,
            CARGAR_PARTIDA,
            NONE_PARTIDA
        };
    
        virtual TipoComandoPartida get_tipo() const  = 0;

};

class ComandoNuevaPartida : public ComandoPartida{
    public:
        const std::string& nombre;
        const unsigned int cantidad_de_jugadores;
        
        explicit ComandoNuevaPartida(const std::string& nombre, const unsigned int cantidad_de_jugadores):
            nombre(nombre), cantidad_de_jugadores(cantidad_de_jugadores){}
        
        TipoComandoPartida get_tipo() const override{
            return TipoComandoPartida::NUEVA_PARTIDA;
        }
};

class ComandoNonePartida : public ComandoPartida{
    public:
        TipoComandoPartida get_tipo() const override{
            return TipoComandoPartida::NONE_PARTIDA;
        }
};

#endif