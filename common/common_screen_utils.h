#ifndef COMMON_SCREEN_UTILS_H
#define COMMON_SCREEN_UTILS_H
#define ALTO_VENTANA 600
#define ANCHO_VENTANA 800
#define FACTOR_ESCALA_BOX 2
#define FACTOR_ESCALA_ARMA 3
#define FACTOR_ESCALA 2
class ScreenUtils {
    public:
        static int get_y_for_screen(int y, int height) {
            return ALTO_VENTANA - y - height;
        }
};
#endif
