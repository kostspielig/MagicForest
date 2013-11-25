

#ifndef MGE_TREEENT
#define MGE_TREEENT

#include "mesh.h"
#include "entity.h"

class TreeEnt : public mge::Entity
{
  bool m_falling;
  bool m_fell;
  mge::Point4F m_rot;
  
public:
  //TreeEnt(const mge::Point4F& color = mge::Point4F (0.25, 0.125, 0, 1));
  TreeEnt (mge::Drawable* mesh);
  ~TreeEnt ();
  virtual void update (float delta_xticks);  
  virtual void handleCollision (Entity& col);

};
  

#endif /* MGE_TREEENT */

