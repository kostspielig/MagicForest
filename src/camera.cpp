/**
 * @file Camera.cpp
 * @brief Implemention of Data Type Camera
 * @author María Carrasco Rodríguez
 * @date March 2008
 *
 */
#include <iostream>
#include <cassert>
#include <cmath>
#include <SDL/SDL_opengl.h>

#include "camera.h"

#define SQR(x) ((x)*(x))


namespace mge
{

  Camera::Camera()
  {
     
    m_position = PointF(0.0, 0.0, 10.0);
    m_view_dir = PointF( 0.0, 0.0, -1.0);
    m_right_vector = PointF(1.0, 0.0, 0.0);
    m_up_vector = PointF(0.0, 1.0, 0.0);

    m_rotated_x = m_rotated_y = m_rotated_z = 0.0;
  }

  
  Camera::Camera(const PointF& pos)
  {
     
    m_position = pos;
    m_view_dir = PointF( 0.0, 0.0, -1.0);
    m_right_vector = PointF(1.0, 0.0, 0.0);
    m_up_vector = PointF(0.0, 1.0, 0.0);

    m_rotated_x = m_rotated_y = m_rotated_z = 0.0;
  }
 

  void Camera::move (PointF direction)
  {
    m_position = m_position + direction;
  }
  
  
  void  Camera::rotateX (float angle)
  {
    m_rotated_x += angle;
	
    //Rotamos  m_view_dir alrededor del m_right_vector
    m_view_dir = (m_view_dir*cos(angle*(M_PI/180.0))
		  + m_up_vector*sin(angle*(M_PI/180.0))).normalize();

    //Calculamos el nuevo m_up_vector (por producto vectorial)
    m_up_vector = m_view_dir.cross(m_right_vector)*-1;
	
  }
  
  
  void Camera::rotateY (float angle)
  {
    m_rotated_y += angle;
	
    //Rotamos m_view_dir alrededor dele m_up_vector
    m_view_dir = (m_view_dir*cos(angle*(M_PI/180.0))
		  - m_right_vector*sin(angle*(M_PI/180.0))).normalize();

    //Calculamos el nuevo m_up_vector (por producto vectorial)
    m_right_vector = m_view_dir.cross(m_up_vector);
  }
  

  void Camera::rotateZ (float angle)
  {
    m_rotated_z += angle;
	
    //Rotamos m_viewdir alrededor del m_right_vector:
    m_right_vector = (m_right_vector*cos(angle*(M_PI/180.0))
		      + m_up_vector*sin(angle*(M_PI/180.0))).normalize();

    //Calculamos el nuevo m_up_vector (por producto vectorial)
    m_up_vector = m_view_dir.cross(m_right_vector)*-1;
  }
  
  
  void Camera::draw (void)
  {

    
    glRotatef(-m_rotated_x , 1.0, 0.0, 0.0);
    glRotatef(-m_rotated_y , 0.0, 1.0, 0.0);
    glRotatef(-m_rotated_z , 0.0, 0.0, 1.0);
    glTranslatef(-m_position[0], -m_position[1], -m_position[2]);
  }
  
  
  void Camera::moveForward ( float distance )
  {
    m_position = m_position + (m_view_dir*-distance);
  }
  
  
  void Camera::strafeRight ( float distance )
  {
    m_position = m_position + (m_right_vector*distance);
  }
  

  void Camera::moveUpward( float distance )
  {
    m_position = m_position + (m_up_vector* distance);
  }
  
 
  void Camera::setPosition( PointF pos)
  {
    m_position = pos;
  }
  
} /* namespace mge */

