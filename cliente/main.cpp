#include <SDL2/SDL.h>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
#include "DuckAnimacion.h"
#include "cliente.h"
#include "lobby.h"
#include <QApplication>
#include "interfaz_lobby/mainwindow.h"

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
    
    QObject::connect(&mainWindow, &MainWindow::crear_partida, [&](){

        Cliente cliente(lobby.get_socket());
        cliente.start();  
    });

    return app.exec();  
}
