#include "cliente_leaderboard.h"

void ClientLeaderboard::update_set(int set) {
    std::string sets = "Game: " + std::to_string(set);
    sets_of_rounds.set_text(sets);
}
void ClientLeaderboard::update_round(int round) {
    std::string round_text = "Round: " + std::to_string(round) + " / " + std::to_string(max_rounds);
    this->round.set_text(round_text);
}
void ClientLeaderboard::update_map(std::unordered_map<int,int> map) {
    std::cout << "entered_updating_map" << std::endl;
    leaderboard.clear();
    int offset_players = 50;
    for (auto& player : map) {
        std::cout << "pushing sdltext!" << std::endl;
        leaderboard.emplace(
            player.first,
            SdlText("Player: " + std::to_string(player.second),
                    this->window, 20, 100, 30, window.height - 130 - offset_players,
                    {0, 0, 0, 0})
        );
        offset_players += offset_players;
    }
}

void ClientLeaderboard::render() {
    sets_of_rounds.render();
    round.render();
    for (auto& text : leaderboard) {
        text.second.render();
    }
}

void ClientLeaderboard::set_color(ColorDuck color, int player_id) {
    for (auto& text : leaderboard) {
        if (text.first == player_id) {
            text.second.set_color(ColorDuckToSDLColor(color));
        }
    }
}

SDL_Color ClientLeaderboard::ColorDuckToSDLColor(ColorDuck colorDuck) {
    uint32_t hexColor = ColorUtils::get_hex(colorDuck); // Obtén el valor hexadecimal

    // Extraer componentes RGBA
    Uint8 r = (hexColor >> 24) & 0xFF; // Los primeros 8 bits
    Uint8 g = (hexColor >> 16) & 0xFF; // Los siguientes 8 bits
    Uint8 b = (hexColor >> 8) & 0xFF;  // Los siguientes 8 bits
    Uint8 a = hexColor & 0xFF;         // Los últimos 8 bits

    // Crear y devolver el SDL_Color
    SDL_Color sdlColor = {r, g, b, a};
    return sdlColor;
}
ClientLeaderboard::ClientLeaderboard(SdlWindow& window, int round, int max_rounds, int sets_of_rounds, std::unordered_map<int,int> player_rounds_won) :
    leaderboard(),
    sets_of_rounds("Game: " + std::to_string(sets_of_rounds), window, 20, 100, 30, window.height - 30, {0,0,0,0}), 
    max_rounds(max_rounds), 
    round("Round: " + std::to_string(round) + " / " + std::to_string(max_rounds), window, 20, 100, 30, window.height - 80, {0,0,0,0}),
    window(window) {
        update_map(player_rounds_won);
    }
