#include <SDL2/SDL.h>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
#include "cliente.h"
#include "cliente_protocolo.h"
#include "../common/common_socket.h"
#include <QApplication>
#include "interfaz_lobby/mainwindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"  
#include "../common/common_color.h"
#include "../common/common_comando_partida.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Cantidad de argumentos invalida" << std::endl;
        return 1;
    }

    QApplication app(argc, argv);  

    const char* hostname = argv[1];
    const char* servname = argv[2];

    Socket conexion(hostname,servname);
    ClienteProtocolo protocolo(std::move(conexion));  

    MainWindow mainWindow;    
    mainWindow.show();
    mainWindow.agregar_partida("DANTE lol");  
    mainWindow.agregar_partida("alto juego ete");
    
    VentanaNuevaPartida ventanaNuevaPartida;             
    VentanaEsperando ventanaEsperando;

    std::vector<Collidable*> collidables; 
    float x_inicial = 0;
    float y_inicial = 0;
    ColorDuck color = ColorDuck::MAX_COLOR;

    QObject::connect(&mainWindow, &MainWindow::crear_partida, [&] () {
        mainWindow.hide();
        ventanaNuevaPartida.show();
        /*lobby.crear_partida(mapaSeleccionado);
        int id = lobby.recibir_id();
        std::cout <<  id << std::endl;

        while (color == ColorDuck::MAX_COLOR) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            evento->print();
            if(evento->get_tipo() == Evento::EventoEspera){
            
            }else if(evento->get_tipo() == Evento::EventoMapa){
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
            
            }else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                
                if(evento_mov->id == id){
                    x_inicial = evento_mov->x;
                    y_inicial = evento_mov->y;
                    color = evento_mov->color;
                }
            }
        }

        Cliente cliente(id,color,lobby.get_socket(), collidables,x_inicial,y_inicial);
        cliente.start();*/
    });

    QObject::connect(&ventanaNuevaPartida, &VentanaNuevaPartida::volver, [&] () {
        ventanaNuevaPartida.hide();
        mainWindow.show();
    });

    QObject::connect(&ventanaNuevaPartida, &VentanaNuevaPartida::crear_partida, [&] (
        const std::string& nombre, const std::string& mapaSeleccionado, const unsigned int cantidad_de_jugadores) {
            
            ComandoNuevaPartida nueva_partida(nombre,cantidad_de_jugadores);
            protocolo.enviar_comando_partida(nueva_partida);
            ventanaNuevaPartida.hide();
            ventanaEsperando.show();
    });
   /* QObject::connect(&mainWindow, &MainWindow::cargar_partida, [&]() {       
        lobby.cargar_partida();
        //obby.recibir_partidas_disponibles()
        /*int id = lobby.recibir_id();
        std::cout <<  id << std::endl;
        
         while (color == ColorDuck::MAX_COLOR) {
            std::unique_ptr<Evento> evento = lobby.recibir_evento();
            evento->print();
            if(evento->get_tipo() == Evento::EventoEspera){
            
            }else if(evento->get_tipo() == Evento::EventoMapa){
                auto evento_mapa = static_cast<EventoMapa*>(evento.get());
                collidables = evento_mapa->collidables;
            
            }else if (evento->get_tipo() == Evento::EventoMovimiento) {
                auto evento_mov = static_cast<EventoMovimiento*>(evento.get());
                
                if(evento_mov->id == id){
                    x_inicial = evento_mov->x;
                    y_inicial = evento_mov->y;
                    color = evento_mov->color;
                }
            }
        }

        Cliente cliente(id,color,lobby.get_socket(), collidables,x_inicial,y_inicial);
        cliente.start();*/
        
    //});

   return app.exec();  
}
