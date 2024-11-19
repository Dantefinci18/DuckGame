#ifndef VECTOR_H
#define VECTOR_H
#include <sstream>
#include <string>
#include <cmath>

class Vector {
    public:
        float x;
        float y;
        Vector(float x, float y) : x(x), y(y) {}
        void reverse() {
            x = -x;
            y = -y;
        }

        Vector operator+(const Vector& other) const {
            return Vector(x + other.x, y + other.y);
        }

        Vector operator-(const Vector& other) const {
            return Vector(x - other.x, y - other.y);
        }

        Vector operator*(float scalar) const {
            return Vector(x * scalar, y * scalar);
        }

        float magnitude() const {
            return std::sqrt(x * x + y * y);
        }

        std::string to_string() const {
            std::ostringstream oss;
            oss << "(" << x << ", " << y << ")";
            return oss.str();
        }
};
#endif
