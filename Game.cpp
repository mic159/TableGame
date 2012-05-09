#include <Arduino.h>
#include "Game.h"

Game::Game(int map_num, uint8_t width, uint8_t height)
: map(map_num, width, height)
{
	score[0] = 0;
	score[1] = 0;
	players[0].setPosition(1, 1);
	players[1].setPosition(width - 2, height - 2);
}

void Game::update(PS2X* ctrl1, PS2X* ctrl2)
{
	players[0].update(ctrl1, &map);
	players[1].update(ctrl2, &map);
}

void Game::render(HT1632LEDMatrix* display)
{
	map.render(display);
	players[0].render(display);
	players[1].render(display);
}
