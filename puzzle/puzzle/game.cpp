#include "game.hpp"
#include "sdl_context.hpp"
#include <nfd.h>
#include <iostream>

using namespace std;

Game* game;

void EventHandler::poll_events() {
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            game->stop();
        break;
        case SDL_MOUSEBUTTONUP:
            process_click();
        break;
        case SDL_KEYDOWN:
            keydown(e.key.keysym.sym);
        break;
        case SDL_KEYUP:
            keyup(e.key.keysym.sym);
            process_key_press();
        break;
        }
    }
}

void EventHandler::keydown(int keysym) {
    keymap[keysym] = true;
}

void EventHandler::keyup(int keysym) {
    keymap[keysym] = false;
}

bool EventHandler::isDown(int keysym) {
    if(keymap.find(keysym) == keymap.end()) {
        return false;
    } else {
        return keymap[keysym];
    }
}

void
EventHandler::process_click() {
    if(tile_x == -1) {
        tile_x = e.button.x / game->currentLevel->getRenderTileWidth();
        tile_y = e.button.y / game->currentLevel->getRenderTileHeight();
    } else {
        int x = e.button.x / game->currentLevel->getRenderTileWidth();
        int y = e.button.y / game->currentLevel->getRenderTileHeight();
        game->currentLevel->swap(tile_x, tile_y, x, y);
        tile_x = -1;
    }
}
void EventHandler::process_key_press() {
    int net_size;
    switch (e.key.keysym.sym) {
	case SDLK_KP_ENTER:
        net_size = game->currentLevel->getNetSize();
        game->currentLevel = game->levelLoader.nextFromDialog();
        game->currentLevel->setNetSize(net_size);
        game->currentLevel->shuffle();
    break;
	case SDLK_RIGHT:
        game->currentLevel->setNetSize(game->currentLevel->getNetSize() + 1);
        game->currentLevel->shuffle();
    break;
	case SDLK_LEFT:
        game->currentLevel->setNetSize(game->currentLevel->getNetSize() - 1);
        game->currentLevel->shuffle();
    break;
    }
}

LevelLoader::LevelLoader() {
    levelsFile.open("resources/levels.txt");
}

std::unique_ptr<Puzzle>
LevelLoader::next() {
    if(levelsFile.is_open()) {
        string path;
        int netSize;
        if(levelsFile >> path >> netSize) {
            return unique_ptr<Puzzle>(new Puzzle("resources/"+path, netSize));
        }
    }
    return nextFromDialog();
}
std::unique_ptr<Puzzle>
LevelLoader::nextFromDialog() {
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog( "png,jpg,bmp", NULL, &outPath );
    if(result == NFD_OKAY) {
        string path = string(outPath);
        return unique_ptr<Puzzle>(new Puzzle(path));
    } else if (result == NFD_CANCEL) {
        game->stop();
    } else {
        exit(1);
    }
    return nullptr;
}

void  Game::run() {
	done = false;
    while (!done) {
        SDL_RenderClear(context->renderer);
        eventHandler.poll_events();
        if(eventHandler.isDown(SDLK_SPACE)) {
            currentLevel->texture.render();
        } else {
            currentLevel->render();
            if(eventHandler.tile_x != -1) {
                const Tile& tile = currentLevel->tile(eventHandler.tile_x, eventHandler.tile_y);
                SDL_SetRenderDrawColor(context->renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderDrawRect(context->renderer, &tile.render_clip);
                SDL_SetRenderDrawColor(context->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
            if(currentLevel->isDone()) {
                SDL_RenderClear(context->renderer);
                currentLevel->texture.render();
                SDL_RenderPresent(context->renderer);
                SDL_Delay(2000);
                currentLevel = levelLoader.next();
                currentLevel->shuffle();
            }
        }
        SDL_RenderPresent(context->renderer);
    }
}
void
Game::stop() {
    done = true;
}
