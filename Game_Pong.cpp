#include <Arduino.h>
#include "Game_Pong.h"
#include "HT1632.h"
#include "PS2X_lib.h"

GamePong::GamePong(uint8_t width, uint8_t height)
: pad_1(height, 0)
, pad_2(height, width - 1)
, ball(width / 2, height / 2, width, height)
, score_1(0)
, score_2(0)
, invert(false)
{
}

void GamePong::update(PS2X* ctrl1, PS2X* ctrl2)
{
	pad_1.update(ctrl1);
	pad_2.update(ctrl2);
	ball.update();
	if (ball.x <= 1)
	{
		if (ball.y >= pad_1.top && ball.y <= pad_1.bottom)
		{
			// Hit
			ball.x = 1;
			float intersect_norm = -(pad_1.pos - ball.y) / (pad_1.size / 2);
			float reflect_angle = intersect_norm * 0.785398163f;
			ball.setAngle(reflect_angle);
		} else {
			// Score (p2)
			score_2 += 1;
			invert = true;
			ball.x = 1;
			ball.dx = -ball.dx;
		}
	} else if (ball.x >= ball.width - 2) {
		if (ball.y >= pad_2.top && ball.y <= pad_2.bottom)
		{
			// Hit
			ball.x = ball.width - 2;
			float intersect_norm = (pad_2.pos - ball.y) / (pad_2.size / 2);
			float reflect_angle = intersect_norm * 0.785398163f + 3.14159265f;
			ball.setAngle(reflect_angle);
		} else {
			// Score (p1)
			score_1 += 1;
			invert = true;
			ball.x = ball.width - 2;
			ball.dx = -ball.dx;
		}
	}
}

void GamePong::render(HT1632LEDMatrix* display)
{
	if (invert)
	{
		display->fillScreen();
		invert = false;
	}
	if (score_1 < 10)
		display->setCursor(display->width() / 2 - (6), 1);
	else if (score_1 < 100)
		display->setCursor(display->width() / 2 - (6 * 2), 1);
	else
		display->setCursor(display->width() / 2 - (6 * 3), 1);
	display->print(score_1, DEC);
	display->print(score_2, DEC);
	pad_1.render(display);
	pad_2.render(display);
	ball.render(display);
	display->drawLine(0, 0, display->width(), 0, 1);
	display->drawLine(0, display->height() - 1, display->width(), display->height() - 1, 1); 
}

Ball::Ball(float x, float y, uint8_t width, uint8_t height)
: x(x)
, y(y)
, dx(0)
, dy(0)
, width(width)
, height(height)
{
	setAngle(0.523598776f); // 30 degrees
}

void Ball::setAngle(float angle)
{
	dx = cos(angle);
	dy = sin(angle);
}

void Ball::render(HT1632LEDMatrix* display)
{
	display->setPixel(x, y);
}

void Ball::update()
{
    x += dx;
    y += dy;
    if (y >= height - 1)
    {
        dy = -dy;
        y = height - 1;
    }
    else if (y <= 1)
    {
        dy = -dy;
        y = 1;
    }
    
}

Pad::Pad(uint8_t screen_height, uint8_t x)
: height(screen_height)
, pos(screen_height / 2)
, size(8)
, x(x)
{
	top = (pos - (size / 2));
	bottom = (pos + (size / 2));
}

void Pad::update(PS2X* c)
{
	pos += ((float)(c->Analog(PSS_LY) - 128) / 256) * 1.5;
	if (c->Button(PSB_PAD_UP))
	{
		pos -= 1;
	}
	if (c->Button(PSB_PAD_DOWN))
	{
		pos += 1;
	}
	if (pos < 0) pos = 0;
	if (pos > height) pos = height;
	top = (pos - (size / 2));
	bottom = (pos + (size / 2));
}

void Pad::render(HT1632LEDMatrix* display)
{
    display->drawLine(x, top, x, bottom - 1, 1);
}
