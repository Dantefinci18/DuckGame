#include <SDL2/SDL.h>
#include <iostream>
#include "Sdl/SdlWindow.h"
#include "Sdl/SdlTexture.h"
#include "cliente.h"
#include "../common/common_socket.h"
#include <QApplication>
#include "interfaz_lobby/mainwindow.h"
#include "../server/Collidable.h"
#include "../server/Platform.h"
#include "../server/server_leaderboard.h"  
#include "cliente_leaderboard.h"
#include "../common/common_color.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Cantidad de argumentos invalida" << std::endl;
        return 1;
    }

    const char* hostname = argv[1];
    const char* servname = argv[2];

    Socket conexion(hostname,servname); 

    ClienteLobby lobby(argc,argv,std::move(conexion));
   return lobby.run();  
}
