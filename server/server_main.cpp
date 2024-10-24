#define ARGUMENTOS_SERVER 2
#define NOMBRE_SERVER 1

#include "common_retorno.h"
#include "server_servidor.h"

int main(int argc, const char* argv[]) {

    const char* servername;

    if (argc == ARGUMENTOS_SERVER) {
        servername = argv[NOMBRE_SERVER];

    } else {
        return ERROR;
    }

    Servidor servidor(servername);
    servidor.run();

    return EXITO;
}
