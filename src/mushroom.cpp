/**
 *@file mushroom.cpp
 * Implementation of Data Type Mushroom
 *@author María Carrasco Rodríguez
 *
 */

#include <SDL/SDL_opengl.h>
#include "mushroom.h"
#include "hemisphere.h"
#include "cylinder.h"

static const float MAX_SCALE = 0.3;
static const float MIN_SCALE = 0.1;

Mushroom::~Mushroom()
{
}

Mushroom::Mushroom (const mge::Point4F &color)
{
  m_color = color;
  size = 0.2;
  mge::Mesh* mesh = new mge::Hemisphere;
  getNode().getChild("head").attachDrawable(mesh);
  getNode().getChild("head").setRotate(mge::Point4F(90,-1,0,0));
  getNode().getChild("head").setScale(mge::PointF(0.7,0.7,0.7));
  getNode().getChild("head").setPosition(mge::PointF(0, 0.5, 0));
  
  mesh->setMaterial (color,
		     mge::Point4F(0.3, 0.2, 0.2, 1),
		     mge::Point4F(0.2, 0.1, 0.1, 1),
		     40);
  
  mesh = new mge::Cylinder;
  getNode().getChild("body").attachDrawable(mesh);
  getNode().getChild("body").setScale(mge::PointF(0.3,0.3,0.3));
  getNode().getChild("body").setPosition(mge::PointF(0, 0, 0)); 

  mesh->setMaterial (mge::Point4F(0.5, 0.7, 0, 1),
		     mge::Point4F(0.5, 0.5, 0.5, 1),
		     mge::Point4F(0.0, 0.0, 0.0, 1),
		     40);

  getNode().setScale(mge::PointF(1.5, 2, 1.5));
  
  m_radius = 1;
}


void Mushroom::update (float delta_xticks)
{
  
  if ( size <= MIN_SCALE ){
    size = size + delta_xticks;
    getNode().setScale(mge::PointF(size,
				 size,
				 size));
    
  } else if ( size >= MAX_SCALE){
    size = size - delta_xticks;
    getNode().setScale(mge::PointF(size,
				 size,
				 size));
				 }
}

void Mushroom::handleCollision (Entity& col)
{
  kill ();
}
