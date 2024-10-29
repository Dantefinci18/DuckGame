#include "server_gameloop.h"
#include "../common/estado.h"

Gameloop::Gameloop(Queue<ComandoAccion> &comandos_acciones ,Monitor& monitor):
 comandos_acciones(comandos_acciones), monitor(monitor), player({100.0f, 150.0f}) {}

void Gameloop::run() {
    
    const float targetFPS = 5.0f;
    const float targetFrameTime = 1.0f / targetFPS;

    while (_keep_running) {
        ComandoAccion accion = comandos_acciones.pop();
        auto frameStartTime = std::chrono::high_resolution_clock::now();
        
        if (accion == DERECHA) {
            player.set_direction({1.0f, 0.0f});
        
        } else if (accion == IZQUIERDA) {
            player.set_direction({-1.0f, 0.0f});
        
        } else if (accion == SALTAR) {
            player.jump();
        
        } else {
            player.set_direction({0.0f, 0.0f});
        
        }

        for (auto& platform : platforms) {
            player.update(platform);
        }
        
        Vector pos_pato = player.get_posicion();
        monitor.enviar_estado(pos_pato);
        ejecutar_eventos();
    }
}

void Gameloop::agregar_plataforma(Platform plataforma){
    platforms.push_back(plataforma);
}

void Gameloop::ejecutar_eventos() {

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}