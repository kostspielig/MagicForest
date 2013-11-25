/** 
 * @file keylistener.cpp	
 * Interface KeyListener
 * @author María Carrasco Rodríguez
 *
 */

#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <SDL/SDL.h>

namespace mge
{

  class KeyListener
  {
  public:
    virtual ~KeyListener() {}
    virtual bool handleKeyPress (SDL_Event& event) = 0;
    virtual bool handleKeyRelease (SDL_Event& event) = 0;
  };
  
} /* namespace mge */

#endif /* KEYLISTENER_H */
