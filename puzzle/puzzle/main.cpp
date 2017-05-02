#include <iostream>
#include <random>
#include <time.h>
#include "sdl_context.hpp"
#include "game.hpp"
#undef main
using namespace std;

int main() {
	srand(time(NULL));
	context = new SDL_Context(1280, 720);
	game = new Game;
	game->currentLevel = game->levelLoader.next();
	game->currentLevel->shuffle();
	game->run();
	delete game;
	delete context;
	return 0;
}