#include "server_mapa.h"

Mapa::Mapa(int id_mapa) {
    std::map<int, std::string> map_files = {
        {1, "../server/mapas/mapa_1.yaml"},
    };
    YAML::Node config = YAML::LoadFile(map_files[id_mapa]);
    
    for (const auto& item : config["collidables"]) {
        std::string tipo = item["type"].as<std::string>();
        Vector posicion(item["x"].as<float>(), item["y"].as<float>());
        float width = item["width"].as<float>();
        float height = item["height"].as<float>();

        if (tipo == "Platform") {
            //TODO: Make this not a pointer
            collidables.push_back(new Platform(posicion, width, height));
        }

        if (tipo == "SpawnPlace") {
            collidables.push_back(new SpawnPlace(posicion, width, height));
        }
        // Otros tipos de collidables. Cajas spawnplaces, etc.
    }
}
