#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <Gamebuino-Meta.h>
// variable for the main menu
const char* const MainMenuTextEnglish[] =
{
  "NEW GAME",
  "LOAD GAME",
  "TUTORIAL",
  "SETTING",
  "CREDITS"
};
const char* const MainMenuTextFrench[] =
{
  "NOUVEAU JEU",
  "CONTINUER JEU",
  "DIDACTICIEL",
  "OPTIONS",
  "CREDITS"
};
const uint8_t MENU = 100;
const uint8_t NEWGAME = 0;
const uint8_t CONTINUE = 1;
const uint8_t TUTORIAL = 2;
const uint8_t SETTING = 3;
const uint8_t CREDITS = 4;
// variable for the option menu
const char* const SettingMenuTextEnglish[] =
{
  "ENGLISH",
  "FRENCH",
  "-EXIT-"
};
const char* const SettingMenuTextFrench[] =
{
  "ANGLAIS",
  "FRANCAIS",
  "SORTIR"
};
// Translate
const uint8_t PAUSE = 100;
const uint8_t ENGLISH = 0;
const uint8_t FRENCH = 1;
const uint8_t EXIT_SETTING = 2;


// variable for the menu game
const uint8_t NBR_ITEM_MENU = 8;

// variable for the game
const uint8_t DELAY_MONEY = 10; // seconds before recovering the money

// Menu
const uint8_t INFO = 1;
const uint8_t SAVE = 2;
const uint8_t READ = 3;
const uint8_t BULL = 4;
const uint8_t ROAD_H = 5;
const uint8_t HOME_RED = 6;
const uint8_t POWER_STATION = 7;
const uint8_t WATER_TOWER = 8;

// tile map
const uint8_t GRASS = 20;
const uint8_t SAND = 21;
const uint8_t SEA = 22;
// tile road
const uint8_t ROAD_DR = 23;
const uint8_t ROAD_DL = 24;
const uint8_t ROAD_UR = 25;
const uint8_t ROAD_UL = 26;
const uint8_t ROAD_INT_UP = 27;
const uint8_t ROAD_INT_DOWN = 28;
const uint8_t ROAD_INT_RIGHT = 29;
const uint8_t ROAD_INT_LEFT = 30;
const uint8_t ROAD_INT = 31;
const uint8_t ROAD_V = 32;

// variable grouping all roads
const uint8_t ROAD = 100;

// variable type error
const uint8_t ERROR_ROAD = 200;
const uint8_t ERROR_ELEC = 201;
const uint8_t ERROR_WATER = 202;

// camera dimension
const uint8_t NBR_TILES_WIDTH = 14;
const uint8_t NBR_TILES_HEIGHT = 14;

// dimension of the tiles 2D not isometric
const float TILE_WIDTH = 8;
const float TILE_HEIGHT = 8;

// MAP
const uint8_t MAP_LINE = 30;
const uint8_t MAP_COLUMN = 30;
const uint8_t MAP_SPEED = 3;
const uint8_t LIMIT_LEFT = 0;
const uint8_t LIMIT_RIGHT = (MAP_COLUMN * TILE_WIDTH ) -
                            (NBR_TILES_WIDTH * TILE_WIDTH );
const uint8_t LIMIT_UP = 0;
const uint8_t LIMIT_DOWN = (MAP_LINE * TILE_HEIGHT ) -
                           (NBR_TILES_HEIGHT * TILE_HEIGHT );


const uint8_t MAP[900] =
{
  22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
  22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
  22, 22, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22,
  22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 20, 21, 21, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 20, 20, 20, 20, 20, 21, 21, 21, 20, 20, 20, 20, 21, 21, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 20, 20, 20, 20, 20, 20, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 20, 20, 21, 20, 20, 20, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 20, 20, 21, 20, 21, 20, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 20, 20, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 21, 20, 20, 21, 20, 21, 21, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 20, 20, 20, 20, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 21, 20, 20, 20, 20, 21, 21, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 20, 20, 20, 20, 20, 21, 20, 20, 20, 21, 21, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 20, 20, 20, 20, 21, 20, 20, 21, 21, 20, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 20, 20, 20, 21, 20, 20, 21, 21, 20, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 20, 21, 21, 20, 20, 21, 21, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 20, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 20, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 22, 22, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 20, 20, 20, 20, 20, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 22, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 20, 20, 20, 20, 20, 21, 21, 22, 22, 22,
  22, 22, 21, 22, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 20, 20, 21, 21, 21, 22, 22, 22,
  22, 22, 22, 22, 21, 21, 21, 21, 21, 21, 21, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22,
  22, 22, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22,
  22, 22, 22, 22, 22, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
  22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
  22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
  22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22
};

// Sound
const Gamebuino_Meta::Sound_FX SOUND_MENU_1[] =
{
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE, 0, 166, -37, -27, 212, 10},
};
const Gamebuino_Meta::Sound_FX SOUND_CONST[] =
{
  {Gamebuino_Meta::Sound_FX_Wave::NOISE, 1, 111, -52, 0, 32, 5},
};
const Gamebuino_Meta::Sound_FX SOUND_ERROR[] =
{
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE, 0, 162, 57, 0, 200, 2},
};

const Gamebuino_Meta::Sound_FX SOUND_BULL[] =
{
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE, 0, 212, 57, -64, 477, 5},
};

// Logo
// new color
const void IMG_ARROW_RIGHT();
const void IMG_ARROW_RIGHT_UP();
const void IMG_ARROW_RIGHT_DOWN();

const void IMG_ARROW_LEFT();
const void IMG_ARROW_LEFT_UP();
const void IMG_ARROW_LEFT_DOWN();

const void IMG_ARROW_UP();
const void IMG_ARROW_DOWN();

void IMG_NO_ENTRY(uint8_t PosX, uint8_t PosY);

// Save game
const uint8_t MEM_READ = 0;
const uint8_t MEM_SAVE = 1;
const uint8_t MEM_DEL = 2;

#endif
