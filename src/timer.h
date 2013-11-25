
#ifndef MGE_TIMER_H
#define MGE_TIMER_H

#include <ctime>

namespace mge
{

  class Timer
  {
    timeval now;
    timeval start;
	
    int nowticks;
    int sinceticks;
    int ms;
    int framecount;
    int rate;
    float rateticks;
	
    void updateTicks();
	
  public:
    /** Constructor. */
    Timer();

    /**
     * Constructor which sets a frames per second rate.
     * @param fpsrate The frames per second rate of the timer.
     * @see forceFps
     */
    Timer(int fpsrate);

    /** Destructor. */
    ~Timer();

    /**
     * Makes the timer force a frames per second update rate. This means
     * that every call to @c update() will cause a sleep to force a
     * rate of updates per second as near as possible to the desired one.
     * @param fpsrate The desired fpsrate. Set it to -1 if you no longer want
     * to have a fixed fpsrate.
     */
    //Limita la velocidad y el update causa un retardo adecuado
    void forceFps(int fpsrate);

    /**
     * Resets the timer counts.
     */
    void reset();

    /**
     * Updates the timer.
     */
    void update();

    /**
     * Returns the milliseconds elapsed between the last call to
     * @c update() and the creation of the Timer or the last @c rest call.
     */
    int ticks() {
      return nowticks;
    };

    /**
     * Retusn the milliseconds elapsed between the last two @c update() calls.
     */
    int deltaTicks() {
      return ms;
    };
  };

} /* namespace mge */

#endif /* MGE_TIMER_H */
