/**
 * @file eventmanager.cpp
 * @brief Implemention of Data Type EventManager
 * @author María Carrasco Rodríguez
 *
 */

#include "eventmanager.h"

namespace mge
{

  bool EventManager::update ()
  {
    bool exit = true;
    SDL_Event ev;
    
    while (SDL_PollEvent (&ev)) {
      switch (ev.type) {
      case SDL_VIDEOEXPOSE:
	{
	  bool cap = false;
	  std::list<VideoListener*>::iterator it = m_videolist.begin();
	  while (!cap && it != m_videolist.end()) {
	    cap = (*it)->handleVideoUpdate(ev);
	    ++it;
	  }
	}
	break;

      case SDL_VIDEORESIZE:
	{
	  bool cap = false;
	  std::list<VideoListener*>::iterator it = m_videolist.begin();
	  while (!cap && it != m_videolist.end()) {
	    cap = (*it)->handleVideoResize(ev);
	    ++it;
	  }
	}
	break;
	
      case SDL_KEYDOWN:
	{
	  bool cap = false;
	  std::list<KeyListener*>::iterator it = m_keylist.begin();
	  while (!cap && it != m_keylist.end()) {
	    cap = (*it)->handleKeyPress(ev);
	    ++it;
	  }
	}
	break;

      case SDL_KEYUP:
	{
	  bool cap = false;
	  std::list<KeyListener*>::iterator it = m_keylist.begin();
	  while (!cap && it != m_keylist.end()) {
	    cap = (*it)->handleKeyRelease(ev);
	    ++it;
	  }
	}
	break;

      case SDL_MOUSEBUTTONUP:
	{
	  bool cap = false;
	  std::list<MouseListener*>::iterator it = m_mouselist.begin();
	  while (!cap && it != m_mouselist.end()) {
	    cap = (*it)->handleButtonPress(ev);
	    ++it;
	  }
	}
	break;

      case SDL_MOUSEBUTTONDOWN:
	{
	  bool cap = false;
	  std::list<MouseListener*>::iterator it = m_mouselist.begin();
	  while (!cap && it != m_mouselist.end()) {
	    cap = (*it)->handleButtonRelease(ev);
	    ++it;
	  }
	}
	break;

      case SDL_MOUSEMOTION:
	{
	  bool cap = false;
	  std::list<MouseListener*>::iterator it = m_mouselist.begin();
	  while (!cap && it != m_mouselist.end()) {
	    (*it)->handleMouseMove(ev);
	    ++it;
	  }
	}
	break;
	
      case SDL_QUIT:
	exit = false;
	break;
	
      default:
	break;
      }
    }

    return exit;
  }
  
} /* namespace mge */
