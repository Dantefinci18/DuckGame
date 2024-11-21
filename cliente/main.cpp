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
#include "ventana_esperando.h"

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
    
    /*QDialog dialog;
    Ui::dialog ui;
    ui.setupUi(&dialog);*/

    std::vector<Collidable*> collidables; 
    float x_inicial = 0;
    float y_inicial = 0;
    ColorDuck color = ColorDuck::MAX_COLOR;
    VentanaEsperando ventanaEsperando; 

    QObject::connect(&mainWindow, &MainWindow::crear_partida, [&] (const std::string& mapaSeleccionado) {
        mainWindow.hide();
        lobby.crear_partida(mapaSeleccionado);
        int id = lobby.recibir_id();

        while (color == ColorDuck::MAX_COLOR) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            
            if(evento->get_tipo() == Evento::EventoEspera){
                ventanaEsperando.show();
            
            }else if(evento->get_tipo() == Evento::EventoMapa){
                ventanaEsperando.hide();
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
            
            }else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                x_inicial = evento_mov->x;
                y_inicial = evento_mov->y;
                color = evento_mov->color;
            }
        }

        Cliente cliente(id,color,lobby.get_socket(), collidables,x_inicial,y_inicial);
        QApplication::quit(); 
        cliente.start();
    });
 

    float x_inicial_dos = 0;
    float y_inicial_dos = 0;
    ColorDuck color_dos = ColorDuck::MAX_COLOR;

    QObject::connect(&mainWindow, &MainWindow::cargar_partida, [&]() {
        mainWindow.hide();
        lobby.cargar_partida();
        int id = lobby.recibir_id();
        
         while (color == ColorDuck::MAX_COLOR) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            
            if(evento->get_tipo() == Evento::EventoEspera){
                ventanaEsperando.show();
            
            }else if(evento->get_tipo() == Evento::EventoMapa){
                ventanaEsperando.hide();
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
            
            }else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                x_inicial = evento_mov->x;
                y_inicial = evento_mov->y;
                color = evento_mov->color;
            }
        }

        Cliente cliente(id,color_dos,lobby.get_socket(), collidables,x_inicial_dos,y_inicial_dos);
        QApplication::quit();
        cliente.start();
        
    });

   return app.exec();  
}
