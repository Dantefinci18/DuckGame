#ifndef VECTOR_H
#define VECTOR_H
class Vector {
    public:
        float x;
        float y;
        Vector(float x, float y) : x(x), y(y) {}
        void reverse() {
            x = -x;
            y = -y;
        }
};
#endif
