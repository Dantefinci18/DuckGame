#include "server_leaderboard.h"
//Leaderboard::Leaderboard() : player_rounds_won(), round(1), set_of_rounds(1), max_rounds(2) {}

//Leaderboard::Leaderboard(int round, int set_of_rounds, std::unordered_map<int,int> player_rounds_won) :
//    player_rounds_won(player_rounds_won), round(round), set_of_rounds(set_of_rounds), max_rounds(5) {}

void Leaderboard::win_round(int player_id) {
    player_rounds_won[player_id] = player_rounds_won[player_id] + 1;
}

void Leaderboard::add_player_id(int id) {
    player_rounds_won[id] = 0;
}
int Leaderboard::get_match_winner() {
    // It is not FINAL round of the set yet.
    if (round % max_rounds != 0) {
        round++;
        return 0;
    }

    int won_id = 0;
    int won_amount = 0;
    for (auto& player : player_rounds_won) {
        if (player.second >= 2 && player.second > won_amount) {
            won_id = player.first;
            won_amount = player.second;
        }
    }
    
    round = 1;
    set_of_rounds++;
    return won_id;
}

