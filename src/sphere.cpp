/** 
 * @file Sphere.cpp	
 * Implementation of Data Type Sphere
 * @author María Carrasco Rodríguez
 *
 */
#include <iostream>
#include <cassert>
#include "sphere.h"
#define RADIUS 3.0f
#define STEP 0.1f

namespace mge
{


  Sphere::Sphere()
  {
  
    int m_radius = 1;
    int m_division = 20;
  
    int i,j;
    begin((Mesh::Mode)GL_QUADS);
    for (i = 0; i < m_division; ++i) {
      colour(PointF(1.0, (float)i / m_division, 0.0));
      for (j = 0; j < m_division/2; j++) {
	point(PointF((m_radius * sin(2* M_PI * (float)j /m_division)) 
		     * cos(2 * M_PI * (float)i /m_division),
		     m_radius * cos(2 * M_PI * (float)j /m_division),
		     (m_radius * sin(2 * M_PI * (float)j /m_division)) 
		     * sin(2 * M_PI * (float)i /m_division)));
	point(PointF((m_radius * sin(2* M_PI * (float)j /m_division)) 
		     * cos(2 * M_PI * (float)(i+1) /m_division),
		     m_radius * cos(2 * M_PI * (float)j /m_division),
		     (m_radius * sin(2 * M_PI * (float)j /m_division)) 
		     * sin(2 * M_PI * (float)(i+1) /m_division)));
	point(PointF((m_radius * sin(2* M_PI * (float)(j+1) /m_division)) 
		     * cos(2 * M_PI * (float)(i+1) /m_division),
		     m_radius * cos(2 * M_PI * (float)(j+1) /m_division),
		     (m_radius * sin(2 * M_PI * (float)(j+1) /m_division)) 
		     * sin(2 * M_PI * (float)(i+1) /m_division)));
	point(PointF((m_radius * sin(2* M_PI * (float)(j+1) /m_division)) 
		     * cos(2 * M_PI * (float)i /m_division),
		     m_radius * cos(2 * M_PI * (float)(j+1) /m_division),
		     (m_radius * sin(2 * M_PI * (float)(j+1) /m_division)) 
		     * sin(2 * M_PI * (float)i /m_division)));
      }
    }
    end();

    }
  
  
} /* namespace mge */
