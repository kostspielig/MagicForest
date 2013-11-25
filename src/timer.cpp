/**
 *@file timer.cpp
 * Implementation of Data Type Timer
 *@author María Carrasco Rodríguez
 *
 */

#include <unistd.h>
#include <iostream>
#include <sys/time.h>

#include "timer.h"

using namespace std;

namespace mge
{

  Timer::Timer() :
    nowticks(0),
    sinceticks(0),
    ms(0),
    framecount(0),
    rate(-1),
    rateticks(1)
  {
    reset();
    updateTicks();
  };

  Timer::Timer(int fpsrate):
    nowticks(0),
    sinceticks(0),
    ms(0),
    framecount(0),
    rate(fpsrate),
    rateticks(1000.0/fpsrate)
  {
    reset();
    updateTicks();
  };

  Timer::~Timer()
  {
  }
	
  void Timer::forceFps(int fpsrate)
  {
    framecount = 0;
    rate = fpsrate;
    rateticks = (1000.0 /rate);
  }
	
  void Timer::reset()
  {
    gettimeofday(&start, NULL);
  }

  void Timer::update()
  {
    int lastticks;
    int targetticks;
    
    lastticks = nowticks;
    
    updateTicks();
	
    if (rate > 0) {
      framecount++;
        
      targetticks = sinceticks + int(framecount * rateticks);
		
      if (nowticks <= targetticks)
	usleep((targetticks - nowticks)*1000);
      else {
	framecount = 0;
	updateTicks();
	sinceticks = nowticks;
      }
    } else {
      updateTicks();
    }
    
    ms = nowticks - lastticks;
  }

  void Timer::updateTicks()
  {
    gettimeofday(&now, NULL);
    nowticks =
      (now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec -
					    start.tv_usec) / 1000;
  }

} /* namespace mge */
