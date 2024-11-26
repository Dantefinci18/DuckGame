#include "duck.h"

#define ANCHO_IMG_DUCK_TOTAL 180
#define ALTO_VENTANA 600
#define DESPLAZAMIENTO_X 6
#define DESPLAZAMIENTO_Y 4
#define FACTOR_ESCALA 2
#define VELOCIDAD_SALTO 15
#define ANCHO_IMG_DUCK 32
#define ALTO_IMG_DUCK 38

Duck::Duck(SdlWindow& window, float x_inicial, float y_inicial,ColorDuck color)
    : movimientos_en_x("../Imagenes/duck_x" + procesar_color(color) + ".png", window),
      movimiento_en_y("../Imagenes/movimiento_y" + procesar_color(color) + ".png", window),
      armas("../Imagenes/guns.png", window),
      death("../Imagenes/duckDead" + procesar_color(color) + ".png", window),
      color(color),
      bala("../Imagenes/balas_magnum.png", window),
      quieto(false),                
      weapon(std::nullopt),          
      direccion_arma(DireccionApuntada::APUNTADO_DERECHA),
      x_img(0),                     
      y_img(0),                     
      x_actual(x_inicial),          
      y_actual(y_inicial),          
      is_dead(false),               
      x_des(x_inicial),              
      y_des(static_cast<int>(y_inicial)),
      x_bala(0),
      y_bala(0),
      esta_disparando(false),
      is_flapping(false),            
      esta_agachado(false),    
      reset(false),     
      flip(SDL_FLIP_NONE)         
{}


void Duck::setear_bala(float x, float y) {
    x_bala = x;
    y_bala = y;
    esta_disparando = true;
}

void Duck::render_bala() {

    const int ANCHO_BALA = 12;  
    const int ALTO_BALA = 16; 
    const int FACTOR_ESCALA_BALA = 4; 
    SDL_RendererFlip flip = (direccion_arma == DireccionApuntada::APUNTADO_IZQUIERDA) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            
    Area srcArea(0, 0, ANCHO_BALA, ALTO_BALA);

    
    int x_renderizado = x_bala;
    int y_renderizado = ALTO_VENTANA - y_bala - ALTO_BALA * FACTOR_ESCALA_BALA;
    Area destArea(x_renderizado, y_renderizado, ANCHO_BALA * FACTOR_ESCALA_BALA, ALTO_BALA * FACTOR_ESCALA_BALA);

    bala.render(srcArea, destArea, flip);
    esta_disparando = false;
    
}


void Duck::render() {
    bool en_movimiento_x = (x_actual != x_des);
    bool en_movimiento_y = (y_actual != y_des);
    //std::cout << "render_duck" << std::endl;
    if (reset) {
        std::cout << "reset" << std::endl;
        weapon = std::nullopt;
        is_dead = false;
        esta_agachado = false;
        is_flapping = false;
        y_actual = y_des;
        x_actual = x_des;
        x_img = 0;
        y_img = 0;
        return;
    }
    if (is_dead) {
        Area srcArea(0, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
        int y_renderizado = ALTO_VENTANA - y_actual - ALTO_IMG_DUCK * FACTOR_ESCALA;
        Area destArea(x_actual, y_renderizado, ANCHO_IMG_DUCK * FACTOR_ESCALA, ALTO_IMG_DUCK * FACTOR_ESCALA);
        death.render(srcArea, destArea, flip);
        return;
    }

    if (esta_disparando) {
        render_bala();
    }

    if (esta_agachado) {
        Area srcArea(5 * ANCHO_IMG_DUCK, 0, ANCHO_IMG_DUCK, ALTO_IMG_DUCK);
        int y_renderizado = ALTO_VENTANA - y_actual - ALTO_IMG_DUCK * FACTOR_ESCALA;
        Area destArea(x_actual, y_renderizado, ANCHO_IMG_DUCK * FACTOR_ESCALA, ALTO_IMG_DUCK * FACTOR_ESCALA);
        movimiento_en_y.render(srcArea, destArea, flip);
    } else {
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
    }

    if (weapon) {
        render_arma(ALTO_VENTANA - y_actual - ALTO_IMG_DUCK * FACTOR_ESCALA);
    }
}

void Duck::apuntar_arma(DireccionApuntada direccion) {
    direccion_arma = direccion;
}

bool Duck::esta_quieto() { return quieto; }

void Duck::kill() {
    is_dead = true;
}

void Duck::mover_a(float x, float y, bool is_flapping, bool reset) {
    if (x != x_des || y != y_des) {
        quieto = false;
    }
    x_des = x;
    this->is_flapping = is_flapping;
    this->reset = reset;
    y_des = y;
}

void Duck::agacharse() {
    esta_agachado = true;
}

void Duck::levantarse() {
    esta_agachado = false;
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
    int arma_index = static_cast<int>(weapon.value());
    Area armaSrcArea(arma_index * 38, 0, 38, 38);
    
    int pos_arma_x = 0;
    int pos_arma_y = 0;
    double angle = 0.0;

    switch (direccion_arma) {
        case DireccionApuntada::APUNTADO_ARRIBA:
            if(flip == SDL_FLIP_NONE){
                angle = -90.0;
                pos_arma_x = 20;
            } else {
                pos_arma_x = 10;
                angle = 90.0;
            }
            pos_arma_y = 20;
            break;
        case DireccionApuntada::APUNTADO_DERECHA:
            pos_arma_x = 20;
            pos_arma_y = 25;
            break;
        case DireccionApuntada::APUNTADO_IZQUIERDA:
            pos_arma_x = 10;
            pos_arma_y = 25;
            flip = SDL_FLIP_HORIZONTAL;
            break;
    }
    Area armaDestArea(x_actual + pos_arma_x, y_renderizado + pos_arma_y, 38, 38);
    armas.render(armaSrcArea, armaDestArea, flip, angle);
}

std::string Duck::procesar_color(ColorDuck color){
    switch (color){
        case ColorDuck::AZUL:
            return "_azul";
        case ColorDuck::ROJO:
            return "_rojo";
        case ColorDuck::VERDE:
            return "_verde";
        case ColorDuck::AMARILLO:
            return "_amarillo";
        case ColorDuck::ROSA:
            return "_rosa";
        case ColorDuck::NARANJA:
            return "_naranja";
        case ColorDuck::CELESTE:
            return "_celeste";
        case ColorDuck::NEGRO:
            return "_negro";
        case ColorDuck::BLANCO:
            return "_blanco";
        case ColorDuck::MAX_COLOR:
            return "Max";
        default:
            return "";
    }
}

ColorDuck Duck::get_color() {
    return color;
}
