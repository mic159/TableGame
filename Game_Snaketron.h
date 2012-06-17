#ifndef GAME_SNAKETRON_H
#define GAME_SNAKETRON_H

#include "Geometary.h"
#include "LinkedList.h"

class PS2X;
class HT1632LEDMatrix;

class Snake
{
public:
	Snake(const Point&);
	void update(PS2X*, bool paused, bool move);
	void render(HT1632LEDMatrix* display);
	
	void reset(const Point&);
	bool intersects(const Point&, bool head = true);
	bool bounds(uint8_t width, uint8_t height);

	LinkedList<Line> body;
	
	uint8_t dx, dy;
	bool ready;
	uint16_t length;
	uint16_t target;
};

class GameSnaketron
{
public:
	GameSnaketron(uint8_t width, uint8_t height);
	void render(HT1632LEDMatrix* display);
	void update(PS2X*, PS2X*);
	
	Snake player_1;
	Snake player_2;
	uint8_t width, height;
	bool playing;
	Point pill;
};

#endif
