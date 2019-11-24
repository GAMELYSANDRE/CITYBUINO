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
    int8_t Type(uint8_t I, uint8_t J ) const;

    // setters methods
    void Type(uint8_t I, uint8_t J, uint8_t ChangeType);


    // others methods
    void Display();
    void Move();
    void CheckTheTile();
    uint8_t CheckPresenceRoad(uint8_t VerifTile );
    void ResetError(uint8_t I, uint8_t J);

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
