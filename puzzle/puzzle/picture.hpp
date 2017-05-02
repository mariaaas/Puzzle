#include <SDL.h>
#include <string>

class Picture {
    SDL_Texture* texture = nullptr;
    int width, height;
public:
    Picture();
    ~Picture();
    bool load(const std::string& path);
    void render(const SDL_Rect* texture_clip = nullptr, const SDL_Rect* render_clip = nullptr);
    int getWidth() {
        return width;
    }
    int getHeight() {
        return height;
    }
};

