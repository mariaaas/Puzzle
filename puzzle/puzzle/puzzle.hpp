#include <SDL.h>
#include <vector>
#include "picture.hpp"
class Tile {
public:
    int x, y;
    SDL_Rect texture_clip;
    SDL_Rect render_clip;
    Tile(int x, int y) : x(x), y(y) {}
    void calculateTextureClip(int tileWidth, int tileHeight);
    void calculateRenderClip(int x, int y, int tileWidth, int tileHeight);
};

typedef std::vector<std::vector<Tile>> TileMap;

class Puzzle {
    TileMap tileMap;
    int netSize;
    int textureTileW;
    int textureTileH;
    int renderTileW;
    int renderTileH;
    bool done;
    void calculateTileMap();
    bool checkIfSolved();
public:
    Picture texture;
    Puzzle(const std::string& path);
    Puzzle(const std::string& path, int netSize);
    void swap(int x1, int y1, int x2, int y2);
    void setNetSize(int size);
    void shuffle();
    void render();
    Tile& tile(int x, int y) {
        return tileMap[y][x];
    }
    int getNetSize() {
        return netSize;
    }
    int getTextureTileWidth() {
        return textureTileW;
    }
    int getTextureTileHeight() {
        return textureTileH;
    }
    int getRenderTileWidth() {
        return renderTileW;
    }
    int getRenderTileHeight() {
        return renderTileH;
    }
    bool isDone() {
        return done;
    }
};


