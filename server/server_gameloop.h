#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <list>
#include <mutex>
#include <string>
#include <tuple>
#include "DisparoManager.h"
#include "../common/common_queue.h"
#include "../common/common_thread.h"
#include "../common/common_accion.h"
#include "server_monitor.h"
#include "server_mapa.h"
#include "server_leaderboard.h"
#include "bala.h"
#include <filesystem>
#include <random>

namespace fs = std::filesystem;
enum EstadoGameloop{
    EN_ESPERA,
    COMENZADA,
    TERMINADA
};
class Gameloop: public Thread {
private:
    Queue<Accion> comandos_acciones;
    PlayerMonitor monitor;
    std::unordered_map<int, std::shared_ptr<Player>> jugadores;
    unsigned int capacidad_minima;
    unsigned int cantidad_de_jugadores = 0;
    std::mutex mtx;
    std::unique_ptr<Mapa> mapa;
    int color;
    int ticks_round_win_screen;
    bool should_reset_round;
    Leaderboard leaderboard;
    
    std::vector<Bala> balas;  

    void sleep();
    void cargar_acciones();
    void procesar_acciones(std::vector<Accion> acciones, Mapa &mapa);
    Player* get_winner();
    void handle_winner(Player* winner);
    void reset_jugadores(); 
    void procesar_acciones(std::vector<Accion> acciones, std::vector<Collidable*> collidables);

public:
    explicit Gameloop(int id_jugador, unsigned int capacidad_minima, Queue<std::unique_ptr<Evento>>& cola_eventos);

    void agregar_jugador(int id_jugador,Queue<std::unique_ptr<Evento>>& cola_eventos);
    std::vector<int> get_ids();
    void eliminar_jugador(int id_jugador,Queue<std::unique_ptr<Evento>>& cola_eventos);
    void run() override;
    EstadoGameloop get_estado();
    void cerrar_conexiones();
    int getRandomMapIndex();
    Queue<Accion>& get_cola_acciones();
    bool esta_llena();
    bool esta_vacia();
};

#endif
