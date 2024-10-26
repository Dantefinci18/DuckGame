target_sources(taller_client
  PRIVATE
  main.cpp
  PUBLIC
)

add_library(sdldemo
  DuckAnimacion.cpp
  cliente_protocolo.cpp
  cliente.cpp
  cliente_sender.cpp
  cliente_receiver.cpp
  Sdl/Area.cpp
  Sdl/SdlTexture.cpp
  Sdl/SdlException.cpp
  Sdl/SdlWindow.cpp
)
