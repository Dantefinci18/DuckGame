#ifndef CLIENT_LEADERBOARD_H
#define CLIENT_LEADERBOARD_H
#include <unordered_map>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlText.h"
#include "duck.h"
#include "enemigo.h"
#include <memory>
#include <vector>
class ClientLeaderboard {
    private:
    SdlText sets_of_rounds;
    SdlText max_rounds;
    SdlText round;
    std::vector<SdlText> players;

    public:
    void update_set(int set);
    void update_round(int round);
    void update_map(std::unordered_map<int,int> map);
    void render(Duck duck);
    ClientLeaderboard(SdlWindow& window, int round, int max_rounds, int sets_of_rounds, std::unordered_map<int,int> player_rounds_won);
};
#endif