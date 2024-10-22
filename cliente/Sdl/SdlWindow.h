#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

struct SdlWindow {
public:
    /**
     * Ctor standalone
     */
    SdlWindow(int width, int height);
    ~SdlWindow();
    void fill();
    void fill(int r, int g, int b, int alpha);
    void render();
    SDL_Renderer* getRenderer() const;

private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
