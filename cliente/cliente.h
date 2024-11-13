#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente_sender.h"
#include "cliente_receiver.h"
#include "cliente_protocolo.h"
#include "enemigo.h" 
#include "DuckAnimacion.h"
#include "Sdl/SdlWindow.h"
#include <atomic>
#include "../common/common_queue.h"
#include "../common/common_evento.h"
#include "../common/common_accion.h"
#include "../common/common_socket.h"
#include "../server/Collidable.h"
#include <SDL2/SDL.h>
#include <unordered_map>
#include <memory>  


class Cliente {
private:
    int id;
    SdlWindow window;
    DuckAnimacion duck; 
    ClienteProtocolo protocolo;
    ClienteReceiver receiver;
    ClienteSender sender;
    Queue<std::unique_ptr<Evento>> queue_eventos;
    Queue<ComandoAccion> queue_acciones;
    std::atomic<bool> conectado {true};
    std::unordered_map<int, std::unique_ptr<Enemigo>> enemigos;
    std::vector<Collidable*> collidables;

    void ejecutar_juego();
    void procesar_eventos_recibidos();
    void manejar_enemigos(const EventoMovimiento& evento_mov, std::vector<Collidable*> collidables);
    void enviar_accion(ComandoAccion* tecla_anterior, ComandoAccion accion);
    void controlar_eventos_del_teclado(ComandoAccion* tecla_anterior);
    void stop();
    void join();

public:
    explicit Cliente(int id,Socket&& socket,std::vector<Collidable*> collidables, float x_inicial, float y_inicial);
    void start();
    ~Cliente();};

#endif // CLIENTE_H