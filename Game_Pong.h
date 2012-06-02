#ifndef GAME_PONG_H
#define GAME_PONG_H

#include "Geometary.h"

class HT1632LEDMatrix;
class PS2X;

class Pad
{
public:
	Pad(uint8_t screen_height, uint8_t x);
	void render(HT1632LEDMatrix* display);
	void update(PS2X*);

	float pos;
	int size;
	float top;
	float bottom;
	uint8_t x;
	uint8_t height;
};

class Ball
{
public:
	Ball(float x, float y, uint8_t width, uint8_t height);
	void render(HT1632LEDMatrix* display);
	void update();
	void setAngle(float angle);

	float x, y;
	float dx, dy;
	uint8_t width, height;
};

class GamePong
{
public:
	GamePong(uint8_t width, uint8_t height);
	
	void render(HT1632LEDMatrix* display);
	void update(PS2X*, PS2X*);
	
private:
	Pad pad_1;
	Pad pad_2;
	Ball ball;
	int score_1;
	int score_2;
	bool invert;
};

#endif
