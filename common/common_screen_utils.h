#ifndef COMMON_SCREEN_UTILS_H
#define COMMON_SCREEN_UTILS_H
#define ALTO_VENTANA 600
#define ANCHO_VENTANA 800
class ScreenUtils {
    public:
        static int get_y_for_screen(int y, int height) {
            return ALTO_VENTANA - y - height;
        }
};
#endif
