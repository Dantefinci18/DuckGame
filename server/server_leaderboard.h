#ifndef SERVER_LEADERBOARD_H
#define SERVER_LEADERBOARD_H
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
class Leaderboard {

    public:
    std::unordered_map<int, int> player_rounds_won;    
    int round;
    int set_of_rounds;
    int max_rounds;

    /* Notifies the leaderboard of a player winning a round */
    void win_round(int player_id);

    /* Returns 0 if there is no winner yet, otherwise returns the ID of the winner
    *  This method should be used after win_round so that it takes into account the last round to calculate
    *  the match winner.
    */
    int get_match_winner();

    //Leaderboard();

    //explicit Leaderboard(int round, int set_of_rounds, std::unordered_map<int,int> player_rounds_won);

    Leaderboard() : player_rounds_won(), round(1), set_of_rounds(1), max_rounds(2) {}

    Leaderboard(int round, int set_of_rounds, std::unordered_map<int,int> player_rounds_won) :
        player_rounds_won(player_rounds_won), round(round), set_of_rounds(set_of_rounds), max_rounds(2) {}

    std::string to_json() const {
        std::ostringstream oss;

        // Start the JSON object
        oss << "{";

        // Add basic fields
        oss << "\"round\":" << round << ",";
        oss << "\"set_of_rounds\":" << set_of_rounds << ",";
        oss << "\"max_rounds\":" << max_rounds << ",";

        // Add the leaderboard map
        oss << "\"leaderboard\":{";

        bool first = true;
        for (const auto& [player_id, rounds_won] : player_rounds_won) {
            if (!first) {
                oss << ",";
            }
            first = false;

            oss << "\"" << player_id << "\":" << rounds_won;
        }

        // Close the leaderboard map and JSON object
        oss << "}";

        oss << "}";

        return oss.str();
    } 
};
#endif
