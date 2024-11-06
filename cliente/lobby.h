#ifndef LOBBY_H
#define LOBBY_H

#include "../common/common_socket.h"



class Lobby {
public:
    Lobby(const char* hostname, const char* servname);
    ~Lobby();
    Socket get_socket();
private:

    Socket socket;
  
};

#endif // LOBBY_H