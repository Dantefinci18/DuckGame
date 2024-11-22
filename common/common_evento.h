#ifndef COMMON_EVENTO_H
#define COMMON_EVENTO_H

#include <vector>
#include <cstdint>
#include "common_weapon.h" 
#include "../server/Collidable.h"
#include "../common/common_color.h"
class Evento {
public:
    enum TipoEvento {
        EventoMovimiento,
        EventoMapa,
        EventoPickup,
        EventoSpawnArma,
        EventoMuerte,
        EventoDisparo,
        EventoEspera,
        EventoAgacharse,
        EventoLevantarse,
        EventoBala
    };

    virtual ~Evento() = default;
    virtual TipoEvento get_tipo() const = 0;  
};

class EventoMovimiento : public Evento {
public:
    int id;
    ColorDuck color;
    float x;
    float y;
    bool is_flapping;

    EventoMovimiento(int id,ColorDuck color,float x, float y, bool is_flapping) : id(id),color(color), x(x), y(y), is_flapping(is_flapping) {}

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

class EventoAgacharse : public Evento {
public:
    int id;

    EventoAgacharse(int id) : id(id) {}
    TipoEvento get_tipo() const override { return TipoEvento::EventoAgacharse; } 
};


class EventoLevantarse : public Evento {
public:
    int id;

    EventoLevantarse(int id) : id(id) {}
    TipoEvento get_tipo() const override { return TipoEvento::EventoLevantarse; } 
};

class EventoBala : public Evento {
public:
    float x;
    float y;

    EventoBala(float x, float y) : x(x), y(y) {}
    TipoEvento get_tipo() const override { return TipoEvento::EventoBala; } 
};

#endif
