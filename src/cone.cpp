/*
 * @file Cone.cpp	
 * Implementation of Data Type Cone
 * @author María Carrasco Rodríguez
 * @date March 2008
 *
 */
#include <iostream>
#include <cassert>
#include "cone.h"
#include <SDL/SDL_opengl.h>

namespace mge
{


  Cone::Cone()
  {

    int i;
    //! Radio del cono
    m_radius = 1;
    //! Altura del cono
    m_height = 1;
    //! Numero de divisiones
    m_division = 20;

    /*
     * Pintamos la base
     */
    begin(Mesh::TRIANGLES);

    for (i = 0; i <=  m_division; ++i) {
    
      point(PointF(0, 0, 0));
      point(PointF( m_radius * cos(2 * M_PI * (float)i / m_division),
		    0.0f, 
		    m_radius * sin(2 * M_PI *(float)i / m_division)));
      point(PointF( m_radius * cos(2 * M_PI * (float)(i+1) / m_division),
		    0.0f, 
		    m_radius * sin(2 * M_PI *(float)(i+1) / m_division)));
    }
    end();


    /*
     * Pintamos los lados
     */
    begin(Mesh::TRIANGLES);
    
    for (i = 0; i <=  m_division; ++i) {
      
      
      point(PointF(m_radius * cos(2 * M_PI * (float)(i+1) / m_division),
		   0.0f, 
		   m_radius * sin(2 * M_PI *(float)(i+1) / m_division)));
      point(PointF(m_radius * cos(2 * M_PI * (float)i / m_division),
		   0.0f, 
		   m_radius * sin(2 * M_PI *(float)i / m_division)));
      
      point(PointF(0, m_height, 0));
    }
    end();

  }


} /* namespace mge */
