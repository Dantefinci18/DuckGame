#include "Vector.h"
#include <iostream>
class Player {
    private:
        Vector position;
        Vector direction;
        float speed;
        float velocity_y;
        bool jumping;
    public:
    void move(float delta_time) {
        position.x += direction.x * speed * delta_time;
        position.y += direction.y * speed * delta_time;
    }

    void set_direction(const Vector& dir) {
        direction = dir;
    }

    void jump() {
        if (!jumping) {
            jumping = true;
            velocity_y = 200.0f;
        }
    }

    void update(float delta_time) {
        if (jumping) {
            position.y += velocity_y * delta_time;
            velocity_y -= 9.8f * delta_time;
            if (position.y <= 0) {
                position.y = 0;
                jumping = false;
                velocity_y = 0.0f;
            }
        }
    }
    
    void print_position() const {
        std::cout << "Player position: (" << position.x << ", " << position.y << ")\n";
    }

    Player(Vector initialPosition) : position(initialPosition), direction(Vector(0,0)), speed(5.0f) {}
};