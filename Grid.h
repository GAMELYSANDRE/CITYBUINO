#ifndef __GRID__
#define __GRID__


#include "Constant.h"
#include "Tile.h"

#include <Gamebuino-Meta.h>

class Grid
{
  public:
    // constructor
    Grid (const uint8_t Map[], int NumberLine, int NumberColumn);
    // Destructor
    ~Grid();

    // getters methods
    int NumberLine() const;
    int16_t CameraX() const;
    int16_t CameraY() const;

    // others methods
    void Display();
    void Move();

  private:
    // Grid dimension
    int m_NumberLine;
    int m_NumberColumn;
    Tile **m_Grid;     // table 2 dimensions
    // Position Camera
    int16_t m_CameraX;
    int16_t m_CameraY;

};

#endif
