#include "duck.h"

#define ANCHO_DUCK_IMG_TOTAL 120
#define ALTO_VENTANA 600
#define DESPLAZAMIENTO_X 6
#define DESPLAZAMIENTO_Y 4
#define FACTOR_ESCALA 2
#define VELOCIDAD_SALTO 15
#define ANCHO_DUCK_IMG 20
#define ALTO_DUCK_IMG 24
#define ANCHO_DUCK 32
#define ALTO_DUCK 48
#define ALTO_BALA 25
#define ANCHO_BALA 11

Duck::Duck(SdlWindow& window, float x_inicial, float y_inicial,ColorDuck color)
    :
      movimientos_en_x("../Imagenes/duck_x" + procesar_color(color) + ".png", window),
      movimiento_en_y("../Imagenes/movimiento_y" + procesar_color(color) + ".png", window),
      armas("../Imagenes/guns.png", window),
      armadura("../Imagenes/Chestplate.png", window),
      casco("../Imagenes/Spikehelm.png", window),
      death("../Imagenes/duckDead" + procesar_color(color) + ".png", window),
      color(color),
      bala("../Imagenes/bullet.png", window),

      quieto(false),                
      weapon(std::nullopt),
      casco_equipado(std::nullopt),
      armadura_equipada(std::nullopt),          
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
    double angle = (direccion_arma == DireccionApuntada::APUNTADO_IZQUIERDA) ? -90 : 90;
    if (direccion_arma == DireccionApuntada::APUNTADO_ARRIBA) {
        angle = 0.0;
    }
            
    Area srcArea(0, 0, ANCHO_BALA, ALTO_BALA);

    
    int x_renderizado = x_bala;
    int y_renderizado = ALTO_VENTANA - y_bala - ALTO_BALA ;
    Area destArea(x_renderizado, y_renderizado, ANCHO_BALA , ALTO_BALA);

    bala.render(srcArea, destArea, flip, angle);
    esta_disparando = false;
    
}


