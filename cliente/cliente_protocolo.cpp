#include "cliente_protocolo.h"
#include <ostream>
#include <bitset>
#include <iostream>


ClienteProtocolo::ClienteProtocolo(const char* hostname, const char* servname) : socket(hostname, servname) {}
#include <bitset>
#include <string>
#include <iostream>

bool ClienteProtocolo::enviar_accion(ComandoAccion &accion) {
    bool was_closed = false;

    std::bitset<8> bits(accion); 

    std::vector<uint8_t> dataToSend(8);
    for (int i = 0; i < 8; ++i) {
        dataToSend[7 - i] = bits[i] ? 1 : 0;  
    }

    socket.sendall(dataToSend.data(), dataToSend.size(), &was_closed);

    return !was_closed;  
}





bool ClienteProtocolo::recibir_evento(Evento &evento) {
    bool was_closed = false;
    return was_closed;

}


void ClienteProtocolo::cerrar_conexion() {
    socket.shutdown(2);
    socket.close();
}
