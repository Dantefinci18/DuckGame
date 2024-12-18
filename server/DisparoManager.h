#ifndef DISPARO_MANAGER_H
#define DISPARO_MANAGER_H

#include "../common/collidables/Player.h"
#include "../common/collidables/Collidable.h"
#include "../common/collidables/Platform.h"
#include "../common/collidables/SpawnPlace.h"
#include "../common/collidables/Box.h"
#include "../common/collidables/SpawnWeaponBox.h"
#include "../common/collidables/SpawnBox.h"
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
                if(collidable->getType() != CollidableType::SpawnPlace && collidable->getType() != CollidableType::SpawnBox){
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
                            //jugador_disparado->morir();
                            jugador_disparado->recibir_disparo();
                        } else {
                            std::cerr << "Error: dynamic_cast a Player falló." << std::endl;
                        }
                        break;
                    }

                    case CollidableType::Platform:
                        break;

                    case CollidableType::Box: {
                        Box* caja_impactada = dynamic_cast<Box*>(primer_impacto);
                        if (caja_impactada && caja_impactada->esta_activa()) {
                            int caja_x = caja_impactada->get_position().x;
                            int caja_y = caja_impactada->get_position().y;

                            EventoCajaDestruida evento_caja_destruida(caja_x, caja_y);
                            eventos.push_back(std::make_shared<EventoCajaDestruida>(evento_caja_destruida));
                            SpawnBox* recompensa = new SpawnBox(Vector(caja_x, caja_y), 20, 20);
                            
                            SpawnBox::ItemType tipo_item = recompensa->get_item_type();

                            if (tipo_item == SpawnBox::ItemType::Weapon) {
                                EventoSpawnArmaBox evento_spawn_arma(caja_x, caja_y, caja_impactada->width, caja_impactada->height, recompensa->get_weapon_type());
                                eventos.push_back(std::make_shared<EventoSpawnArmaBox>(evento_spawn_arma));
                                collidables_a_agregar.push_back(recompensa);
                            } else if (tipo_item == SpawnBox::ItemType::Proteccion) {
                                EventoSpawnProteccionBox evento_spawn_proteccion(caja_x, caja_y, recompensa->get_proteccion_type());
                                eventos.push_back(std::make_shared<EventoSpawnProteccionBox>(evento_spawn_proteccion));
                                collidables_a_agregar.push_back(recompensa);
                            } 
                            //collidables_a_agregar.push_back(recompensa);
                        } else {
                            std::cerr << "Error: dynamic_cast a Box falló." << std::endl;
                        }
                        break;
                    }

                    default:
                        break;
                }
                break; 
            } 
        }
    }
};

#endif // DISPARO_MANAGER_H