void Duck::render() {
    bool en_movimiento_x = (x_actual != x_des);
    bool en_movimiento_y = (y_actual != y_des);
    //std::cout << "render_duck" << std::endl;
    if (reset) {
        std::cout << "reset" << std::endl;
        weapon = std::nullopt;
        casco_equipado = std::nullopt;
        armadura_equipada = std::nullopt;
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
        Area srcArea(0, 0, ANCHO_DUCK, ALTO_DUCK);
        int y_renderizado = ALTO_VENTANA - y_actual - ALTO_DUCK;
        Area destArea(x_actual, y_renderizado, ALTO_DUCK, ANCHO_DUCK);
        death.render(srcArea, destArea, flip);
        return;
    }

    if (esta_disparando) {
        render_bala();
    }

    if (esta_agachado) {
        Area srcArea(5 * ANCHO_DUCK_IMG, 0, ANCHO_DUCK_IMG, ALTO_DUCK_IMG);
        int y_renderizado = ALTO_VENTANA - y_actual - ALTO_DUCK;
        Area destArea(x_actual, y_renderizado, ANCHO_DUCK, ALTO_DUCK);
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

        int y_renderizado = ALTO_VENTANA - y_actual - ALTO_DUCK;
        Area srcArea(x_img, 0, ANCHO_DUCK_IMG, ALTO_DUCK_IMG);
        Area destArea(x_actual, y_renderizado, ANCHO_DUCK, ALTO_DUCK);

        if (en_movimiento_y) {
            
            render_movimiento_salto(srcArea, destArea);
        } else if (en_movimiento_x || quieto) {
            Area srcArea(x_img, 0, ANCHO_DUCK_IMG, ALTO_DUCK_IMG);
            movimientos_en_x.render(srcArea, destArea, flip);
        }
    }

    if(armadura_equipada){
        render_armadura(ALTO_VENTANA - y_actual - ALTO_DUCK);
    }

    if (casco_equipado) {
        render_casco(ALTO_VENTANA - y_actual - ALTO_DUCK);
    }

    if (weapon) {
        render_arma(ALTO_VENTANA - y_actual - ALTO_DUCK);
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

void Duck::set_proteccion(ProteccionType proteccion) {
    switch (proteccion) {
        case ProteccionType::Casco: {
            casco_equipado = proteccion;
            break;
        }
        case ProteccionType::Armadura: {
            armadura_equipada = proteccion;
            break;
        }
        case ProteccionType::NoCasco: {
            casco_equipado = std::nullopt;
            break;
        }
        case ProteccionType::NoArmadura: {
            armadura_equipada = std::nullopt;
            break;
        }
        default: {
            casco_equipado = std::nullopt;
            armadura_equipada = std::nullopt;
        }
    }
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
        if (x_img < ANCHO_DUCK_IMG_TOTAL - ANCHO_DUCK_IMG) {
            x_img += ANCHO_DUCK_IMG;
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
        x_img = (x_img == 2 * ANCHO_DUCK_IMG ? 5 * ANCHO_DUCK_IMG : 2 * ANCHO_DUCK_IMG);
    } 
    else if (distancia_vertical > 0) {
        x_img = 3 * ANCHO_DUCK_IMG;
    } else if (distancia_vertical < 0) {
        x_img = (x_img < ANCHO_DUCK_IMG_TOTAL - ANCHO_DUCK_IMG) ? 4 * ANCHO_DUCK_IMG : 0;
    }
}

void Duck::render_idle() {
    x_img = 0;
    movimientos_en_x.render(Area(0, 0, ANCHO_DUCK_IMG, ALTO_DUCK_IMG), 
                            Area(x_actual, ALTO_VENTANA - y_actual - ALTO_DUCK, ANCHO_DUCK, ALTO_DUCK), flip);
}

void Duck::render_movimiento_salto(Area& srcArea, Area& destArea) {
    movimiento_en_y.render(srcArea, destArea, flip);
}

void Duck::render_arma(int y_renderizado) {
    int arma_index = 0;
    int cuadrado = 38;
    switch (weapon.value()){
        case WeaponType::PistolaCowboy:
            arma_index = 0;
            break;
        case WeaponType::PistolaMagnum:
            arma_index = 1;
            break;
        case WeaponType::PistolaDuelos:
            arma_index = 2;
            break;
        case WeaponType::RifleAK47:
            arma_index = 3;
            break;
        case WeaponType::Escopeta:
            arma_index = 4;
            break;
        case WeaponType::PewPewLaser:
            arma_index = 5;
            break;
        case WeaponType::Sniper:
            arma_index = 7;
            break;
        case WeaponType::None:
            arma_index = 0;
            cuadrado = 0;
            break;
        default:
            arma_index = 0;
            cuadrado = 0;
    }
    Area armaSrcArea(arma_index * cuadrado, 0, cuadrado, cuadrado);
    int aux_agachado = 0;
    int pos_arma_x = 0;
    double angle = 0.0;

    if(esta_agachado){
        aux_agachado = 10 ;
    }

    switch (direccion_arma) {
        case DireccionApuntada::APUNTADO_ARRIBA:
            if(flip == SDL_FLIP_NONE){
                angle = -90.0;
                pos_arma_x = ANCHO_DUCK/4;
            } else {
                pos_arma_x = -ANCHO_DUCK/4;
                angle = 90.0;
            }
            break;
        case DireccionApuntada::APUNTADO_DERECHA:
            pos_arma_x = ANCHO_DUCK/4;
            break;
        case DireccionApuntada::APUNTADO_IZQUIERDA:
            pos_arma_x = -ANCHO_DUCK/4;
            flip = SDL_FLIP_HORIZONTAL;
            break;
    }
    Area armaDestArea(x_actual + pos_arma_x, y_renderizado + aux_agachado, ANCHO_DUCK, ALTO_DUCK);
    armas.render(armaSrcArea, armaDestArea, flip, angle);
}

void Duck::render_casco(int y_renderizado){
    if(casco_equipado){
        int pos_casco_x = 2;
        if(flip == SDL_FLIP_NONE){
            pos_casco_x = -8;
        }
        int aux_y = 18;
        if(esta_agachado){
            aux_y = 10;
            if(flip == SDL_FLIP_NONE){
                pos_casco_x += 2;
            } else {
                pos_casco_x -= 2;
            }
        }
        Area cascoSrcArea(0, 0, 128, 128);
        Area cascoDestArea(x_actual + pos_casco_x, y_renderizado - aux_y, 38, 38);
        casco.render(cascoSrcArea, cascoDestArea, flip, 0.0);
    }
}

void Duck::render_armadura(int y_renderizado){
    if(armadura_equipada){
        int aux_y = 0;
        int aux_x = ANCHO_DUCK/2;
        if(esta_agachado){
            if(flip == SDL_FLIP_NONE){
                aux_x -= 5;
            }
            else{
                aux_x += 5;
            }
            aux_y = 5;
        }
        Area armaduraSrcArea(0, 0, 256, 196);
        Area armaduraDestArea(x_actual - aux_x, y_renderizado + aux_y, 65, 65);
        armadura.render(armaduraSrcArea, armaduraDestArea, flip, 0.0); 
    }
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
