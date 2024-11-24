#include "bala.h"
#include <cmath>  

Bala::Bala(float x_inicial, float y_inicial, float destino_x, float destino_y, float velocidad_inicial)
    : x(x_inicial), y(y_inicial), destino_x(destino_x), destino_y(destino_y), velocidad(velocidad_inicial), activa(true) {}

bool Bala::actualizar(float delta_time) {
    float direccion_x = destino_x - x;
    float direccion_y = destino_y - y;

    float distancia = std::sqrt(direccion_x * direccion_x + direccion_y * direccion_y);
    if (distancia > 0) {
        direccion_x /= distancia;
        direccion_y /= distancia;
    }

    x += direccion_x * velocidad * delta_time;
    y += direccion_y * velocidad * delta_time;

    if (std::sqrt((destino_x - x) * (destino_x - x) + (destino_y - y) * (destino_y - y)) < 1.0f) {
        return false;  
    }

    return true;  
}

void Bala::desactivar() {
    activa = false;
}

bool Bala::estaActiva() const {
    return activa;
}

float Bala::getX() const { return x; }
float Bala::getY() const { return y; }
