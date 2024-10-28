target_sources(taller_client
  PRIVATE
  main.cpp
  cliente_protocolo.cpp
  cliente.cpp
  cliente_sender.cpp
  cliente_receiver.cpp
  PUBLIC
  cliente_protocolo.h
  cliente.h
  cliente_sender.h
  cliente_receiver.h
  
)

add_library(sdldemo
  DuckAnimacion.cpp

  Sdl/Area.cpp
  Sdl/SdlTexture.cpp
  Sdl/SdlException.cpp
  Sdl/SdlWindow.cpp
)
