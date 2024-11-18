#ifndef DISPARO_MANAGER_H
#define DISPARO_MANAGER_H

#include "Player.h"
#include "Collidable.h"
#include "../common/common_evento.h"
#include <vector>
#include <memory>
#include <limits>

class DisparoManager {
public:
    static void procesar_disparo(Player& player, std::vector<Collidable*>& collidables, std::unordered_map<int, Jugador*> jugadores,
                                 std::vector<std::shared_ptr<Evento>>& eventos) {

        if (!player.has_weapon()) {
            return;
        }

        auto destinos = player.disparar();

        Vector origen = player.get_posicion() + Vector(0,1); // ARREGLO PARA LEVANTAR LA LINEA DE TIRO

        for (const auto& destino : destinos) {
            Collidable* primer_impacto = nullptr;
            std::optional<Vector> punto_impacto = std::nullopt;
            float menor_distancia = std::numeric_limits<float>::max();

            for (auto& collidable : collidables) {
                if(collidable->getType() != CollidableType::SpawnPlace){
                    auto interseccion = collidable->intersection_point(origen, destino+Vector(0,1)); // ARREGLO PARA LEVANTAR LA LINEA DE TIRO
                    if (interseccion) {
                        float distancia = (*interseccion - origen).magnitude();
                        if (distancia < menor_distancia) {
                        menor_distancia = distancia;
                        primer_impacto = collidable;
                        punto_impacto = interseccion;
                        }
                    }  
                }
            }

            for (auto& jugador : jugadores) {
                if (jugador.second->get_fisicas() != &player) { 
                    auto interseccion = jugador.second->get_fisicas()->intersection_point(origen, destino);
                    if (interseccion) {
                        float distancia = (*interseccion - origen).magnitude();
                        if (distancia < menor_distancia) {
                            menor_distancia = distancia;
                            primer_impacto = jugador.second->get_fisicas();
                            punto_impacto = interseccion;
                        }
                    }
                }
            }
            player.print_position();
            if (primer_impacto && punto_impacto) {
                switch (primer_impacto->getType()) {
                    case CollidableType::Player:
                        std::cout << "Le pegaste a otro jugador en (" 
                                  << punto_impacto->x << ", " 
                                  << punto_impacto->y << ")" << std::endl;

                        // Lógica para aplicar daño o matar segun sea el caso
                        break;

                    case CollidableType::Platform:
                        std::cout <<"Le pegaste a una plataforma en (" 
                                  << punto_impacto->x << ", " 
                                  << punto_impacto->y << ")" << std::endl;

                        // Que hace aca
                        break;

                    case CollidableType::Box:
                        std::cout << "Le pegaste a una caja en (" 
                                  << punto_impacto->x << ", " 
                                  << punto_impacto->y << ")" << std::endl;

                        // Que hace aca
                        break;

                    default:
                        std::cout << "Impacto desconocido en (" 
                                  << punto_impacto->x << ", " 
                                  << punto_impacto->y << ")" << std::endl;
                        break;
                }
                break;
            } else {
                std::cout << "No hubo impacto en la dirección (" 
                          << destino.x << ", " << destino.y + 1 << ")" << std::endl; // ARREGLO PARA LEVANTAR LA LINEA DE TIRO
            }
        }
    }
};


#endif // DISPARO_MANAGER_H
