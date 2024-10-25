/*
 * Este es un hack alrededor de un bug de G++ que, a pesar de decirle
 * que use un estándar (véase el Makefile), igualmente usa código
 * que es especifico de GNU (y no POSIX).
 *
 * En particular esto afecta a la funcion `strerror_r`.
 * Cuando se usa el estándar POSIX y `GNU_SOURCE` no esta definido, `strerror_r`
 * retorna un `int`.
 *
 * En cambio, con `GNU_SOURCE`, la función retornar un `char*` y no
 * necesariamente podrán el mensaje de error en el buffer sino como retorno.
 * (véase más abajo), lo cual esta claramente mal.
 *
 * Estos "un-define" están para forzar el uso de POSIX y sacar `GNU_SOURCE`
 * al menos en este `.cpp`.
 * */
#undef _GNU_SOURCE
#undef GNU_SOURCE

#include "common_liberror.h"

LibError::LibError(int error_code, const char* fmt, ...) noexcept {

    va_list args;
    va_start(args, fmt);

    int s = vsnprintf(msg_error, sizeof(msg_error), fmt, args);

    va_end(args);

    if (s < 0) {
        
        msg_error[0] = msg_error[1] = msg_error[2] = '?';
        msg_error[3] = ' ';
        msg_error[4] = '\0';

        
        s = 4;
    } else if (s == sizeof(msg_error)) {
        
    }

    
    strerror_r(error_code, msg_error + s, sizeof(msg_error) - s);

    
    msg_error[sizeof(msg_error) - 1] = 0;
}

const char* LibError::what() const noexcept { return msg_error; }

LibError::~LibError() {}
