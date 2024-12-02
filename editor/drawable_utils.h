#ifndef DRAWABLE_UTILS_H
#define DRAWABLE_UTILS_H
#define FACTOR_ESCALA_BOX 2
#include <memory>
#include "../editor/drawable.h"
class DrawableUtils {
    public:
        static std::shared_ptr<Drawable> get_drawable(int x, int y, int w, int h, DrawableType type) {
            if (type == DrawableType::BoxType) {
                return std::make_shared<Box>(x, y);
            }
            if (type == DrawableType::SpawnPlaceType) {
                return std::make_shared<SpawnPlace>(x, y);
            }

            if (type == DrawableType::PlatformType) {
                return std::make_shared<Platform>(x,y,w,h);
            }
            return nullptr;
        }
};
#endif
