/** 
 * @file mouselistener.cpp	
 * @brief Interface Mouse Listener
 * @author María Carrasco Rodríguez
 *
 */

#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <SDL/SDL.h>

namespace mge
{

  class MouseListener
  {
  public:
    virtual ~MouseListener() {}
    virtual bool handleButtonPress (SDL_Event& event) = 0;
    virtual bool handleButtonRelease (SDL_Event& event) = 0;
    virtual bool handleMouseMove (SDL_Event& event) = 0;
  };
  
} /* namespace mge */

#endif /* MOUSELISTENER_H */

