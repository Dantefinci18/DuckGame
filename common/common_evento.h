#ifndef COMMON_EVENTO_H
#define COMMON_EVENTO_H

#include <vector>
#include <cstdint>
#include "../server/Collidable.h"

class Evento {
public:
    enum TipoEvento {
        EventoMovimiento,
        EventoMapa,
        
    };

    virtual ~Evento() = default;
    virtual TipoEvento get_tipo() const = 0;  
};

class EventoMovimiento : public Evento {
public:
    int id;
    float x;
    float y;

    EventoMovimiento(int id, float x, float y) : id(id), x(x), y(y) {}

    TipoEvento get_tipo() const override { return TipoEvento::EventoMovimiento; }  
};

class EventoMapa : public Evento {
public:
    std::vector<Collidable*> collidables;

    EventoMapa(const std::vector<Collidable*>& collidables)
        : collidables(collidables) {}

    TipoEvento get_tipo() const override { return TipoEvento::EventoMapa; }  
};

#endif
