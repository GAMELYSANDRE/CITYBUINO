#include "Building.hpp"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Building::Building() :
  m_X(0),
  m_Y(0),
  m_Width(0),
  m_Height(0),
  m_Color(1)
{
  m_Width = random(2, 3);
  m_Height = random(3, 8);
  // Create column
  m_Windows = new bool*[m_Width];
  // create row
  for (uint8_t i = 0; i < m_Width; i++)
  {
    m_Windows[i] = new bool[m_Height];
  }
  // random light ou no light
  for (uint8_t column = 0; column < m_Width; column++)
  {
    for (uint8_t row = 0; row < m_Height; row++)
    {
      uint8_t Light = random(0, 2);// 0 or 1
      if ( Light == 1 )
      {
        m_Windows[column][row] = true;
      }
      else
      {
        m_Windows[column][row] = false;
      }
      //gb.display.print(Light);
      //delay(200);
    }
    gb.display.printf("\n");
  }
  // random color building
  m_Color = random(1, 4);// 1 or 2 or 3
  m_Width = m_Width * 8;
  m_Height = m_Height * 6;
  m_X = 0;
  m_Y = 64 - m_Height;
}

//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Building::~Building()
{
  for (uint8_t column = 0; column < m_Width / 8; column++)
  {
    delete[] m_Windows[column];
  }
  delete[] m_Windows;
}

//----------------------------------------------------------------------
//                       Getters methods
//----------------------------------------------------------------------
bool Building::GetX() const
{
  return (m_X);
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
void Building::SetX(uint8_t ChangeX)
{
  m_X = ChangeX;
}

//----------------------------------------------------------------------
//                        Display Building
//----------------------------------------------------------------------

void Building::Display()
{
  Color Blue = gb.createColor(0, 43, 216);
  Color BlueSide = gb.createColor(0, 27, 135);
  Color Purple = gb.createColor(112, 117, 139);
  Color PurpleSide = gb.createColor(91, 40, 104);
  Color Grey = gb.createColor(120, 156, 177);
  Color GreySide = gb.createColor(60, 78, 88);
  switch (m_Color)
  {
    case 1:
      gb.display.setColor(Blue);
      break;
    case 2:
      gb.display.setColor(Purple);
      break;
    case 3:
      gb.display.setColor(Grey);
      break;
  }
  gb.display.fillRect(m_X, m_Y, m_Width, m_Height);
  switch (m_Color)
  {
    case 1:
      gb.display.setColor(BlueSide);
      break;
    case 2:
      gb.display.setColor(PurpleSide);
      break;
    case 3:
      gb.display.setColor(GreySide);
      break;
  }
  gb.display.fillTriangle(m_X + m_Width, m_Y,
                          m_X + m_Width + 5, m_Y + 5,
                          m_X + m_Width, m_Y + 5);
  gb.display.fillRect(m_X + m_Width, m_Y + 5, 6, m_Height - 5);
  for (uint8_t column = 0; column < m_Width / 8; column++)
  {
    for (uint8_t row = 0; row < m_Height / 6; row++)
    {
      if ( m_Windows[column][row] == true)
      {
        gb.display.setColor(216, 173, 0);
      }
      else
      {
        gb.display.setColor(0, 0, 0);
      }
      gb.display.fillRect(m_X + 2 + (column * 8), ( m_Y + 2 ) + ( row * 6) , 4, 2);
    }
  }
}
