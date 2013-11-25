/**
 * @file ground.cpp
 * @brief Implemention of Data Type Ground
 * @author María Carrasco Rodríguez
 *
 */

#include "ground.h"
namespace mge
{
  Ground::Ground (const char* texName,
		  int tiles,
		  float l)
  {
    int i, j;
    tiles /= 2;
     
    /*
       v3      v2
        *-----*
        |     |
        |     | 
        *-----*
       v0     v1
    */
     
    
    begin((Mesh::Mode)GL_TRIANGLES);
    setTexture(texName);

    for (i = -tiles; i < tiles; ++i) {
      for (j = -tiles; j < tiles; ++j) {
	texCoord(Point2F(1.0, 0.0));
	point(PointF(i * l + l/2, 0, j * l -l/2)); //v2
	texCoord(Point2F(1.0, 1.0));
	point(PointF(i * l + l/2, 0, j * l + l/2)); // v1
	texCoord(Point2F(0.0, 0.0));
	point(PointF(i * l - l/2, 0, j * l - l/2)); //V3
    
	texCoord(Point2F(1.0, 1.0));
	point(PointF(i * l + l/2, 0, j * l + l/2)); //v1
	texCoord(Point2F(0.0, 1.0));
	point(PointF(i * l - l/2, 0, j * l + l/2)); //v0
	texCoord(Point2F(0.0, 0.0));
	point(PointF(i * l - l/2, 0, j * l - l/2)); //v3
      }
    }
    
    end();
  }
  
}/* namespace mge */
