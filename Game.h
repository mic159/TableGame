#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"

class HT1632LEDMatrix;
class PS2X;

class Game
{
public:
	Game(int map_num, uint8_t width, uint8_t height);
	
	void render(HT1632LEDMatrix* display);
	void update(PS2X*, PS2X*);
	
private:
	Map map;
	Player players[2];
	uint8_t score[2];
};

#endif
