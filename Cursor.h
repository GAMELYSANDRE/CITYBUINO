#ifndef __CURSOR__
#define __CURSOR__

#include "Tile.h"
#include "Constant.h"
#include <Gamebuino-Meta.h>

class Cursor
{
  public:
    // constructors
    Cursor();
    // Destructor
    ~Cursor();

    // getters methods
    bool State() const;
    uint8_t Choice() const;
    uint16_t ViewLine() const;
    uint16_t ViewColumn() const;
    uint8_t GridLine() const;
    uint8_t GridColumn() const;
    uint16_t CameraX() const;
    uint16_t CameraY() const;

    // setters methods
    void State(bool ChangeState);
    void Choice(uint8_t ChangeChoice);
    void ViewLine(uint16_t ChangeViewLine);
    void ViewColumn(uint16_t ChangeViewColumn);
    void GridLine(uint8_t ChangeGridLine);
    void GridColumn(uint8_t ChangeGridColumn);
    void CameraX(uint16_t ChangeCameraX);
    void CameraY(uint16_t ChangeCameraY);

    // other methods
    void Display();

  private:
    bool m_State; 	       // inactive (0) or active (1)
    Tile *m_TileCursor;    // building tile
    uint8_t m_Choice;	   // choice of the tile
    int16_t m_ViewLine;    // Screen Position
    int16_t m_ViewColumn;  // Screen Position
    int8_t m_GridLine;    // Grid Position
    int8_t m_GridColumn;  // Grid Position
    int16_t m_CameraX;
    int16_t m_CameraY;
};


#endif
