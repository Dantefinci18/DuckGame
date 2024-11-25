#include "common_color.h"
#include <cstdint> // Para uint32_t

class ColorUtils {
public:
    static uint32_t get_hex(ColorDuck color) {
        switch (color) {
            case ColorDuck::BLANCO:   return 0xFFFFFFFF; // Blanco
            case ColorDuck::ROJO:     return 0xFF0000FF; // Rojo
            case ColorDuck::AZUL:     return 0x0000FFFF; // Azul
            case ColorDuck::VERDE:    return 0x00FF00FF; // Verde
            case ColorDuck::AMARILLO: return 0xFFFF00FF; // Amarillo
            case ColorDuck::NARANJA:  return 0xFFA500FF; // Naranja
            case ColorDuck::ROSA:     return 0xFFC0CBFF; // Rosa
            case ColorDuck::NEGRO:    return 0x000000FF; // Negro
            case ColorDuck::CELESTE:  return 0x87CEEBFF; // Celeste
            default:
                return 0x000000FF; // Valor por defecto (Negro con opacidad completa)
        }
    }
};