#include <Arduino.h>
#include "Map.h"

#include "HT1632.h"

Map::Map(int num, uint8_t width, uint8_t height)
: width(width)
, height(height)
, num_walls(0)
{
	generate(num);
}

void Map::generate(int num)
{
	num_walls = 3;
	walls[0] = Line(2, 2, width - 3, 2);
	walls[1] = Line(2, 2, 2, height / 2);
	walls[2] = Line(2, height / 2, width / 2, height / 2);
}

boolean Map::collides(const Point& p) const
{
	// Outsides
	if (p.x < 1 || p.y < 1)
		return true;
	if (p.x >= width - 1 || p.y >= height - 1)
		return true;
	// Walls
	for (uint8_t i = 0; i < num_walls; ++i)
	{
		if (p.x >= walls[i].start.x && p.x <= walls[i].end.x)
			if (p.y >= walls[i].start.y && p.y <= walls[i].end.y)
				return true;
	}
	return false;
}

void Map::render(HT1632LEDMatrix* screen)
{
	screen->drawRect(0, 0, screen->width(), screen->height(), 1);
	for (uint8_t i = 0; i < num_walls; ++i)
	{
		screen->drawLine(walls[i].start.x, walls[i].start.y, walls[i].end.x, walls[i].end.y, 1);
	}
}
