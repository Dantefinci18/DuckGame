#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "Player.h"
#include <vector>
#include <string>
class Game : Thread {
    private:
    // Only 1 player, obviously change this
    Player player;

    // Obviously change this
    Queue<std::string>& commands;
    public:
    virtual void run() override {
        // Change this to a config
        const float targetFPS = 15.0f;
        auto lastTime = std::chrono::high_resolution_clock::now();
        const float targetDeltaTime = 1.0f / targetFPS;

        while (true) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count() * 1000;
            lastTime = currentTime;   
            if (deltaTime >= targetDeltaTime) {
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

                player.move(targetDeltaTime);
                player.update(targetDeltaTime);
                player.print_position();
            }
        }
    }

    Game(Player& player, Queue<std::string>& queue) : player(player), commands(queue) {}
    using Thread::start;
};