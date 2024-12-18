#ifndef SERVER_MAPA_H
#define SERVER_MAPA_H

#include <vector>
#include <memory>
#include <string>
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include "../common/collidables/Platform.h"
#include "../common/collidables/SpawnPlace.h"
#include "../common/collidables/SpawnWeaponBox.h"
#include "../common/collidables/SpawnBox.h"
#include "../common/collidables/Box.h"

namespace fs = std::filesystem;
class Mapa {
private:
    std::vector<std::unique_ptr<Collidable>> collidables;

public:
    explicit Mapa(int id_mapa);

    std::vector<Collidable*> getCollidables() const;

    void agregar_collidables(std::vector<Collidable*> nuevos_collidables);

    Mapa(const Mapa&) = delete;
    Mapa& operator=(const Mapa&) = delete;

    Mapa(Mapa&&) noexcept = default;
    Mapa& operator=(Mapa&&) noexcept = default;

    ~Mapa() = default; 
};

#endif // SERVER_MAPA_H
