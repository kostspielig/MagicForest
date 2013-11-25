
#ifndef MGE_ENTITY
#define MGE_ENTITY

#include "scenenode.h"

namespace mge
{

  class Entity
  {    
    SceneNode m_node;
    bool m_must_die;
    
  protected:
    float m_radius;

  public:
    Entity ()
      : m_must_die (false)
      , m_radius (0.0)
    {}
    
    ~Entity();
    
    SceneNode& getNode ()
    {
      return m_node;
    }

    const SceneNode& getNode () const
    {
      return m_node;
    }

    float getRadius () const {
      return m_radius;
    }
    
    void kill () {
      m_must_die = true;
    }
    
    bool mustDie () const {
      return m_must_die;
    }
    
    virtual void update (float delta_ticks) {}
    
    virtual void handleCollision (Entity& col) {}
  };
  
} /* namespace mge */

#endif /* MGE_MUSHROOM */
