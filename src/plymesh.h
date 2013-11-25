

#ifndef PLY_H
#define PLY_H

#include "point.h"
#include "mesh.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <GL/glut.h>
#include <ctype.h>
#include <unistd.h>


namespace mge
{

  class PlyMesh : public Mesh
  {
      
  private:
    const char* m_ply_name;
 
  public:
    PlyMesh();
    PlyMesh(const char *name);

    void open();

  };

} /* namespace mge */

#endif /* PLY_H */
