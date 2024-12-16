#ifndef PLATFORM_H
#define PLATFORM_H

#include "Collidable.h"
#include <iostream>
#include <vector>

class Platform : public Collidable {
public:
    Platform(Vector position, float width, float height);

    virtual CollidableType getType() const override;

    virtual bool onCollision(Collidable& other) override;

    virtual ~Platform();

    void print_bounding_box() const override;

    virtual void update(std::vector<Collidable*> others) override;

    void print_position() const override;
};

#endif
