target_sources(taller_client
  PRIVATE
  main.cpp
  PUBLIC
)

add_library(sdldemo
  DuckAnimacion.cpp
  Sdl/Area.cpp
  Sdl/SdlTexture.cpp
  Sdl/SdlException.cpp
  Sdl/SdlWindow.cpp
)
