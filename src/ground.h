/**
 * @file ground.h
 *
 * @author María Carrasco Rodríguez
 */


#ifndef MGE_GROUND_H
#define MEG_GROUND_H


#include <string>
#include <SDL/SDL.h>

#include "mesh.h"


namespace mge
{

  class Ground: public Mesh
  {
    const char *m_tex;
    
  public:
    Ground (const char* texName = "tex/grass-512.jpg",
	    int tiles = 20,
	    float l = 30.0f);
  };

} /* namespace mge */

#endif /*  MGE_GROUND_H */
