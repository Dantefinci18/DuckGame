#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente_sender.h"
#include "cliente_receiver.h"
#include "cliente_protocolo.h"
#include "cliente_leaderboard.h"
#include "duck.h"
#include "mapa.h"
#include "enemigo.h" 
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlFullscreenMessage.h"
#include <atomic>
#include "../common/common_queue.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include "../common/common_socket.h"
#include "../common/common_color.h"
#include "../server/Collidable.h"
#include "../server/server_leaderboard.h"
#include <SDL2/SDL.h>
#include <unordered_map>
#include <memory>  


class Cliente {
private:
    int id;
    SdlWindow window;
    Duck duck;
    std::unique_ptr<Mapa> mapa;
    ClientLeaderboard leaderboard;
    ClienteProtocolo protocolo;
    ClienteReceiver receiver;
    ClienteSender sender;
    Queue<std::unique_ptr<Evento>> queue_eventos;
    Queue<ComandoAccion> queue_acciones;
    std::atomic<bool> conectado {true};
    std::unordered_map<int, std::unique_ptr<Enemigo>> enemigos;
    std::vector<Collidable*> collidables;
    std::unique_ptr<SdlFullscreenMessage> win_message;

    /*
     * Funcion que ejecuta el juego
     */
    void ejecutar_juego();

    /*
     * Funcion que procesa los eventos recibidos
     */
    void procesar_eventos_recibidos();

    /*
     * Funcion que maneja el movimiento del pato
     * Recibe un evento de movimiento
     */
    void agachar_duck(const EventoAgacharse& evento_agacharse);

    /*
     * Funcion que maneja el movimiento del pato
     * Recibe un evento de movimiento
     */
    void levantarse_duck(const EventoLevantarse& evento_levantarse);


    /*
     * Funcion que maneja los enemigos
     * Recibe un evento de movimiento
     */
    void manejar_enemigos(const EventoMovimiento& evento_mov);

    /*
     * Funcion que maneja el arma
     * Recibe un evento de pickup y un vector de collidables
     */
    void manejar_arma(const EventoPickup& evento_pickup, std::vector<Collidable*> collidables);

    /*
     * Funcion que maneja la muerte
     * Recibe un evento de muerte
     */
    void manejar_muerte(const EventoMuerte& evento_muerte);

    /*
     * Funcion que maneja el spawn de un arma
     * Recibe un evento de spawn de arma y un vector de collidables
     */
    void spawn_arma(const EventoSpawnArma& evento_spawn, std::vector<Collidable*> collidables);

    /*
     * Funcion que envia una accion
     * Recibe un puntero a una accion anterior y una accion
     */
    void enviar_accion(ComandoAccion* tecla_anterior, ComandoAccion accion);

    /*
     * Funcion que controla los eventos del teclado
     * Recibe un puntero a una accion anterior
     */
    void controlar_eventos_del_teclado(ComandoAccion* tecla_anterior);

    /*
     * Funcion que procesa un color
     * Recibe un color
     */
    std::string procesar_color(ColorDuck color);

    /*
     * Funcion que procesa el evento de que alguien gano una ronda.
     */
    void handle_win_screen(const EventoWinRound& evento);
    /*
     * Funcion que para el cliente
     */
    void stop();

    /*
     * Funcion que joinea al hilo
     */
    void join();

public:

    /*
     * Constructor de la clase Cliente, recibe un id, un color, un socket, un vector de collidables, un float con la posicion x inicial y un float con la posicion y inicial
     */
    explicit Cliente(int id,ColorDuck color,Socket&& socket,std::vector<Collidable*> collidables, Leaderboard leaderboard, float x_inicial, float y_inicial);
    
    /*
     * Funcion que inicia el cliente
     */
    void start();

    /*
     * Destructor de la clase Cliente
     */
    ~Cliente();};

#endif // CLIENTE_H