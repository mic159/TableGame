#include <PS2X_lib.h>
#include <HT1632.h>

//#include "Game_Pong.h"
#include "Game_Snaketron.h"

//  - Pins -
// Display
#define DATA 2
#define WR 3
#define CS_1 4
#define CS_2 5
#define CS_3 6
#define CS_4 7

// Controller
#define CTRL_CLK 9
#define CTRL_CMD 11
#define CTRL_DAT 10
#define CTRL_CS_1 12
#define CTRL_CS_2 8


HT1632LEDMatrix screen = HT1632LEDMatrix(DATA, WR, CS_1, CS_2, CS_3, CS_4);
PS2X controller_1;
PS2X controller_2;

void setup()
{
  Serial.begin(9600);
  screen.begin(HT1632_COMMON_8NMOS, HT1632_EXT_VERTICAL);

  controller_1.config_gamepad(CTRL_CLK, CTRL_CMD, CTRL_CS_1, CTRL_DAT, true, false);
  controller_2.config_gamepad(CTRL_CLK, CTRL_CMD, CTRL_CS_2, CTRL_DAT, true, false);
  
  delay(100);
  screen.setTextSize(1);
  screen.setTextColor(1);
  screen.setBrightness(6);
  screen.clearScreen();
  screen.writeScreen();
}


void loop()
{
//  Game game(0, screen.width(), screen.height());
//  GamePong game(screen.width(), screen.height());
  GameSnaketron game(screen.width(), screen.height());
  
  while(true)
  {
    screen.clearScreen();
    controller_1.read_gamepad();
    controller_2.read_gamepad();
    game.update(&controller_1, &controller_2);
    game.render(&screen);
    screen.writeScreen();
    
    delay(10);
  }
}
