#include <SDL2/SDL.h>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
#include "cliente.h"
#include "lobby.h"
#include <QApplication>
#include "interfaz_lobby/mainwindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"  
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
    float x_inicial = 0;
    float y_inicial = 0;
    ColorDuck color = ColorDuck::MAX_COLOR;

    QObject::connect(&mainWindow, &MainWindow::crear_partida, [&] (const std::string& mapaSeleccionado) {
        lobby.crear_partida(mapaSeleccionado);
        int id = lobby.recibir_id();
        while (collidables.empty()) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            if (evento->get_tipo() == Evento::EventoMapa) {
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
            }
            if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                x_inicial = evento_mov->x;
                y_inicial = evento_mov->y;
                color = evento_mov->color;



            }
        }

        Cliente cliente(id,color,lobby.get_socket(), collidables,x_inicial,y_inicial);
        cliente.start();
    });

    return app.exec();  
}
