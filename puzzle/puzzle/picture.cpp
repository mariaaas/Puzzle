#include "picture.hpp"
#include "sdl_context.hpp"
#include <SDL_image.h>
#include <iostream>
#include <memory>
using namespace std;

Picture::Picture() {}

Picture::~Picture() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}
bool Picture::load(const std::string& path) {
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(imageSurface == nullptr) {
        cerr << IMG_GetError() << endl;
        return false;
    }
    texture = SDL_CreateTextureFromSurface(context->renderer, imageSurface);
    if(texture == nullptr) {
        cerr << SDL_GetError() << endl;
        return false;
    }
    width = imageSurface->w;
    height = imageSurface->h;
    SDL_FreeSurface(imageSurface);
    return true;
}

void Picture::render(const SDL_Rect* texture_clip, const SDL_Rect* render_clip) {
    SDL_RenderCopy(context->renderer, texture, texture_clip, render_clip);
}
