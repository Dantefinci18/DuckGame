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
    void set_title(const char* titulo);
    SDL_Renderer* getRenderer() const;
    int width;
    int height;

private:
    
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
