#ifndef COMMON_EVENTO_H
#define COMMON_EVENTO_H

#include <vector>
#include <cstdint>
#include "common_weapon.h" // Assuming WeaponType is defined here
#include "../server/Collidable.h"
#include "common_direcciones.h"
class Evento {
public:
    enum TipoEvento {
        EventoMovimiento,
        EventoMapa,
        EventoPickup,
        EventoSpawnArma,
        EventoMuerte,
        EventoDisparo,
        EventoEspera
    };

    virtual ~Evento() = default;
    virtual TipoEvento get_tipo() const = 0;  
};

class EventoMovimiento : public Evento {
public:
    int id;
    float x;
    float y;
    DireccionApuntada direccion_apuntada;

    EventoMovimiento(int id, float x, float y, DireccionApuntada direccion_apuntada) : id(id), x(x), y(y), direccion_apuntada(direccion_apuntada) {}

    TipoEvento get_tipo() const override { return TipoEvento::EventoMovimiento; }  
};

class EventoMapa : public Evento {
public:
    std::vector<Collidable*> collidables;

    EventoMapa(const std::vector<Collidable*>& collidables)
        : collidables(collidables) {}

    TipoEvento get_tipo() const override { return TipoEvento::EventoMapa; }  
};

class EventoSpawnArma : public Evento {
public:
    float x;
    float y;
    WeaponType weapon_type;

    EventoSpawnArma(float x, float y, WeaponType weapon_type) 
        : x(x), y(y), weapon_type(weapon_type) {}

    TipoEvento get_tipo() const override { return TipoEvento::EventoSpawnArma; } 
};

class EventoPickup : public Evento {
public:
    int id;
    float x;
    float y;
    WeaponType weapon_type;

    EventoPickup(int id, float x, float y, WeaponType weapon_type) 
        : id(id), x(x), y(y), weapon_type(weapon_type) {}

    TipoEvento get_tipo() const override { return TipoEvento::EventoPickup; } 
};

class EventoMuerte : public Evento {
public:
    int id;

    EventoMuerte(int id) : id(id) {}
    TipoEvento get_tipo() const override { return TipoEvento::EventoMuerte; } 
};

class EventoDisparo : public Evento {
public:
    int id;

    EventoDisparo(int id) : id(id){}
    TipoEvento get_tipo() const override { return TipoEvento::EventoDisparo; } 
};

class EventoEspera : public Evento {
    public:
        TipoEvento get_tipo() const override { return TipoEvento::EventoEspera; }
};

#endif
