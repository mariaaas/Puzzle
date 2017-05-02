#include <SDL.h>
class SDL_Context {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Context(int w, int h);
    ~SDL_Context();
    int getScreenWidth() {
        return SDL_GetWindowSurface(window)->w;
    }
    int getScreenHeight() {
        return SDL_GetWindowSurface(window)->h;
    }
};

extern SDL_Context* context;


