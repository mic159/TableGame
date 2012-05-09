#include "Player.h"
#include "Map.h"
#include <PS2X_lib.h>
#include <HT1632.h>

Player::Player()
: pos(0,0)
{}

void Player::update(PS2X* ctrl, const Map* map)
{
	Point newPos(pos);
	if (ctrl->Button(PSB_PAD_UP) || ctrl->Analog(PSS_LY) < 100)
		newPos.y -= 1;
	if (ctrl->Button(PSB_PAD_DOWN) || ctrl->Analog(PSS_LY) > 150)
		newPos.y += 1;
	if (!map->collides(newPos))
		pos = newPos;
	else
		newPos.y = pos.y;
	if (ctrl->Button(PSB_PAD_LEFT) || ctrl->Analog(PSS_LX) < 100)
		newPos.x -= 1;
	if (ctrl->Button(PSB_PAD_RIGHT) || ctrl->Analog(PSS_LX) > 150)
		newPos.x += 1;
	newPos.clamp(1, 1, map->getWidth() - 2, map->getHeight() - 2);
	if (!map->collides(newPos))
		pos = newPos;
}

void Player::render(HT1632LEDMatrix* screen)
{
	screen->setPixel(pos.x, pos.y);
}
