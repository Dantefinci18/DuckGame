#include "foo.h"
#include "Game.h"
int main() {
    Player player({0.0f, 0.0f});
    Queue<std::string> commands;
    Game* game = new Game(player, commands);
    game->start();

    while (true) {
        std::string command;
        std::getline(std::cin, command);
        if (command == "q") {
            break;
        }
        commands.push(command);
    }
}