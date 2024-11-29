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
message(STATUS "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
# Define target: lib common between client, server and editor programs
# HEY TODO XXX: change the name to something that you like
add_library(taller_common STATIC)

# add the source files that make the lib
# HEY!! TODO XXX: add more subfolders here
add_subdirectory(common/)

# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(taller_common ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(taller_common PUBLIC .)

# Install libSDL2pp (for client or editor)
# HEY!! TODO XXX: add more dependendies (either for client, server or editor)
if(TALLER_CLIENT OR TALLER_EDITOR)
    include(FetchContent)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.8
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-2.8.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.22.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf)
endif()

# Program section
# ---------------
# Client
if(TALLER_CLIENT)
    add_executable(taller_client)
    
    # Make them depend on taller_common lib
    add_dependencies(taller_client taller_common)

    # Add source files and enable warnings
    add_subdirectory(cliente)

    set_project_warnings(taller_client ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link the taller_common lib target
    target_link_libraries(sdldemo SDL2 SDL2_ttf SDL2_image SDL2_mixer)
    target_link_libraries( taller_client taller_common  sdldemo)

    # Qt5 configuration for client
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

if(TALLER_EDITOR)
    add_executable(taller_editor)
    
    # Make them depend on taller_common lib
    add_dependencies(taller_editor taller_common)

    # Add source files and enable warnings
    add_subdirectory(editor)

    set_project_warnings(taller_editor ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    target_link_libraries( taller_editor taller_common )

    # Qt5 configuration for client
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    file(GLOB EDITOR_UISOURCES editor/*.ui)

    qt5_wrap_ui(EDITOR_UIS_HEADERS ${EDITOR_UISOURCES})

    qt5_wrap_cpp(EDITOR_MOC_HEADERS editor/map_editor.h)

    target_include_directories(taller_editor
        PRIVATE
            ${CMAKE_BINARY_DIR}  
    )

    qt5_add_resources(EDITOR_RESOURCES ${CMAKE_SOURCE_DIR}/editor/editor_resources.qrc)

    target_sources(taller_editor PRIVATE ${EDITOR_RESOURCES})

    target_sources(taller_editor
        PRIVATE
            ${EDITOR_UIS_HEADERS}       
            ${EDITOR_MOC_HEADERS}      
    )

    target_link_libraries(taller_editor
        Qt5::Widgets
    )
endif()



if(TALLER_SERVER)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    include(FetchContent)
    FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG master # Puedes cambiar a una versión específica si lo prefieres
    )
    FetchContent_MakeAvailable(yaml-cpp)

    add_executable(taller_server)

    # Make them depend on taller_common lib
    add_dependencies(taller_server taller_common)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(server)

    set_project_warnings(taller_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link the taller_common lib target
    target_link_libraries(taller_server taller_common yaml-cpp)
endif()
