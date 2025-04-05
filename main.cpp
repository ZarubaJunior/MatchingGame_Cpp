#include "Card.h"
#include "Game.h"
int main() {

    Game game;

    while (game.isRunning())
    {
        game.update();
        game.render();
    }

    return 0;
	Map map;
	map.SetMap();


	return 0;

}