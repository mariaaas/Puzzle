#include <memory>
#include <fstream>
#include <map>
#include "puzzle.hpp"

class EventHandler {
	std::map<int, bool> keymap;
	SDL_Event e;
	void process_click();
	void process_key_press();
public:
    int tile_x , tile_y;     
	EventHandler(){ tile_x = -1; };
    void poll_events();
    void keydown(int keysym);
    void keyup(int keysym);
    bool isDown(int keysym);
};

class LevelLoader {
    std::ifstream levelsFile;
public:
    LevelLoader();
    std::unique_ptr<Puzzle> next();
    std::unique_ptr<Puzzle> nextFromDialog();
};

class Game {
    EventHandler eventHandler;
    bool done ;
public:
    LevelLoader levelLoader;
    std::unique_ptr<Puzzle> currentLevel;
    void run();
    void stop();
};

extern Game* game;

