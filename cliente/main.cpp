#include <SDL2/SDL.h>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
#include "cliente.h"
#include "lobby.h"
#include <QApplication>
#include "interfaz_lobby/mainwindow.h"
#include "../common/collidables/Collidable.h"
#include "../common/collidables/Platform.h"
#include "../server/server_leaderboard.h"  
#include "cliente_leaderboard.h"
#include "../common/common_color.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Cantidad de argumentos invalida" << std::endl;
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

    QObject::connect(&mainWindow, &MainWindow::crear_partida, [&] (const std::string& mapaSeleccionado) {
        lobby.crear_partida(mapaSeleccionado);
        int id = lobby.recibir_id();

        while (color == ColorDuck::MAX_COLOR) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            evento->print();
            if(evento->get_tipo() == Evento::EventoEspera){
            
            }else if(evento->get_tipo() == Evento::EventoMapa){
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
                leaderboard = evento_mapa->leaderboard;
            
            }else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                
                if(evento_mov->id == id){
                    x_inicial = evento_mov->x;
                    y_inicial = evento_mov->y;
                    color = evento_mov->color;
                }
            }
        }

        Cliente cliente(id,color,lobby.get_socket(), collidables, leaderboard, x_inicial,y_inicial);
        cliente.start();
    });

    QObject::connect(&mainWindow, &MainWindow::cargar_partida, [&]() {       
        lobby.cargar_partida();
        int id = lobby.recibir_id();
        
         while (color == ColorDuck::MAX_COLOR) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            evento->print();
            if(evento->get_tipo() == Evento::EventoEspera){
            
            }else if(evento->get_tipo() == Evento::EventoMapa){
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
                leaderboard = evento_mapa->leaderboard;
            
            }else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                
                if(evento_mov->id == id){
                    x_inicial = evento_mov->x;
                    y_inicial = evento_mov->y;
                    color = evento_mov->color;
                }
            }
        }
        Cliente cliente(id,color,lobby.get_socket(), collidables, leaderboard, x_inicial,y_inicial);
        cliente.start();
        
    });

   return app.exec();  
}
