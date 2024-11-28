#ifndef DISPARO_MANAGER_H
#define DISPARO_MANAGER_H

#include "Player.h"
#include "Collidable.h"
#include "Platform.h"
#include "SpawnPlace.h"
#include "Box.h"
#include "SpawnWeaponBox.h"
#include "bala.h"
#include "../common/common_evento.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <limits>
#include <iostream>

class DisparoManager {
public:
    static void procesar_disparo(Player& player, std::vector<Collidable*>& collidables, std::unordered_map<int, std::shared_ptr<Player>>jugadores, std::vector<Bala>& balas, std::vector<std::shared_ptr<Evento>>& eventos, std::vector<Collidable*>& collidables_a_agregar) {
        
        if (!player.has_weapon()) {
            return;
        }

        auto destinos = player.disparar();

        Vector origen = player.get_posicion_arma();

        for (const auto& destino : destinos) {
            Collidable* primer_impacto = nullptr;
            std::optional<Vector> punto_impacto = std::nullopt;
            float menor_distancia = std::numeric_limits<float>::max();
            Vector punto_final = destino;

            for (auto& collidable : collidables) {
                if(collidable->getType() != CollidableType::SpawnPlace && collidable->getType() != CollidableType::SpawnWeaponBox){
                    auto interseccion = collidable->intersection_point(origen, destino);
                    if (interseccion) {
                        float distancia = (*interseccion - origen).magnitude();

                        if (collidable->getType() == CollidableType::Box) {
                            Box* caja = dynamic_cast<Box*>(collidable);
                            if (caja && !caja->esta_activa()) {
                                continue;
                            }
                        }

                        if (distancia < menor_distancia) {
                            menor_distancia = distancia;
                            primer_impacto = collidable;
                            punto_impacto = interseccion;
                            punto_final = *interseccion;
                        }
                    }
                }
            }

            for (auto& jugador : jugadores) {
                if (jugador.second.get() != &player && 
                    !jugador.second->is_duck_dead() && 
                    !jugador.second->is_agachado()) {

                    auto interseccion = jugador.second->intersection_point(origen, destino);
                    if (interseccion) {
                        float distancia = (*interseccion - origen).magnitude();
                        if (distancia < menor_distancia) {
                            menor_distancia = distancia;
                            primer_impacto = dynamic_cast<Collidable*>(jugador.second.get());
                            punto_impacto = interseccion;
                            punto_final = *interseccion;
                        }
                    }
                }
            }

            Bala nueva_bala(origen.x, origen.y, punto_final.x, punto_final.y, 0.5f); 
            balas.push_back(nueva_bala);

            player.print_position();

            if (primer_impacto && punto_impacto) {
                switch (primer_impacto->getType()) {
                    case CollidableType::Player: {
                        Player* jugador_disparado = dynamic_cast<Player*>(primer_impacto);
                        if (jugador_disparado) {
                            jugador_disparado->morir();
                        } else {
                            std::cerr << "Error: dynamic_cast a Player falló." << std::endl;
                        }
                        break;
                    }

                    case CollidableType::Platform:
                        std::cout << "Le pegaste a una plataforma en (" 
                                  << punto_impacto->x << ", " 
                                  << punto_impacto->y << ")" << std::endl;
                        break;

                    case CollidableType::Box: {
                        Box* caja_impactada = dynamic_cast<Box*>(primer_impacto);
                        if (caja_impactada && caja_impactada->esta_activa()) {
                            float caja_x = caja_impactada->get_position().x;
                            float caja_y = caja_impactada->get_position().y;

                            std::cout << "Le pegaste a una caja en (" 
                                      << caja_x << ", " 
                                      << caja_y << ")" << std::endl;

                            EventoCajaDestruida evento_caja_destruida(caja_x, caja_y);
                            eventos.push_back(std::make_shared<EventoCajaDestruida>(evento_caja_destruida));
                            SpawnWeaponBox* recompensa = new SpawnWeaponBox(Vector(caja_x, caja_y), 20, 20);
                            EventoSpawnArmaBox evento_spawn_arma(caja_x, caja_y, recompensa->get_weapon_type());
                            eventos.push_back(std::make_shared<EventoSpawnArmaBox>(evento_spawn_arma));
                            collidables_a_agregar.push_back(recompensa);
                        } else {
                            std::cerr << "Error: dynamic_cast a Box falló." << std::endl;
                        }
                        break;
                    }

                    default:
                        std::cout << "Impacto desconocido en (" 
                                  << punto_impacto->x << ", " 
                                  << punto_impacto->y << ")" << std::endl;
                        break;
                }
                break; 
            } else {
                std::cout << "No hubo impacto en la dirección (" 
                          << destino.x << ", " << destino.y << ")" << std::endl;
            }
        }
    }
};

#endif // DISPARO_MANAGER_H
