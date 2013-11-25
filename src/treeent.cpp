/** 
 * @file treeent.cpp	
 * @brief Implementation of Data Type TreeEnt
 * @author María Carrasco Rodríguez
 *
 */

#include <iostream>

#include "treeent.h"

static const float FALL_SPEED = 0.1;

using namespace mge;

TreeEnt::TreeEnt (Drawable* mesh)
  : m_falling (false)
  , m_fell (false)
{
  getNode().addDrawable (mesh); // Ya que todos los arboles son iguales, usamos el mismo mesh
  m_radius = 5;
}

TreeEnt::~TreeEnt ()
{
}


void TreeEnt::update (float delta_ticks)
{
  if (m_falling && !m_fell) {
    m_rot [0] -= FALL_SPEED * delta_ticks;
    if (m_rot [0] <= -90) {
      m_rot [0] = -90;
      m_fell = true;
    }
    
    getNode().setRotate (m_rot);
  }
}

void TreeEnt::handleCollision (Entity& col)
{
  if (!m_falling && !m_fell) {
    m_falling = true;
    PointF dir =
      (getNode().getPosition() - col.getNode().getPosition())
      .cross (PointF (0, 1, 0))
      .normalize ();

    m_rot [1] = dir [0];
    m_rot [2] = dir [1];
    m_rot [3] = dir [2];
  }
}

