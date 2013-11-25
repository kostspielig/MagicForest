

#ifndef MGE_MUSHROOM
#define MGE_MUSHROOM

#include "mesh.h"
#include "entity.h"

class Mushroom : public mge::Entity
{
  float size;
  mge::Point4F m_color;
  
public:
  Mushroom(const mge::Point4F& color = mge::Point4F (0.7, 0, 0, 1));
  ~Mushroom();

  mge::Point4F getColor ()
  { return m_color; }
  
  virtual void update (float delta_xticks);  
  virtual void handleCollision (Entity& col);
  
};
  

#endif /* MGE_MUSHROOM */
