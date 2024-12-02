#ifndef COMMON_PARTIDA_H
#define COMMON_PARTIDA_H

#include <string>

class Partida{
    public:
        int id;
        const std::string& nombre;

        explicit Partida(int id, const std::string& nombre): id(id), nombre(nombre){}
};

#endif