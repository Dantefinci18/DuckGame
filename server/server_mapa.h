#ifndef SERVER_MAPA_H
#define SERVER_MAPA_H

#include <vector>
#include <memory>
#include <string>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include "Platform.h"
#include "SpawnPlace.h"
#include "Box.h"

class Mapa {
private:
    std::vector<std::unique_ptr<Collidable>> collidables;

public:
    explicit Mapa(int id_mapa);

    std::vector<Collidable*> getCollidables() const;

    Mapa(const Mapa&) = delete;
    Mapa& operator=(const Mapa&) = delete;

    Mapa(Mapa&&) noexcept = default;
    Mapa& operator=(Mapa&&) noexcept = default;

    ~Mapa() = default; 
};

#endif // SERVER_MAPA_H
