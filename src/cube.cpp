/**
 * @file Cube.cpp
 * @brief Implemention of Data Type Cube
 * @author María Carrasco Rodríguez
 * @date March 2008
 *
 */
#include <iostream>
#include <cassert>
#include "cube.h"
#include <SDL/SDL_opengl.h>

namespace mge
{

  /*
          v7     v6
          *------*
       v4/.  v5 /|
        *-----*  |
       v|3*...|..* v2
        |.    |  /
        *-----* /
       v0     v1
       
  */
  
  Cube::Cube()
  {
     float l = 1.0f;
     
   
     begin(Mesh::TRIANGLES);

    colour(PointF(1, 0, 0));
    point(PointF(l/2,l/2,l/2)); 
    point(PointF(-l/2,l/2,l/2)); 
    point(PointF(-l/2,-l/2,l/2));

    colour(PointF(1, 1, 0));
    point(PointF(l/2,l/2,l/2)); 
    point(PointF(-l/2,-l/2,l/2));
    point(PointF(l/2,-l/2,l/2));

    colour(PointF(0.6, 0, 0.9));
    point(PointF(l/2,l/2,l/2)); 
    point(PointF(l/2,-l/2,l/2)); 
    point(PointF(l/2,l/2,-l/2)); 

    colour(PointF(1, 0, 0));
    point(PointF(l/2,-l/2,-l/2));
    point(PointF(l/2,l/2,-l/2)); 
    point(PointF(l/2,-l/2,l/2)); 

    colour(PointF(1, 1, 0));
    point(PointF(-l/2,l/2,-l/2)); 
    point(PointF(l/2,l/2,-l/2)); 
    point(PointF(l/2,-l/2,-l/2)); 

    colour(PointF(0.6, 0, 0.9));
    point(PointF(-l/2,l/2,-l/2)); 
    point(PointF(l/2,-l/2,-l/2)); 
    point(PointF(-l/2,-l/2,-l/2));

    colour(PointF(1, 0, 0));
    point(PointF(-l/2,l/2,l/2)); 
    point(PointF(-l/2,l/2,-l/2)); 
    point(PointF(-l/2,-l/2,l/2)); 

    colour(PointF(1, 1, 0));
    point(PointF(-l/2,l/2,-l/2)); 
    point(PointF(-l/2,-l/2,-l/2));
    point(PointF(-l/2,-l/2,l/2));

    colour(PointF(0.6, 0, 0.9));
    point(PointF(l/2,l/2,l/2)); 
    point(PointF(l/2,l/2,-l/2)); 
    point(PointF(-l/2,l/2,-l/2));

    colour(PointF(1, 0, 0));
    point(PointF(l/2,l/2,l/2)); 
    point(PointF(-l/2,l/2,-l/2));
    point(PointF(-l/2,l/2,l/2)); 

    colour(PointF(1, 1, 0));
    point(PointF(l/2,-l/2,-l/2));
    point(PointF(l/2,-l/2,l/2));
    point(PointF(-l/2,-l/2,-l/2));
    
    colour(PointF(0.6, 0, 0.9));
    point(PointF(l/2,-l/2,l/2)); 
    point(PointF(-l/2,-l/2,l/2)); 
    point(PointF(-l/2,-l/2,-l/2)); 
    end();
  }

} /* namespace mge */
