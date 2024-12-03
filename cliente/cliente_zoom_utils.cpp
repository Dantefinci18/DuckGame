#include "duck.h"
#include "enemigo.h"
#include "../common/common_screen_utils.h"
#include <vector>
#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>
#include <algorithm>
#define OFFSET 50
#define MIN_ZOOM_IN 3
class ZoomUtils {
    public:
    static SDL_Rect get_zoom(std::unordered_map<int, std::unique_ptr<Enemigo>>& enemigos_map, 
        Duck& duck, 
        int w, 
        int h) {
        int min_declared_w = w / MIN_ZOOM_IN;
        int min_declared_h = h / MIN_ZOOM_IN;
        std::vector<SDL_Rect> players_transformed = transform_players(enemigos_map, duck, w, h);
        // Calculate a partial width containing all the ducks.
        int min_x = INT32_MAX;
        int max_x = 0;
        int min_y = INT32_MAX;
        int max_y = 0;
        for (auto& player : players_transformed) {
            if (player.x - 2*OFFSET < min_x) {
                min_x = player.x - 2*OFFSET;
            }
            if (player.x + player.w + 2*OFFSET > max_x) {
                max_x = player.x + player.w + 2*OFFSET;
            }
            if (player.y - 2*OFFSET < min_y) {
                min_y = player.y - 2*OFFSET;
            }
            if (player.y + player.h + 2*OFFSET > max_y) {
                max_y = player.y + player.h + 2*OFFSET;
            }
        }
                         

        int width = std::max(min_declared_w, (max_x - min_x + 2 * OFFSET));
        int height = std::max(min_declared_h, (max_y - min_y + 2 * OFFSET));

        // Maintain aspect ration
        float aspect_ratio = static_cast<float>(w) / static_cast<float>(h);
        float actual_aspect = static_cast<float>(width) / static_cast<float>(height);
        if (actual_aspect > aspect_ratio ) {
            height = static_cast<int>(width / aspect_ratio);
        }
        else {
            width = static_cast<int>(height * aspect_ratio);
        }
        
        // Recalculate based on width and height maintaining aspect ratio containing ducks
        int x = min_x ;
        int y = min_y ;

        int recalculated_x = x;
        if (x + width > w) {
            recalculated_x = w - width;
        }

        if (recalculated_x < 0) {
            recalculated_x = 0;
        }
        int recalculated_y = y;
        if (y + height > h) {
            recalculated_y = h - height;
        }

        if (recalculated_y < 0) {
            recalculated_y = 0;
        }

        
        SDL_Rect rect = {recalculated_x,recalculated_y,width,height};
        return rect;
    }

    static std::vector<SDL_Rect> transform_players(std::unordered_map<int, std::unique_ptr<Enemigo>>& enemigos_map,
        Duck& duck, int w, int h) {
        std::vector<SDL_Rect> rects;
        for (auto& enemy : enemigos_map) {
            int x = static_cast<int>(enemy.second->duck.x_actual);
            int y = ScreenUtils::get_y_for_screen(static_cast<int>(enemy.second->duck.y_actual), ANCHO_DUCK_IMG);
            rects.push_back({x, y, ANCHO_DUCK_IMG, ALTO_DUCK_IMG});
        }   
        int x = static_cast<int>(duck.x_actual);
        int y = ScreenUtils::get_y_for_screen(static_cast<int>(duck.y_actual), ANCHO_DUCK_IMG);
        rects.push_back({x, y, ANCHO_DUCK_IMG, ALTO_DUCK_IMG});
        return rects;
    }

};