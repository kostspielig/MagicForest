
#ifndef MGE_CAMERA_H
#define MGE_CAMERA_H

#include <iostream>
#include <cmath>
#include <ctype.h>
#include "point.h"
#include "drawable.h"

namespace mge
{

  class Camera : public Drawable
  {
  private:
    PointF m_position; //Posición (vrp)
    PointF m_view_dir; //Orientación (vpn)
    PointF m_up_vector; //Sentido "Hacia arriba" (vuv)
    PointF m_right_vector; 

    float m_rotated_x, m_rotated_y, m_rotated_z; //Ejes x, y , z

  public:

    Camera();

    Camera(const PointF& pos);
    
    void draw ( void );
    
    void move ( PointF direction );
    void rotateX ( float angle );
    void rotateY ( float angle );
    void rotateZ ( float angle );

    void moveForward ( float distance );
    void moveUpward ( float distance );
    void strafeRight ( float distance );

    void setPosition ( PointF pos);

  };

  
} /* namespace mge */

#endif /* MGE_CAMERA_H */

