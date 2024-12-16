#ifndef BOX_H
#define BOX_H

#include "Collidable.h"
#include <iostream>
#include <string>
#include <vector>

class Box : public Collidable {
public:
    Box(Vector position, float width, float height);
    virtual ~Box();

    virtual CollidableType getType() const override;
    virtual bool onCollision(Collidable& other) override;
    virtual void update(std::vector<Collidable*> others) override;
    virtual void print_bounding_box() const override;
    virtual void print_position() const override;

    Vector get_position() const;

    void activar();
    void desactivar();
    bool esta_activa() const;

private:
    bool activa;
};

#endif
