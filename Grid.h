#ifndef __GRID__
#define __GRID__


#include "Constant.h"
#include "Tile.h"

#include <Gamebuino-Meta.h>

class Grid
{
  public:
    // constructor
    Grid (const uint8_t Map[], uint8_t NumberLine, uint8_t NumberColumn);
    // Destructor
    ~Grid();

    // getters methods
    uint8_t CameraX() const;
    uint8_t CameraY() const;
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
    Tile **m_Grid;     // table 2 dimensions
    // Position Camera
    uint8_t m_CameraX;
    uint8_t m_CameraY;
    // save tile position following the camera
    uint8_t m_CameraTileX;
    uint8_t m_CameraTileY;
    
    // others methods
    void TestGame();

};

#endif
