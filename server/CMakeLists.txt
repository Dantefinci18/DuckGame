target_sources(taller_server
    PUBLIC
    Game.h
    Player.h
    Vector.h
    Platform.h
    Collidable.h
    server_aceptador.h
    server_gameloop.h
    server_receiver.h
    server_sender.h
    server_monitor.h
    server_protocolo.h
    server_jugador.h
    server_servidor.h

    PRIVATE
    server_main.cpp
    server_aceptador.cpp 
    server_gameloop.cpp 
    server_receiver.cpp
    server_sender.cpp
    server_monitor.cpp
    server_protocolo.cpp
    server_jugador.cpp
    server_servidor.cpp

)