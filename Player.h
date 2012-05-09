#ifndef PLAYER_H
#define PLAYER_H

#include "Geometary.h"

class HT1632LEDMatrix;
class PS2X;
class Map;

class Player
{
public:
	Player();
	void render(HT1632LEDMatrix* screen);
	void update(PS2X*, const Map*);
	void setPosition(int x, int y) {pos.x = x; pos.y = y;}
private:
	Point pos;
};

#endif
