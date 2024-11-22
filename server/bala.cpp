#include "bala.h"
#include <cmath>  // Para usar sqrt y calcular la distancia

// Constructor
Bala::Bala(float x_inicial, float y_inicial, float destino_x, float destino_y, float velocidad_inicial)
    : x(x_inicial), y(y_inicial), destino_x(destino_x), destino_y(destino_y), velocidad(velocidad_inicial), activa(true) {}

// Método para actualizar la  de la bala
bool Bala::actualizar(float delta_time) {
    float direccion_x = destino_x - x;
    float direccion_y = destino_y - y;

    float distancia = std::sqrt(direccion_x * direccion_x + direccion_y * direccion_y);
    if (distancia > 0) {
        direccion_x /= distancia;
        direccion_y /= distancia;
    }

    // Actualiza la posición de la bala en la dirección deseada
    x += direccion_x * velocidad * delta_time;
    y += direccion_y * velocidad * delta_time;

    // Verifica si la bala ha llegado al destino
    if (std::sqrt((destino_x - x) * (destino_x - x) + (destino_y - y) * (destino_y - y)) < 1.0f) {
        return false;  // La bala llegó al destino
    }

    return true;  // La bala sigue activa
}

// Método para desactivar la bala después de un impacto
void Bala::desactivar() {
    activa = false;
}

// Método para comprobar si la bala está activa
bool Bala::estaActiva() const {
    return activa;
}

// Métodos para obtener la posición actual de la bala
float Bala::getX() const { return x; }
float Bala::getY() const { return y; }
