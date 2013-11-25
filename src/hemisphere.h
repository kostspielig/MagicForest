/**
 * @file hemisphere.h
 *
 * @author María Carrasco Rodríguez
 */

#ifndef MGE_HEMISPHERE_H
#define MGE_HEMISPHERE_H

#include "point.h"
#include "mesh.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctype.h>
#include <unistd.h>


namespace mge
{

  class Hemisphere: public  Mesh {
      
  private:

  public:

    Hemisphere();

  };

} /* namespace mge */

#endif /* MGE_HEMISPHERE_H */
