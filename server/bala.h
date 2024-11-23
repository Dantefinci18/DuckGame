#ifndef BALA_H
#define BALA_H

class Bala {
public:
    
    float x;           
    float y;           
    float destino_x;  
    float destino_y;  
    float velocidad;    
    bool activa;       

    Bala(float x_inicial, float y_inicial, float direccionX_inicial, float direccionY_inicial, float velocidad_inicial);

    bool actualizar(float delta_time);

    void desactivar();

    bool estaActiva() const;

    float getX() const;
    float getY() const;
};

#endif // BALA_H
