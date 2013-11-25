
#ifndef MGE_SCENENODE_H
#define MGE_SCENENODE_H

#include <list>
#include <string>
#include "tree.h"
#include "drawable.h"
#include "point.h"
#include "point4.h"

namespace mge
{
  class SceneNode : public TreeNode<std::string, SceneNode>,
		    public Drawable
  {
    std::list<Drawable*> m_draw_add;
    std::list<Drawable*> m_draw_attach;
    PointF m_position;
    PointF m_scale;
    Point4F m_rotate;
      
  public:
    SceneNode();
    ~SceneNode();

    void attachDrawable(Drawable* d) {
      m_draw_attach.push_back(d);
    }

    void detachDrawable(Drawable* d) {
      m_draw_attach.remove(d);
    }

    void addDrawable(Drawable* d) {
      m_draw_add.push_back(d);
    }

    void deleteDrawable(Drawable* d) {
      m_draw_add.remove(d);
    }

    void setPosition(const PointF& pos) {
      m_position = pos;
    }

    void setScale(const PointF& scale) {
      m_scale = scale;
    }

    void setRotate(const Point4F& rotate) {
      m_rotate = rotate;
    }

    PointF getPosition () const {
      return m_position;
    }

    PointF getRealPosition () const {
      return getParent () ?
	m_position + getParent ()->getRealPosition ():
	m_position;
    }

    float getDistance (const SceneNode& nod) const {
      return nod.getParent () == getParent () ?
	(m_position - nod.m_position).length() :
	(getRealPosition () - nod.getRealPosition ()).length();
    }
      
    void draw();
  };

} /* namespace mge */

#endif /* MGE_SCENENODE_H */
