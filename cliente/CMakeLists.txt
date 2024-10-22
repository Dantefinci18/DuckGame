cmake_minimum_required(VERSION 3.10)
project(DuckGame)

message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_library(sdldemo
  DuckAnimacion.cpp
  Sdl/Area.cpp
  Sdl/SdlTexture.cpp
  Sdl/SdlException.cpp
  Sdl/SdlWindow.cpp
)

add_executable(duckgame main.cpp)
target_link_libraries(duckgame sdldemo SDL2 SDL2_image)
install(FILES ../Imagenes/DuckMovimientos.png DESTINATION ${CMAKE_BINARY_DIR})