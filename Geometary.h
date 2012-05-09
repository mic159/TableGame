#ifndef GEOMETARY_H
#define GEOMETARY_H

#include <Arduino.h>

struct Point
{
	Point(uint8_t x, uint8_t y) : x(x), y(y) {}
	Point() : x(0), y(0) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	
	void clamp(uint8_t x_min, uint8_t y_min, uint8_t x_max, uint8_t y_max)
	{
		x = max(min(x, x_max), x_min);
		y = max(min(y, y_max), y_min);
	}
	
	uint8_t x,y;
};

struct Line
{
	Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
	: start(x1, y1), end(x2, y2) {}
	Line(Point start, Point end) : start(start), end(end) {}
	Line() : start(), end() {}
	
	Point start;
	Point end;
};

#endif
