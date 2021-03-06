
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>

#include "keylistener.h"
#include "mouselistener.h"
#include "videolistener.h"

namespace mge
{

  class EventManager
  {
    std::list<KeyListener*> m_keylist;
    std::list<MouseListener*> m_mouselist;
    std::list<VideoListener*> m_videolist;
    
  public:
    void addKeyListener (KeyListener* keyl) {
      m_keylist.push_back (keyl);
    }

    void deleteKeyListener (KeyListener* keyl) {
      m_keylist.remove (keyl);
    }

    void addMouseListener (MouseListener* mousel) {
      m_mouselist.push_back (mousel);
    }

    void deleteMouseListener (MouseListener* mousel) {
      m_mouselist.remove (mousel);
    }

    void addVideoListener (VideoListener* videol) {
      m_videolist.push_back (videol);
    }

    void deleteVideoListener (VideoListener* videol) {
      m_videolist.remove (videol);
    }

    bool update ();
  };
  
} /* namespace mge */

#endif /* EVENTMANAGER_H */
