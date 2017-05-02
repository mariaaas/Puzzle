#include "puzzle.hpp"
#include "sdl_context.hpp"

void Tile::calculateTextureClip(int tileWidth, int tileHeight) {
    this->texture_clip.w = tileWidth;
    this->texture_clip.h = tileHeight;
    this->texture_clip.x = x * tileWidth;
    this->texture_clip.y = y * tileHeight;
}

void Tile::calculateRenderClip(int x, int y, int tileWidth, int tileHeight) {
    this->render_clip.w = tileWidth;
    this->render_clip.h = tileHeight;
    this->render_clip.x = x * tileWidth;
    this->render_clip.y = y * tileHeight;
}

Puzzle::Puzzle(const std::string& path) : Puzzle(path, 3) {}
Puzzle::Puzzle(const std::string& path, int netSize) {
    texture.load(path);
    setNetSize(netSize);
}

void Puzzle::swap(int x1, int y1, int x2, int y2) {
	std::swap(tileMap[y1][x1], tileMap[y2][x2]);
    done = checkIfSolved();
    tileMap[y1][x1].calculateRenderClip(x1, y1, renderTileW, renderTileH);
    tileMap[y2][x2].calculateRenderClip(x2, y2 ,renderTileW, renderTileH);
}

void Puzzle::setNetSize(int size) {
    if(size < 2) size = 2;
    if(size > 6) size = 6;
    this->netSize = size;
    textureTileW = texture.getWidth() / netSize;
    textureTileH = texture.getHeight() / netSize;
    renderTileW  = context->getScreenWidth() / netSize;
    renderTileH  = context->getScreenHeight() / netSize;
    calculateTileMap();
}

void Puzzle::shuffle() {
    for(int i = 0; i < netSize * netSize; i++) {
        int x1 = rand() % netSize, y1 = rand() % netSize;
        int x2 = rand() % netSize, y2 = rand() % netSize;
        this->swap(x1, y1, x2, y2);
    }
}

void Puzzle::render() {
    for(int i = 0; i < netSize; i++) {
        for(int j = 0; j < netSize; j++) {
            const Tile& tile = tileMap[i][j];
            texture.render(&tile.texture_clip, &tile.render_clip);
            SDL_RenderDrawRect(context->renderer, &tile.render_clip);
        }
    }
}

void Puzzle::calculateTileMap() {
    tileMap.clear();
    for(int i = 0; i < netSize; i++) {
        tileMap.push_back(std::vector<Tile>());
        for(int j = 0; j < netSize; j++) {
            Tile tile(j, i);
            tile.calculateTextureClip(textureTileW, textureTileH);
            tile.calculateRenderClip(j, i, renderTileW, renderTileH);
            tileMap[i].push_back(tile);
        }
    }
}
bool Puzzle::checkIfSolved() {
    for(int i = 0; i < netSize; i++) {
        for(int j = 0; j < netSize; j++) {
            const Tile& tile = tileMap[i][j];
            if(tile.x != j || tile.y != i) {
                return false;
            }
        }
    }
    return true;
}
