#ifndef COMMON_EVENTO_H
#define COMMON_EVENTO_H

#include <vector>
#include <cstdint>
#include "common_weapon.h" 
#include "../server/Collidable.h"
#include "../common/common_color.h"
#include "../common/common_direcciones.h"
#include "../server/server_leaderboard.h"
#include "common_proteccion.h"



class Evento {
public:
    enum TipoEvento {
        EventoMovimiento,
        EventoMapa,
        EventoPickup,
        EventoPickupProteccion,
        EventoSpawnArma,
        EventoMuerte,
        EventoDisparo,
        EventoEspera,
        EventoApuntar,
        EventoAgacharse,
        EventoLevantarse,
        EventoWinRound,
        EventoWinMatch,
        EventoBala,
        EventoCajaDestruida,
        EventoSpawnArmaBox,
        EventoSpawnProteccionBox
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

    EventoMovimiento(int id, ColorDuck color, float x, float y, bool is_flapping, bool reset) 
        : id(id), color(color), x(x), y(y), is_flapping(is_flapping), reset(reset) {}

    void print() const override {
        
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoMovimiento; }  
};

class EventoMapa : public Evento {
public:
    std::vector<Collidable*> collidables;
    Leaderboard leaderboard;

    EventoMapa(const std::vector<Collidable*>& collidables, Leaderboard leaderboard)
        : collidables(collidables), leaderboard(leaderboard) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoMapa\", "
            << "\"collidables_count\": " << collidables.size() << ", "
            << "\"leaderboard\": " << leaderboard.to_json()
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

class EventoPickupProteccion : public Evento {
public:
    int id;
    float x;
    float y;
    ProteccionType proteccion_type;

    EventoPickupProteccion(int id, float x, float y, ProteccionType proteccion_type) 
        : id(id), x(x), y(y), proteccion_type(proteccion_type) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoPickupProteccion\", "
            << "\"id\": " << id << ", "
            << "\"x\": " << x << ", "
            << "\"y\": " << y << ", "
            << "\"proteccion_type\": " << static_cast<int>(proteccion_type)
            << " }";
        std::cout << oss.str() << std::endl;
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoPickupProteccion; } 
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

    EventoDisparo(int id) : id(id) {}

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

class EventoApuntar : public Evento {
public:
    int id;
    DireccionApuntada direccion;

    EventoApuntar(int id, DireccionApuntada direccion) : id(id), direccion(direccion) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoApuntar\", "
            << "\"id\": " << id << ", "
            << "\"direccion\": " << static_cast<int>(direccion)
            << " }";
        std::cout << oss.str() << std::endl;
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoApuntar; } 
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

class EventoWinMatch : public Evento {
public:
    int id;

    EventoWinMatch(int id) : id(id) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoWinMatch\", "
            << "\"id\": " << id
            << " }";
        std::cout << oss.str() << std::endl;
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoWinMatch; } 
};

class EventoBala : public Evento {
public:
    float x;
    float y;

    EventoBala(float x, float y) : x(x), y(y) {}

    void print() const override {
        
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoBala; }
};

class EventoCajaDestruida : public Evento {
public:
    float x;
    float y;

    EventoCajaDestruida(float x, float y) : x(x), y(y) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoCajaDestruida\", "
            << "\"x\": " << x << ", "
            << "\"y\": " << y
            << " }";
        std::cout << oss.str() << std::endl;
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoCajaDestruida; }

};

class EventoSpawnArmaBox : public Evento {
public:
    float x;
    float y;
    WeaponType weapon_type; 
    EventoSpawnArmaBox(float x, float y, WeaponType weapon_type) 
        : x(x), y(y), weapon_type(weapon_type) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoSpawnArmaBox\", "
            << "\"x\": " << x << ", "
            << "\"y\": " << y << ", "
            << "\"weapon_type\": " << static_cast<int>(weapon_type)
            << " }";
        std::cout << oss.str() << std::endl;
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoSpawnArmaBox; } 
};

class EventoSpawnProteccionBox : public Evento {
public:
    float x;
    float y;
    ProteccionType proteccion_type; 
    EventoSpawnProteccionBox(float x, float y, ProteccionType proteccion_type) 
        : x(x), y(y), proteccion_type(proteccion_type) {}

    void print() const override {
        std::ostringstream oss;
        oss << "{ \"type\": \"EventoSpawnProteccionBox\", "
            << "\"x\": " << x << ", "
            << "\"y\": " << y << ", "
            << "\"proteccion_type\": " << static_cast<int>(proteccion_type)
            << " }";
        std::cout << oss.str() << std::endl;
    }

    TipoEvento get_tipo() const override { return TipoEvento::EventoSpawnProteccionBox; } 
};

#endif // COMMON_EVENTO_H
