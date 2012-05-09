#ifndef MAP_H
#define MAP_H

#include "Geometary.h"

class HT1632LEDMatrix;

class Map
{
public:
	Map(int num, uint8_t width, uint8_t height);
	void render(HT1632LEDMatrix* display);
	boolean collides(const Point&) const;
	void generate(int num);
	uint8_t getWidth() const { return width; }
	uint8_t getHeight() const { return height; }
private:
	uint8_t width;
	uint8_t height;
	Line walls[12];
	uint8_t num_walls;
};

#endif
