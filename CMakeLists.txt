cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS ON)

project(taller_tp
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/URL-HERE"
    LANGUAGES CXX
)

option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." OFF)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Definir la biblioteca común entre el cliente, servidor y editor
add_library(taller_common STATIC)

# Añadir subdirectorios
add_subdirectory(common/)

# Habilitar warnings para los targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(taller_common ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Directorios de cabeceras para la biblioteca
target_include_directories(taller_common PUBLIC .)

# Instalar libSDL2pp para cliente o editor
if(TALLER_CLIENT OR TALLER_EDITOR)
    include(FetchContent)
    FetchContent_Declare(
        libSDL2pp
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    FetchContent_MakeAvailable(libSDL2pp)
endif()

# Program section
# ---------------
if(TALLER_CLIENT)
    add_executable(taller_client)

    # Añadir dependencia de taller_common
    add_dependencies(taller_client taller_common SDL2pp::SDL2pp)

    # Añadir archivos fuente y habilitar warnings
    add_subdirectory(cliente)

    set_project_warnings(taller_client ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Incluir los headers de SDL2pp
    target_include_directories(taller_client PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Linkear la librería taller_common y SDL2
    target_link_libraries(taller_client taller_common sdldemo SDL2 SDL2_image)
endif()

if(TALLER_SERVER)
    include(FetchContent)
    FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG master # Puedes cambiar a una versión específica si lo prefieres
    )
    FetchContent_MakeAvailable(yaml-cpp)

    add_executable(taller_server)

    # Añadir dependencia de taller_common
    add_dependencies(taller_server taller_common)

    # Añadir archivos fuente y habilitar warnings
    add_subdirectory(server)

    set_project_warnings(taller_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Linkear la librería taller_common y yaml-cpp
    target_link_libraries(taller_server taller_common yaml-cpp)
endif()

if(TALLER_CLIENT)
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    file(GLOB UISOURCES cliente/interfaz_lobby/*.ui)

    qt5_wrap_ui(UIS_HEADERS ${UISOURCES})

    qt5_wrap_cpp(MOC_HEADERS cliente/interfaz_lobby/mainwindow.h)

    target_include_directories(taller_client
        PRIVATE
            ${CMAKE_BINARY_DIR}  
    )

    qt5_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/cliente/interfaz_lobby/resources.qrc)

    target_sources(taller_client PRIVATE ${RESOURCES})

    target_sources(taller_client
        PRIVATE
            ${UIS_HEADERS}       
            ${MOC_HEADERS}      
    )

    target_link_libraries(taller_client
        Qt5::Widgets
        sdldemo
    )
endif()
