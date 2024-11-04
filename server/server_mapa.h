#include <vector>
#include <memory>
#include "Platform.h"
#include <string>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include <iostream>
#include <filesystem>
class Mapa {
private:
    std::vector<Collidable*> collidables;

public:
    explicit Mapa(int id_mapa);

    const std::vector<Collidable*> getCollidables() const {
        return collidables;
    }
};