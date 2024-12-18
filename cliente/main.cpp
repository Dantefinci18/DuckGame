#include <SDL2/SDL.h>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
#include "cliente.h"
#include "lobby.h"
#include <QApplication>
#include "interfaz_lobby/mainwindow.h"

#include "../server/server_leaderboard.h"  
#include "cliente_leaderboard.h"
#include "../common/common_color.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Cantidad de argumentos inválida" << std::endl;
        return 1;
    }

    QApplication app(argc, argv);  

    const char* hostname = argv[1];
    const char* servname = argv[2];

    Lobby lobby(hostname, servname);  
    MainWindow mainWindow(&lobby);    
    mainWindow.show();               

    std::vector<Collidable*> collidables;
    Leaderboard leaderboard; 
    float x_inicial = 0;
    float y_inicial = 0;
    ColorDuck color = ColorDuck::MAX_COLOR;
    int jugador_id = -1;

    QObject::connect(&mainWindow, &MainWindow::crear_partida, [&] (const int cantidad_jugadores) {
        lobby.crear_partida(cantidad_jugadores);
        if (jugador_id == -1) {
            jugador_id = lobby.recibir_id();
        }          std::cout << jugador_id << std::endl;

        while (color == ColorDuck::MAX_COLOR) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            if (evento->get_tipo() == Evento::EventoMapa) {
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
                leaderboard = evento_mapa->leaderboard;
            } else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                if (evento_mov->id == jugador_id) { 
                    x_inicial = evento_mov->x;
                    y_inicial = evento_mov->y;
                    color = evento_mov->color;
                }
            } else if (evento->get_tipo() == Evento::EventoEspera) {
                auto evento_espera = static_cast<EventoEspera*>(evento.get());
                mainWindow.mostrarMensajeEspera(evento_espera->id_partida);
                QApplication::processEvents(); 
            }
        }
        mainWindow.hide();  
        Cliente cliente(jugador_id, color, lobby.get_socket(), collidables, leaderboard, x_inicial, y_inicial);
        cliente.start();
        lobby.reconectar_lobby(hostname, servname);
        mainWindow.restaurar();
        mainWindow.show();
        jugador_id = -1;
        color = ColorDuck::MAX_COLOR;
    });

    QObject::connect(&mainWindow, &MainWindow::cargar_partida, [&]() {       
        lobby.cargar_partida();
        if (jugador_id == -1) {
            jugador_id = lobby.recibir_id();
        }  
        std::cout << jugador_id << std::endl;

        while (true) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            evento->print();
    
            if (evento->get_tipo() == Evento::EventoPartidas) {
                auto evento_partidas = static_cast<EventoPartidas*>(evento.get());
                mainWindow.actualizarListaPartidas(evento_partidas->partidas);
                break;
            }
        }
        color = ColorDuck::MAX_COLOR;

    });


    QObject::connect(&mainWindow, &MainWindow::unirse_partida, [&] (int id_partida) {
        lobby.unirse_partida(id_partida);
        while (color == ColorDuck::MAX_COLOR) {
            QApplication::processEvents(); 
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            if (evento->get_tipo() == Evento::EventoMapa) {
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
                leaderboard = evento_mapa->leaderboard;
            } else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                if (evento_mov->id == jugador_id) {  
                    x_inicial = evento_mov->x;
                    y_inicial = evento_mov->y;
                    color = evento_mov->color;
                }
            } else if (evento->get_tipo() == Evento::EventoEspera) {
                auto evento_espera = static_cast<EventoEspera*>(evento.get());
                mainWindow.mostrarMensajeEspera(evento_espera->id_partida);
            }
        }
        mainWindow.hide();  
        Cliente cliente(jugador_id, color, lobby.get_socket(), collidables, leaderboard, x_inicial, y_inicial);
        cliente.start();
        lobby.reconectar_lobby(hostname, servname);
        mainWindow.restaurar();
        mainWindow.show(); 
        jugador_id = -1;
        color = ColorDuck::MAX_COLOR;
    });

    return app.exec();  
}
