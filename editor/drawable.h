#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include <iostream>
#include <unordered_map>
#include "../common/common_screen_utils.h"
#include <yaml-cpp/yaml.h>
enum DrawableType {
    BoxType,
    SpawnPlaceType,
    PlatformType,
    None
};


const std::unordered_map<DrawableType, std::string> DrawableTypeStrings = {
        {DrawableType::BoxType, "Box"},
        {DrawableType::SpawnPlaceType, "SpawnPlace"},
        {DrawableType::PlatformType, "Platform"}
    };

class Drawable {
    public:
    int x;
    int y;
    int w;
    int h;
    std::string image;
    DrawableType type;
    Drawable(int x, int y, int w, int h, const std::string& image);
    

    static std::string to_string(DrawableType type) {
        return DrawableTypeStrings.at(type);
    }
    bool is_within(int point_x, int point_y);
    virtual DrawableType get_type() const = 0;
    virtual ~Drawable() = default;
    YAML::Node to_yaml();

    
};

class Box : public Drawable {
    public:
    Box(int x, int y);
    DrawableType get_type() const override {
        return DrawableType::BoxType;
    }
};

class SpawnPlace : public Drawable {
    public:
    SpawnPlace(int x, int y);
    DrawableType get_type() const override {
        return DrawableType::SpawnPlaceType;
    }
};
class Platform : public Drawable {
    public:
    Platform(int x, int y, int w, int h);
    DrawableType get_type() const override {
        return DrawableType::PlatformType;
    }
};
#endif
