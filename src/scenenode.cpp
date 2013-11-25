/** 
 * @file scenenode.cpp	
 * @brief Implementation of Data Type SceneNode
 * @author María Carrasco Rodríguez
 *
 */

#include <SDL/SDL_opengl.h>
#include "scenenode.h"

namespace mge
{

  SceneNode::SceneNode() :
    m_position(0.0f, 0.0f, 0.0f),
    m_scale(1.0f, 1.0f, 1.0f)
  {}

  SceneNode::~SceneNode()
  {
    for (std::list<Drawable*>::iterator it = m_draw_attach.begin();
	 it != m_draw_attach.end(); ++it)
      delete *it;
  }

  void SceneNode::draw()
  {
    glPushMatrix();

    glTranslatef(m_position[0], m_position[1], m_position[2]);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    glRotatef(m_rotate[0], m_rotate[1], m_rotate[2], m_rotate[3]);

    for (std::list<Drawable*>::iterator it = m_draw_attach.begin();
	 it != m_draw_attach.end(); ++it)
      (*it)->draw();

    for (std::list<Drawable*>::iterator it = m_draw_add.begin();
	 it != m_draw_add.end(); ++it)
      (*it)->draw();
    
    for (ChildIter iter = begin(); iter != end(); ++iter)
      (*iter)->draw();
      
    glPopMatrix();
  }

} /* namespace mge */
