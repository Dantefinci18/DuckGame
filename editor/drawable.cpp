#include "drawable.h"

Drawable::Drawable(int x, int y, int w, int h, const std::string& image) : x(x), y(y), 
    w(w), h(h), image(image) {}

Box::Box(int x, int y) : Drawable(x, y, 40, 40, ":/images_editor/images_editor/box.png") {}

SpawnPlace::SpawnPlace(int x, int y) : Drawable(x, y, 50, 50, ":/images_editor/images_editor/gun.png") {}

Platform::Platform(int x, int y, int w, int h) : Drawable(x, y, w, h, ":/images_editor/images_editor/platform.png") {}

/* Supposing incoming x,y has a reference from top left (0,0)*/
bool Drawable::is_within(int point_x, int point_y) {
    // Check if the point is within the Drawable's boundaries
    return (point_x >= x && point_x <= x + w &&
            point_y <= y && point_y >= y - h);
}

YAML::Node Drawable::to_yaml() {
    YAML::Node node;
    node["type"] = to_string(get_type());
    node["x"] = x;
    node["y"] = ALTO_VENTANA - y;
    node["width"] = w;
    node["height"] = h;
    return node;
}