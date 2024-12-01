#ifndef COMMON_PROTECCION_H
#define COMMON_PROTECCION_H

enum class ProteccionType {
    Armadura,
    Casco,
    None // ver esto 
};

class Proteccion {
private:
    bool sirve;
public:
    ProteccionType type;

    Proteccion(ProteccionType type) : sirve(true), type(type) {} 
    virtual ~Proteccion() = default;

    ProteccionType get_type() const {
        return type;
    }

    bool en_condiciones() const {
        return sirve;
    }

    void impactar() {
        sirve = false;
    }
};

#endif
