
#ifndef MGE_ENTITYMANAGER
#define MGE_ENTITYMANAGER

#include "entity.h"
#include <list>

namespace mge
{

  class EntityManager
  {
    std::list <Entity*> m_ents_static;
    std::list <Entity*> m_ents_dyn;
    
  public:

    ~EntityManager();
    
    void attachEntityStatic (Entity* ente)
    {
      m_ents_static.push_back(ente);
    }

    
    void attachEntityDynamic (Entity* ente)
    {
      m_ents_dyn.push_back(ente);
    }

    void detachEntityStatic (Entity* ente)
    {
      m_ents_static.remove(ente);
    }

    void detachEntityDynamic (Entity* ente)
    {
      m_ents_dyn.remove(ente);
    }

    
    void update (float delta_ticks);
    
  };
    
} /* namespace mge */

#endif /* MGE_ENTITYMANAGER */
