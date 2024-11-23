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
        EventoWinRound
    };

    virtual ~Evento() = default;
    virtual TipoEvento get_tipo() const = 0; 
    virtual void print() const = 0; 
};

class EventoMovimiento : public Evento {
public:
    int id;
    ColorDuck color;
    float x;
    float y;
    bool is_flapping;
    bool reset;

    EventoMovimiento(int id,ColorDuck color,float x, float y, bool is_flapping, bool reset) : id(id),color(color), x(x), y(y), is_flapping(is_flapping), reset(reset) {}
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoMovimiento\", "
            << "\"id\": " << id << ", "
            << "\"color\": " << static_cast<int>(color) << ", "
            << "\"x\": " << x << ", "
            << "\"y\": " << y << ", "
            << "\"is_flapping\": " << (is_flapping ? "true" : "false") << ", "
            << "\"reset\": " << (reset ? "true" : "false")
            << " }";
        std::cout << oss.str() << std::endl;
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoMovimiento; }  
};

class EventoMapa : public Evento {
public:
    std::vector<Collidable*> collidables;

    EventoMapa(const std::vector<Collidable*>& collidables)
        : collidables(collidables) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoMapa\", "
            << "\"collidables_count\": " << collidables.size()
            << " }";
        std::cout << oss.str() << std::endl;
    }
    TipoEvento get_tipo() const override { return TipoEvento::EventoMapa; }  
};

class EventoSpawnArma : public Evento {
public:
    float x;
    float y;
    WeaponType weapon_type;

    EventoSpawnArma(float x, float y, WeaponType weapon_type) 
        : x(x), y(y), weapon_type(weapon_type) {}
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoSpawnArma\", "
            << "\"x\": " << x << ", "
            << "\"y\": " << y << ", "
            << "\"weapon_type\": " << static_cast<int>(weapon_type)
            << " }";
        std::cout << oss.str() << std::endl;
    }
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
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoPickup\", "
            << "\"id\": " << id << ", "
            << "\"x\": " << x << ", "
            << "\"y\": " << y << ", "
            << "\"weapon_type\": " << static_cast<int>(weapon_type)
            << " }";
        std::cout << oss.str() << std::endl;
    }
    TipoEvento get_tipo() const override { return TipoEvento::EventoPickup; } 
};

class EventoMuerte : public Evento {
public:
    int id;

    EventoMuerte(int id) : id(id) {}
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoMuerte\", "
            << "\"id\": " << id
            << " }";
        std::cout << oss.str() << std::endl;
    }
    TipoEvento get_tipo() const override { return TipoEvento::EventoMuerte; } 
};

class EventoDisparo : public Evento {
public:
    int id;

    EventoDisparo(int id) : id(id){}
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoDisparo\", "
            << "\"id\": " << id
            << " }";
        std::cout << oss.str() << std::endl;
    }
    TipoEvento get_tipo() const override { return TipoEvento::EventoDisparo; } 
};

class EventoEspera : public Evento {
    public:
        void print() const override {
            std::cout << "{ \"type\": \"EventoEspera\" }" << std::endl;
        }
        TipoEvento get_tipo() const override { return TipoEvento::EventoEspera; }
};

class EventoAgacharse : public Evento {
public:
    int id;

    EventoAgacharse(int id) : id(id) {}
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoAgacharse\", "
            << "\"id\": " << id
            << " }";
        std::cout << oss.str() << std::endl;
    }
    TipoEvento get_tipo() const override { return TipoEvento::EventoAgacharse; } 
};


class EventoLevantarse : public Evento {
public:
    int id;

    EventoLevantarse(int id) : id(id) {}
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoLevantarse\", "
            << "\"id\": " << id
            << " }";
        std::cout << oss.str() << std::endl;
    }
    TipoEvento get_tipo() const override { return TipoEvento::EventoLevantarse; } 
};

class EventoWinRound : public Evento {
public:
    int id;
    EventoWinRound(int id) : id(id) {}
    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoWinRound\", "
            << "\"id\": " << id
            << " }";
        std::cout << oss.str() << std::endl;
    }
    TipoEvento get_tipo() const override { return TipoEvento::EventoWinRound; } 
};

#endif
