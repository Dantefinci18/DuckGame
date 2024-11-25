#include "cliente_leaderboard.h"

void ClientLeaderboard::update_set(int set) {
    std::string sets = "Game: " + std::to_string(set);
    sets_of_rounds.set_text(sets);
}
void ClientLeaderboard::update_round(int round) {
    return;
}
void ClientLeaderboard::update_map(std::unordered_map<int,int> map) {
    return;
}

void ClientLeaderboard::render(Duck duck) {
    sets_of_rounds.render();
    return;
}

ClientLeaderboard::ClientLeaderboard(SdlWindow& window, int round, int max_rounds, int sets_of_rounds, std::unordered_map<int,int> player_rounds_won) :
    sets_of_rounds("Game: " + std::to_string(sets_of_rounds), window, 20, 100, 30, window.height - 30), 
    max_rounds("MaxRounds: " + std::to_string(max_rounds), window, 20, 100, 30, window.height - 30), 
    round("MaxRounds: " + std::to_string(max_rounds), window, 20, 100, 30, window.height - 30),
    players() {
        //Add textures for each player pointer
    }
