#ifndef COMMON_SERIALIZADOR_H
#define COMMON_SERIALIZADOR_H

#include <string>
#include <vector>
#include <cstdint>

#include "../common/common_accion.h"
#include "../common/common_evento.h"

class Serializador {
public:

    std::vector<uint8_t> serializar_accion(ComandoAccion &accion);

    ComandoAccion deserializar_accion(const uint8_t* data);

    std::vector<uint8_t> serializar_evento(const Evento& evento);

    Evento deserializar_evento(const uint8_t* tipo_data, const uint8_t* x_data, const uint8_t* y_data, const uint8_t* id_data, const uint8_t* id2_data);

    std::vector<uint8_t> serializar_id(int id);
    int deserializar_id(const uint8_t* id_binary);

    void imprimir_uint8_t_array(const uint8_t* array, size_t size);

};
#endif //COMMON_SERIALIZADOR_H