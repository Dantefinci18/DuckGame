#ifndef CLIENT_LEADERBOARD_H
#define CLIENT_LEADERBOARD_H
#include <unordered_map>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlText.h"
#include "../common/common_color.h"
#include "../common/common_color_utils.h"
#include "duck.h"
#include "enemigo.h"
#include <memory>
#include <vector>
class ClientLeaderboard {
    private:
    std::unordered_map<int,SdlText> leaderboard;
    SdlText sets_of_rounds;
    int max_rounds;
    SdlText round;
    SdlWindow& window;
    SDL_Color ColorDuckToSDLColor(ColorDuck colorDuck);
    public:
    void update_set(int set);
    void update_round(int round);
    void update_map(std::unordered_map<int,int> map);
    void set_color(ColorDuck color, int player_id);
    void render();
    ClientLeaderboard(SdlWindow& window, int round, int max_rounds, int sets_of_rounds, std::unordered_map<int,int> player_rounds_won);
};
#endif