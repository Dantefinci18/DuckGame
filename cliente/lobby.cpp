#include "lobby.h"
#include <utility>

Lobby::Lobby(const char* hostname, const char* servname) : socket(hostname, servname) {}

Lobby::~Lobby() {}

Socket Lobby::get_socket() {
    return std::move(socket);
}