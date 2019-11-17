#include "GBTime.h"

//----------------------------------------------------------------------
//                      Constructors
//----------------------------------------------------------------------

GBTime::GBTime() : 
  m_BeginTime(0), 
  m_TempTime(0) , 
  m_Activate(0)
{
  
}

//----------------------------------------------------------------------
//                       Getters methods
//----------------------------------------------------------------------
unsigned long GBTime::BeginTime() const
{
  return m_BeginTime;
}

unsigned long GBTime::TempTime() const
{
  return m_TempTime;
}

//----------------------------------------------------------------------
//                     Time management methods
//----------------------------------------------------------------------

void GBTime::Reset() 
{
  m_TempTime = 0;
  m_BeginTime = millis();
}

void GBTime::InitBeginTime() 
{
  if ( m_Activate == false )
  {
    m_BeginTime = millis();
    m_Activate = true;
  }
}

void GBTime::IncrementTime() 
{
  m_TempTime = millis() - m_BeginTime;
}


