#include <Arduino.h>
#include "Game_Snaketron.h"
#include "HT1632.h"
#include "PS2X_lib.h"

GameSnaketron::GameSnaketron(uint8_t width, uint8_t height)
: width(width)
, height(height)
, player_1(Point(4, 4))
, player_2(Point(width - 5, height - 5))
, playing(true)
{
	player_1.dy = 1;
	player_2.dy = -1;
	pill.x = random(1, width - 2);
	pill.y = random(1, height - 2);
}

void GameSnaketron::render(HT1632LEDMatrix* display)
{
	if (!playing) {
		display->setCursor((width / 2) - (6 * 3 / 2), (height / 2) - 3);
		display->print("END");
	}
	display->drawRect(0, 0, width, height, 1);
	player_1.render(display);
	player_2.render(display);
	display->setPixel(pill.x, pill.y);
}

void GameSnaketron::update(PS2X* controller1, PS2X* controller2)
{
	if (playing) {
		// Update player positions
		static uint8_t a = 0;
		bool move = (++a % 2) == 0;
		bool paused = !player_1.ready || !player_2.ready;
		player_1.update(controller1, paused, move);
		player_2.update(controller2, paused, move);

		// Pill
		if (player_1.body.last->item->end == pill || player_2.body.last->item->end == pill)
		{
			if (player_1.body.last->item->end == pill)
				player_1.target += 5;
			if (player_2.body.last->item->end == pill)
				player_2.target += 5;
			do {
				pill.x = random(1, width - 2);
				pill.y = random(1, height - 2);
			} while (player_1.intersects(pill) || player_2.intersects(pill));
		}

		if (move) {
			// Crash!!
			// Hit eachother
			if (player_1.intersects(player_2.body.last->item->end))
				playing = false;
			if (player_2.intersects(player_1.body.last->item->end))
				playing = false;
			// Hit yourself
			if (player_1.intersects(player_1.body.last->item->end, false))
				playing = false;
			if (player_2.intersects(player_2.body.last->item->end, false))
				playing = false;
			// Went out
			if (player_1.bounds(width, height))
				playing = false;
			if (player_2.bounds(width, height))
				playing = false;
		}
	} else {
		if (controller1->ButtonPressed(PSB_START))
		{
			player_1.reset(Point(4, 4));
			player_2.reset(Point(width - 5, height - 5));
			player_1.dy = 1;
			player_2.dy = -1;
			pill.x = random(1, width - 2);
			pill.y = random(1, height - 2);
			playing = true;
		}
		return;
	}
}

Snake::Snake(const Point& p)
: dx(0), dy(0)
, ready(false)
, length(1)
, target(5)
{
	reset(p);
}

void Snake::reset(const Point& p)
{
	// Delete old body
	while (body.first != NULL)
	{
		delete body.first->item;
		body.Remove(body.first->item);
	}
	
	// reset direction
	dx = 0; dx = 0;
	length = 1;
	target = 5;
	ready = false;
	
	// Insert new body
	Line* s = new Line(p, p);
	body.Add(s);
}

inline int normalise(uint8_t start, uint8_t end)
{
	if (start == end) return 0;
	if (start < end) return 1;
	return -1;
}

void Snake::update(PS2X* c, bool paused, bool move)
{
	if (c->ButtonPressed(PSB_START))
		ready = !ready;

	if (paused)
		return;
		
	if (c->ButtonPressed(PSB_PAD_UP) && dy == 0) {
		dx = 0;
		dy = -1;
		Line* s = new Line(body.last->item->end, body.last->item->end);
		body.Add(s);
	} else if (c->ButtonPressed(PSB_PAD_DOWN) && dy == 0) {
		dx = 0;
		dy = 1;
		Line* s = new Line(body.last->item->end, body.last->item->end);
		body.Add(s);
	} else if (c->ButtonPressed(PSB_PAD_LEFT) && dx == 0) {
		dx = -1;
		dy = 0;
		Line* s = new Line(body.last->item->end, body.last->item->end);
		body.Add(s);
	} else if (c->ButtonPressed(PSB_PAD_RIGHT) && dx == 0) {
		dx = 1;
		dy = 0;
		Line* s = new Line(body.last->item->end, body.last->item->end);
		body.Add(s);
	}

	if (move) {
		body.last->item->end.x += dx;
		body.last->item->end.y += dy;
		++length;
	}
	
	while (length > target)
	{
		int sdx = normalise(body.first->item->start.x, body.first->item->end.x);
		int sdy = normalise(body.first->item->start.y, body.first->item->end.y);
		body.first->item->start.x += sdx;
		body.first->item->start.y += sdy;
		if (body.first->item->start == body.first->item->end && body.first->next != NULL)
		{
			body.Remove(body.first);
		}
		--length;
	}
}

void Snake::render(HT1632LEDMatrix* display)
{
	LinkedList<Line>::Node* s = body.first;
	while (s != NULL)
	{
		display->drawLine(s->item->start.x, s->item->start.y, s->item->end.x, s->item->end.y, 1);
		s = s->next;
	}
	if (!ready)
	{
		display->drawCircle(body.last->item->end.x, body.last->item->end.y, 2, 1);
	}
}

bool Snake::intersects(const Point& p, bool head)
{
	LinkedList<Line>::Node* s = body.first;
	while (s != NULL)
	{
		// If head_segment is false, dont include the last segment
		if (head || s != body.last)
			if (s->item->intersects(p))
				return true;
		s = s->next;
	}
	return false;
}

bool Snake::bounds(uint8_t width, uint8_t height)
{
	if (body.last->item->end.x <= 0 || body.last->item->end.y <= 0)
		return true;
	if (body.last->item->end.x >= width || body.last->item->end.y >= height)
		return true;
	return false;
}

