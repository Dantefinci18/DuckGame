#include "duck.h"

#define ANCHO_IMG_DUCK_TOTAL 180
#define ALTO_VENTANA 600
#define DESPLAZAMIENTO_X 6
#define DESPLAZAMIENTO_Y 4
#define FACTOR_ESCALA 2
#define VELOCIDAD_SALTO 15
#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

Duck::Duck(SdlWindow& window, float x_inicial, float y_inicial, std::string color)
    : movimientos_en_x("../Imagenes/duck_x" + color + ".png", window),
      movimiento_en_y("../Imagenes/movimiento_y" + color + ".png", window),
      armas("../Imagenes/guns.png", window),
      death("../Imagenes/duckDead" + color + ".png", window),
      quieto(false),
      weapon(std::nullopt),
      x_img(0),
      y_img(0),
      x_actual(x_inicial),
      y_actual(y_inicial),
      x_des(x_inicial),
      y_des(static_cast<int>(y_inicial)),
      is_dead(false),
      is_flapping(false),
      flip(SDL_FLIP_NONE) {}

void Duck::render() {
    bool en_movimiento_x = (x_actual != x_des);
    bool en_movimiento_y = (y_actual != y_des);

    if (is_dead) {
        Area srcArea(0, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
        int y_renderizado = ALTO_VENTANA - y_actual - ALTO_IMG_DUCK * FACTOR_ESCALA;
        Area destArea(x_actual, y_renderizado, ANCHO_IMG_DUCK * FACTOR_ESCALA, ALTO_IMG_DUCK * FACTOR_ESCALA);
        death.render(srcArea, destArea, flip);
        return;
    }
    if (en_movimiento_x) {
        render_movimiento_horizontal();
    }

    if (en_movimiento_y) {
        render_movimiento_vertical();
    } else if (!en_movimiento_x) {
        render_idle();
    }

    int y_renderizado = ALTO_VENTANA - y_actual - ALTO_IMG_DUCK * FACTOR_ESCALA;
    Area srcArea(x_img, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
    Area destArea(x_actual, y_renderizado, ANCHO_IMG_DUCK * FACTOR_ESCALA, ALTO_IMG_DUCK * FACTOR_ESCALA);

    if (en_movimiento_y) {
        render_movimiento_salto(srcArea, destArea);
    } else if (en_movimiento_x || quieto) {
        movimientos_en_x.render(srcArea, destArea, flip);
    }

    if (weapon) {
        render_arma(y_renderizado);
    }
}

bool Duck::esta_quieto() { return quieto; }

void Duck::kill() {
    is_dead = true;
}

void Duck::mover_a(float x, float y, bool is_flapping) {
    if (x != x_des || y != y_des) {
        quieto = false;
    }
    x_des = x;
    this->is_flapping = is_flapping;
    y_des = y;
}

void Duck::set_weapon(WeaponType weapon) {
    this->weapon = weapon;
}

Duck::~Duck() {}

void Duck::render_movimiento_horizontal() {
    if (x_actual < x_des) {
        x_actual += DESPLAZAMIENTO_X;
        flip = SDL_FLIP_NONE;
    } else if (x_actual > x_des) {
        x_actual -= DESPLAZAMIENTO_X;
        flip = SDL_FLIP_HORIZONTAL;
    }

    if (y_actual == y_des) {
        if (x_img < ANCHO_IMG_DUCK_TOTAL - ANCHO_IMG_DUCK) {
            x_img += ANCHO_IMG_DUCK;
        } else {
            x_img = 0;
        }
    }
}

void Duck::render_movimiento_vertical() {
    float distancia_vertical = y_des - y_actual;
    float velocidad_vertical = VELOCIDAD_SALTO * (distancia_vertical > 0 ? 1 : -1);

    if (std::abs(distancia_vertical) < VELOCIDAD_SALTO) {
        y_actual = y_des;
    } else {
        y_actual += velocidad_vertical;
    }

    if ((distancia_vertical > 0 && y_actual > y_des) || (distancia_vertical < 0 && y_actual < y_des)) {
        y_actual = y_des;
    }

    if (is_flapping) {
        x_img = (x_img == 2 * ANCHO_IMG_DUCK ? 5 * ANCHO_IMG_DUCK : 2 * ANCHO_IMG_DUCK);
    } 
    else if (distancia_vertical > 0) {
        x_img = 3 * ANCHO_IMG_DUCK;
    } else if (distancia_vertical < 0) {
        x_img = (x_img < ANCHO_IMG_DUCK_TOTAL - ANCHO_IMG_DUCK) ? 4 * ANCHO_IMG_DUCK : 0;
    }
}

void Duck::render_idle() {
    x_img = 0;
    movimientos_en_x.render(Area(0, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK), 
                            Area(x_actual, ALTO_VENTANA - y_actual - ALTO_IMG_DUCK * FACTOR_ESCALA, ANCHO_IMG_DUCK * FACTOR_ESCALA, ALTO_IMG_DUCK * FACTOR_ESCALA), flip);
}

void Duck::render_movimiento_salto(Area& srcArea, Area& destArea) {
    movimiento_en_y.render(srcArea, destArea, flip);
}

void Duck::render_arma(int y_renderizado) {
    Area armaSrcArea(0, 0, 38, 38);
    Area armaDestArea(x_actual + 20, y_renderizado + 25, 38, 38);
    armas.render(armaSrcArea, armaDestArea, flip);
}
