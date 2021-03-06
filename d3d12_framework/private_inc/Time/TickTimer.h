#ifndef TICK_TIMER_H
#define TICK_TIMER_H

#include "Time/Timer.h"

/// <summary>
/// Timer based on GetTickCount
/// </summary>
class TickTimer : public Timer
{
  public:
    TickTimer();
    
    /// <summary>
    /// Checks if the specified amount of time has ellapsed between now and the
    /// last stored reference time.  If it has, then the reference time is
    /// updated as well
    /// <summary>
    /// <param name="ms">
    /// desired number of milliseconds to have ellapsed
    /// </param>
    /// <param name="actual_ms">
    /// actual number of milliseconds ellapsed when this function returns true
    /// </param>
    /// <returns>
    /// true  if the requested amount of time has ellapsed
    /// false otherwise
    /// </returns>
    bool CheckDelta(UINT ms, UINT& actual_ms);
    
  private:
    /// <summary>
    /// reference time
    /// </summary>
    DWORD m_ref_time;
};

#endif /* TICK_TIMER_H */
