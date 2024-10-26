#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "Player.h"
#include <vector>
#include <string>
class Game : Thread {
    private:
    // Only 1 player, obviously change this
    Player player;
    std::vector<Platform> platforms;
    // Obviously change this
    Queue<std::string>& commands;
    public:
    virtual void run() override {
        // Change this to a config
        const int targetFPS = 15;
        std::chrono::milliseconds interval(1000 / targetFPS);

        while (true) {
            auto start = std::chrono::steady_clock::now();
            std::string command;
            bool found = commands.try_pop(command);
            if (found) {
                std::cout << "found!" << std::endl;
                if (command == "d") {
                    player.set_direction({1.0f, 0.0f});
                }
                else if (command == "a") {
                    player.set_direction({-1.0f, 0.0f});
                }

                else if (command == "w") {
                    player.jump();
                }
                else if (command == "release") {
                    player.set_direction({0.0f, 0.0f});
                }
            }

            for (auto& platform : platforms) {
                // YOu shouldn't update for each platform. If you want to check all collisiones then pass al collidibles.
                player.update(platform);
            }
            player.print_position();
            for (auto& platform : platforms) {
                platform.print_position();
            }
            
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::this_thread::sleep_for(interval - elapsed);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    Game(Player& player, Queue<std::string>& queue, std::vector<Platform> platforms) : player(player), platforms(platforms), commands(queue) {}
    using Thread::start;
};