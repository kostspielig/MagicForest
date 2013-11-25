

#ifndef MGE_CONE_H
#define MGE_CONE_H

#include "point.h"
#include "mesh.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctype.h>
#include <unistd.h>


namespace mge
{


  class Cone: public Mesh {
      
  private:
    //! Radio del cono
    int m_radius;
    //! Altura del cono
    int m_height;
    //! Numero de divisiones
    int m_division;

  public:

    Cone();

  };

} /* namespace mge */

#endif /* MGE_CONE_H */

