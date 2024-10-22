target_sources(taller_client
  PRIVATE
  main.cpp
  PUBLIC
)

add_library(sdldemo
  Sdl/SdlException.cpp
  Sdl/SdlWindow.cpp
)