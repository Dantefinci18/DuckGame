#include "foo.h"
#include "Game.h"
#include "Platform.h"
#include <vector>
int main() {
    Player player({100.0f, 150.0f});
    Queue<std::string> commands;
    Platform platform({100.0f, 40.0f}, 100.0, 30.0);
    std::vector<Platform> platforms;
    platforms.push_back(platform);
    Game* game = new Game(player, commands, platforms);
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