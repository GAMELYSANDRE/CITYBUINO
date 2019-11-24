#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <Gamebuino-Meta.h>

// variable for the game
const uint8_t DELAY_MONEY = 10; // seconds before recovering the money

// type of tile
const uint8_t GRASS = 1;
const uint8_t SAND = 2;
const uint8_t SEA = 3;
const uint8_t INFO = 4;
const uint8_t BULL = 5;
const uint8_t ROAD_H = 6;
const uint8_t ROAD_V = 7;
const uint8_t HOME_RED = 8;
const uint8_t POWER_STATION = 9;

const uint8_t ROAD_DR = 20;
const uint8_t ROAD_DL = 21;
const uint8_t ROAD_UR = 22;
const uint8_t ROAD_UL = 23;
const uint8_t ROAD_INT_UP = 24;
const uint8_t ROAD_INT_DOWN = 25;
const uint8_t ROAD_INT_RIGHT = 26;
const uint8_t ROAD_INT_LEFT = 27;
const uint8_t ROAD_INT = 28;

// variable grouping all roads
const uint8_t ROAD = 100;

// variable type error
const uint8_t ERROR_ROAD = 200;

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

const uint8_t Map[900] =
{
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3,
  3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 2, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3,
  3, 3, 2, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3,
  3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3,
  3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
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

#endif
