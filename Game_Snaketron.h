#ifndef GAME_SNAKETRON_H
#define GAME_SNAKETRON_H

#include "Geometary.h"


class Snake
{
public:
	Snake(uint8_t x, uint8_t y);
	void update(PS2X*);
	void render(HT1632LEDMatrix* display);

	struct Segment
	{
		Line shape;
		uint8_t length;
		Segment* next;
		Segment* prev;
	};
	Segment* section_start;
	Segment* section_end;
};

class GameSnaketron
{
public:
	GameSnaketron(uint8_t width, uint8_t height);
	void render(HT1632LEDMatrix* display);
	void update(PS2X*, PS2X*);
	Snake player_1;
	Snake player_2;
	uint8_t width;
	uint8_t height;
};

#endif
