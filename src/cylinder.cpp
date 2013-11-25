
/** 
 * @file Cylinder.cpp	
 * Implementation of the Data Type Cylinder
 * @author María Carrasco Rodríguez
 * @date March 2008
 l *
*/
#include <iostream>
#include <cassert>
#include "cylinder.h"
#include <SDL/SDL_opengl.h>

namespace mge
{


  Cylinder::Cylinder()
  {

    m_radius = 1;
    m_height = 2;
    m_division = 8;

    int i;
    
#if 1
    begin(Mesh::TRIANGLES);
    for (i = 0; i <=  m_division; ++i) {
      
      point(PointF(0, 0, 0));
      point(PointF(m_radius * cos(2 * M_PI * (float)i / m_division),
		   0.0f, 
		   m_radius * sin(2 * M_PI * (float)i / m_division)));
      
      point(PointF(m_radius * cos(2 * M_PI * (float)(i+1) / m_division),
		   0.0f, 
		   m_radius * sin(2 * M_PI * (float)(i+1) / m_division)));
    }
    end();
#endif
    
    begin((Mesh::Mode)GL_QUADS);
    for (i = 0; i <= m_division; ++i) {
      
      point(PointF(m_radius * cos(2 * M_PI * (float)i / m_division),
		   0, 
		   m_radius * sin(2 * M_PI * (float)i / m_division)));
      
      point(PointF(m_radius * cos(2 * M_PI * (float)i / m_division),
		   m_height, 
		   m_radius * sin(2 * M_PI * (float)i / m_division)));
      
      point(PointF(m_radius * cos(2 * M_PI * (float)(i+1) / m_division),
		   m_height, 
		   m_radius * sin(2 * M_PI * (float)(i+1) / m_division)));
      
      point(PointF(m_radius * cos(2 * M_PI * (float)(i+1) / m_division),
		   0, 
		   m_radius * sin(2 * M_PI * (float)(i+1) / m_division)));
      
    }
    end();

#if 1
    begin(Mesh::TRIANGLES);
    for (i = 0; i <=  m_division; ++i) {
      
      point(PointF(m_radius * cos(2 * M_PI * (float)(i+1) / m_division),
		   m_height, 
		   m_radius * sin(2 * M_PI * (float)(i+1) / m_division)));
      
      point(PointF(m_radius * cos(2 * M_PI * (float)i / m_division),
		   m_height, 
		   m_radius * sin(2 * M_PI * (float)i / m_division)));
      
      point(PointF(0, m_height, 0));
      
    }
    end();
#endif
    
  }
  

} /* namespace mge */
