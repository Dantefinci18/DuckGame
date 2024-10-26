#include "Vector.h"
#include "Collidable.h"
#include "Platform.h"
#include <iostream>
class Player : public Collidable {
    private:
        Vector direction;
        float speed;
        float velocity_y;
        bool jumping;
    public:
    void move() {
        
        velocity_y -= 9.8;
        position.x += direction.x * speed;
        position.y += velocity_y ;
        if (position.y < 0) {
            position.y = 0;
            velocity_y = -9.8;
            jumping = false;
        }
    }

    void set_direction(const Vector& dir) {
        direction = dir;
    }

    void jump() {
        if (!jumping) {
            jumping = true;
            velocity_y = 60.0f;
        }
    }

    void update(Collidable& other) {
        move();
        onCollision(other);
    }
    
    void print_bounding_box() const {
        std::cout << "Player position:" << "\n"
            << "left: " <<  std::to_string(left()) << ", "
            << "right: " <<  std::to_string(right()) << ", "
            << "top: " <<  std::to_string(top()) << ", "
            << "bottom: " <<  std::to_string(bottom()) << std::endl;;
    }

    void print_position() const {
        std::cout << "Player position" << "(" << position.x << ", " << position.y << "), ";
    }

    virtual CollidableType getType() const override {
        return CollidableType::Player;
    }

    virtual void onCollision(Collidable& other) override {
        if (other.getType() == CollidableType::Platform) {
            Platform& platform = static_cast<Platform&>(other);
            
            CollidableSide side = getCollisionSide(platform);
            if (side == CollidableSide::Top) {
                position.y = platform.top();
                jumping = false;  
                velocity_y = -9.8;
            }

            if (side == CollidableSide::Bottom) {
                position.y = platform.bottom();
            }

            if (side == CollidableSide::Left || side == CollidableSide::Right) {
                direction.reverse();
            }

        }
    }
    virtual ~Player() {}
    Player(Vector initialPosition) : Collidable(initialPosition, 10.0f, 20.0f), direction(Vector(0,0)), speed(20.0f), velocity_y(-9.8f), jumping(false) {}
};