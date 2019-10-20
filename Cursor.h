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
    uint16_t Line() const;
    uint16_t Column() const;
    uint16_t CameraX() const;
    uint16_t CameraY() const;

    // setters methods
    void State(bool ChangeState);
    void Choice(uint8_t ChangeChoice);
    void Line(uint16_t ChangeLine);
    void Column(uint16_t ChangeColumn);
    void CameraX(uint16_t ChangeCameraX);
    void CameraY(uint16_t ChangeCameraY);
    
    /// method other
    void Display();
    	
private:
    bool m_State; 	       // inactive (0) or active (1)
    Tile *m_TileCursor;    // building tile
    uint8_t m_Choice;	   // choice of the tile
    int16_t m_Line;	  
	int16_t m_Column;
    int16_t m_CameraX;
    int16_t m_CameraY;	  
};


#endif

