/** 
 * @file videolistener.cpp	
 * @brief Interface Video Listener
 * @author María Carrasco Rodríguez
 *
 */

#ifndef VIDEOLISTENER_H
#define VIDEOLISTENER_H

#include <SDL/SDL.h>

namespace mge
{

  class VideoListener
  {
  public:
    VideoListener () {}
    virtual bool handleVideoUpdate (SDL_Event& ev) = 0;
    virtual bool handleVideoResize (SDL_Event& ev) = 0;
  };
  
} /* namespace mge */

#endif /* VIDEOLISTENER_H */
