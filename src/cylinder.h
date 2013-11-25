/**
 * @file cylinder.h
 * Fichero cabecera del Tipo de Dato Cilindro
 * @author María Carrasco Rodríguez
 * @date March 2008
 * 
 */

#ifndef MGE_CYLINDER_H
#define MGE_CYLINDER_H

#include "point.h"
#include "mesh.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctype.h>
#include <unistd.h>


namespace mge
{

  class Cylinder: public Mesh{
      
  private: 
    //! Radio del cilindro
    int m_radius;
    //! Altura del cilindro
    int m_height;
    //! Numero de divisiones
    int m_division;
  
  public:
 
    Cylinder();

  };

} /* namespace mge */

#endif /* MGE_CYLINDER_H */
