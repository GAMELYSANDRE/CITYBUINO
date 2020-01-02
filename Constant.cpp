#include "Constant.h"

//----------------------------------------------------------------------
// navigation logo
//----------------------------------------------------------------------

Color SUPERRED = gb.createColor(255, 0, 0);

//     LOGO RIGHT 
const void IMG_ARROW_RIGHT() 
{
  gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(65, 20, 75, 30, 65, 40);
}
const void IMG_ARROW_RIGHT_UP()
{
	gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(65, 5, 75, 5, 75, 15);
}
const void IMG_ARROW_RIGHT_DOWN() 
{
  gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(65, 60, 75, 50, 75, 60);
}

//     LOGO LEFT
const void IMG_ARROW_LEFT() 
{
  gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(5, 30, 15, 20, 15, 40);
}
const void IMG_ARROW_LEFT_UP() 
{
  gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(5, 5, 15, 5, 5, 15);
}
const void IMG_ARROW_LEFT_DOWN()
{
	gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(5, 50, 5, 60, 15, 60);
}
//     LOGO UP
const void IMG_ARROW_UP()
{
	gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(40, 5, 30, 15, 50, 15);
}
//     LOGO DOWN
const void IMG_ARROW_DOWN()
{
	gb.display.setColor(SUPERRED);
  gb.display.fillTriangle(40, 60, 30, 50, 50, 50);
}

void IMG_NO_ENTRY(uint8_t PosX,uint8_t PosY)
{
	gb.display.setColor(SUPERRED);
  gb.display.fillCircle(PosX, PosY, 6);
  gb.display.setColor(WHITE);
  gb.display.fillRect(PosX - 3, PosY -1, 6, 3);
  gb.sound.fx(SOUND_ERROR);
}
