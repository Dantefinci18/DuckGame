#include "server_mapa.h"

Mapa::Mapa(int id_mapa) {
    std::map<int, std::string> map_files = {
        {1, "../server/mapas/mapa_1.yaml"},
        {2, "../server/mapas/mapa_2.yaml"},
        {3, "../server/mapas/mapa_3.yaml"},
    };
    YAML::Node config = YAML::LoadFile(map_files[id_mapa]);

    for (const auto& item : config["collidables"]) {
        std::string tipo = item["type"].as<std::string>();
        Vector posicion(item["x"].as<float>(), item["y"].as<float>());
        float width = item["width"].as<float>();
        float height = item["height"].as<float>();

        if (tipo == "Platform") {
            collidables.push_back(std::make_unique<Platform>(posicion, width, height));
        }

        if (tipo == "SpawnPlace") {
            collidables.push_back(std::make_unique<SpawnPlace>(posicion, width, height));
        }

        if (tipo == "Box") {
            collidables.push_back(std::make_unique<Box>(posicion, width, height));
        }

    }
}

std::vector<Collidable*> Mapa::getCollidables() const {
    std::vector<Collidable*> raw_collidables;
    raw_collidables.reserve(collidables.size());
    for (const auto& collidable : collidables) {
        raw_collidables.push_back(collidable.get()); 
    }
    return raw_collidables;
}

void Mapa::agregar_collidables(std::vector<Collidable*> nuevos_collidables) {
    for (auto& collidable : nuevos_collidables) {
        collidables.push_back(std::unique_ptr<Collidable>(collidable));
        std::cout << "\033[97;42mAGREGO COLLIDABLE AL MAPA\033[0m" << std::endl;
        for (auto& collidable_viejo : collidables) {
        if (collidable_viejo->getType() == CollidableType::Box) {
            Box* box = static_cast<Box*>(collidable_viejo.get());
            if (box->get_position().x == collidable->position.x && box->get_position().y == collidable->position.y){
                box->desactivar();
            }
        }
    }
    }

    
    
}