
target_sources(taller_client
  PRIVATE
    main.cpp
    cliente_protocolo.cpp
    cliente.cpp
    cliente_sender.cpp
    cliente_receiver.cpp
    lobby.cpp
    enemigo.cpp
    mapa.cpp
    duck.cpp
    interfaz_lobby/mainwindow.cpp
    interfaz_lobby/resources.qrc

  PUBLIC
    cliente_protocolo.h
    cliente.h
    cliente_sender.h
    cliente_receiver.h
    lobby.h
    enemigo.h
    mapa.h
    duck.h
    interfaz_lobby/mainwindow.h
)

add_library(sdldemo
  Sdl/Area.cpp
  Sdl/SdlTexture.cpp
  Sdl/SdlException.cpp
  Sdl/SdlWindow.cpp
  Sdl/SdlMessage.cpp
)

target_link_libraries(sdldemo
  ${SDL2_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
)

