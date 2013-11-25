/**
 * @file goblin.cpp
 * @brief Implemention of Data Type Goblin
 *        which is the main character of the game
 * @author María Carrasco Rodríguez
 *
 */

#include "goblin.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "mesh.h"
#include "mushroom.h"


static const float ROTATE_SPEED = 0.2;
static const float MOVE_SPEED = 0.02;
static const float CAMERA_DISTANCE = 20.0;
static const float CAMERA_HEIGHT = 5.0;

using namespace mge;

Goblin::Goblin ()
  : m_pos (0, 1.6, 0)
  , m_rot (0, 0, 1, 0)
  , m_rotate_left (false)
  , m_rotate_right (false)
  , m_move_forward (false)
  , m_move_backward (false)
  , m_mush_count (0)
{
  /* Definición del muñeco -> ¡¡¡goblin!!! */
  Mesh* mesh;
  mesh = new Sphere; 
   
  getNode().getChild ("head").attachDrawable (mesh);
  
  mesh->setMaterial(Point4F(0.2125, 0.1275, 0.054, 0.0),
		    Point4F(0.714, 0.4284, 0.18144, 0.0),
		    Point4F(0.393548, 0.271906,	0.166721, 0.0), 20);
  getNode().getChild ("head"). setPosition (PointF (0,2.5,0));

  mesh = new Cone;
  m_hat = mesh;
  getNode().getChild ("hat"). attachDrawable (mesh);
  mesh->setMaterial(Point4F(0.33, 0.26, 0.23, 0.0),
		    Point4F(0.50, 0.11, 0.00, 0.0),
		    Point4F(0.95, 0.73, 0.00, 0.0), 93);
  getNode ().getChild("hat"). setPosition (PointF(0, 3, 0));

  mesh = new Cylinder;
  getNode().getChild ("body"). attachDrawable (mesh);
  mesh->setMaterial(Point4F(0, 0, 0, 0.0),
		    Point4F(0.1, 0.35, 0.1, 0.0),
		    Point4F(0.45, 0.55, 0.45, 0.0), 25);
  getNode().getChild("body"). setPosition (PointF (0, -0.5, 0));

  mesh = new Cylinder;
  getNode().getChild("leg"). attachDrawable (mesh);
  
  mesh->setMaterial(Point4F(0.2125, 0.1275, 0.054, 0.0),
		    Point4F(0.714, 0.4284, 0.18144, 0.0),
		    Point4F(0.393548, 0.271906,	0.166721, 0.0), 20);
  getNode().getChild("leg"). setScale (PointF (-0.3, 1.5, -0.3));
  getNode().getChild("leg"). setPosition (PointF (0.5, -2, 0));
  
  mesh = new Cylinder;
  getNode().getChild("leg2"). attachDrawable (mesh);
  
  mesh->setMaterial(Point4F(0.2125, 0.1275, 0.054, 0.0),
		    Point4F(0.714, 0.4284, 0.18144, 0.0),
		    Point4F(0.393548, 0.271906,	0.166721, 0.0), 20);
  getNode().getChild("leg2"). setScale (PointF (-0.3, 1.5, -0.3));
  getNode().getChild("leg2"). setPosition (PointF (-0.5, -2, 0));

  mesh = new Cylinder;
  getNode().getChild("arm"). attachDrawable (mesh);
  
  mesh->setMaterial(Point4F(0.2125, 0.1275, 0.054, 0.0),
		    Point4F(0.714, 0.4284, 0.18144, 0.0),
		    Point4F(0.393548, 0.271906,	0.166721, 0.0), 20);
  getNode().getChild("arm"). setRotate (Point4F(90, 0, 0, 1));
  getNode().getChild("arm"). setScale (PointF (-0.6, 0.23, 0.23));
  getNode().getChild("arm"). setPosition (PointF (-2.25, 1, 0));

  mesh = new Sphere;
  getNode().getChild("arm").getChild("hand"). attachDrawable(mesh);
  
  mesh->setMaterial(Point4F(0.2125, 0.1275, 0.054, 0.0),
		    Point4F(0.714, 0.4284, 0.18144, 0.0),
		    Point4F(0.393548, 0.271906,	0.166721, 0.0), 20);
  getNode().getChild("arm").getChild("hand"). setScale(PointF(1, -0.33, -0.33));
  getNode().getChild("arm").getChild("hand"). setPosition(PointF(0, -0.4, 0));

  
  mesh = new Cylinder;
  getNode().getChild("arm2"). attachDrawable (mesh);
  
  mesh->setMaterial(Point4F(0.2125, 0.1275, 0.054, 0.0),
		    Point4F(0.714, 0.4284, 0.18144, 0.0),
		    Point4F(0.393548, 0.271906,	0.166721, 0.0), 20);
  getNode().getChild("arm2"). setRotate (Point4F(90, 0, 0, 1));
  getNode().getChild("arm2"). setScale (PointF (-0.6, 0.23, 0.23));
  getNode().getChild("arm2"). setPosition (PointF (1.091, 1, 0));

  mesh = new Sphere;
  getNode().getChild("arm2").getChild("hand"). attachDrawable(mesh);
  
  mesh->setMaterial(Point4F(0.2125, 0.1275, 0.054, 0.0),
		    Point4F(0.714, 0.4284, 0.18144, 0.0),
		    Point4F(0.393548, 0.271906,	0.166721, 0.0), 20);
  getNode().getChild("arm2").getChild("hand"). setScale(PointF(1, -0.33, -0.33));
  getNode().getChild("arm2").getChild("hand"). setPosition(PointF(0, 2.4, 0));

  
  /* If we prefer using a ply model... just replace here! ->
     getNode().attachDrawable (m_model);
     getNode().setRotate (m_rot);
     getNode().setPosition (m_pos);
     getNode().setScale (PointF (0.2, 0.2, 0.2));
  */
  
  m_dir = PointF (cos ((- m_rot[0] - 270) * M_PI / 180),
		  0,
		  sin ((- m_rot[0] - 270) * M_PI / 180));

  m_camera.setPosition (m_pos
			+ m_dir * (-CAMERA_DISTANCE)
			+ PointF (0, CAMERA_HEIGHT, 0));
  m_camera.rotateX (-atan (CAMERA_HEIGHT / CAMERA_DISTANCE) / M_PI * 180);
  m_camera.rotateY (180);
  
  m_radius = 5;

  m_sound = Mix_LoadWAV("sounds/yeah.ogg");
  if (!m_sound)
      std::cerr << "No se pudo cargar el sonido." << std::endl;
}

Goblin::~Goblin()
{
    Mix_FreeChunk (m_sound);
}

bool Goblin::handleKeyPress (SDL_Event& event)
{
  switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
      m_rotate_left = true;
      return true;

    case SDLK_RIGHT:
      m_rotate_right = true;
      return true;
      
    case SDLK_UP:
      m_move_forward = true;
      return true;

    case SDLK_DOWN:
      m_move_backward = true;
      return true;
      
    default:
      return false;
    }
}

bool Goblin::handleKeyRelease (SDL_Event& event)
{
  switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
      m_rotate_left = false;
      return true;

    case SDLK_RIGHT:
      m_rotate_right = false;
      return true;
      
    case SDLK_UP:
      m_move_forward = false;
      return true;

    case SDLK_DOWN:
      m_move_backward = false;
      return true;
      
    default:
      return false;
    }
}

void Goblin::update (float delta_ticks)
{
  if (m_rotate_left) {
    m_rot[0] += ROTATE_SPEED * delta_ticks;
    m_camera.rotateY (ROTATE_SPEED * delta_ticks);
  }

  if (m_rotate_right) {
    m_rot[0] -= ROTATE_SPEED * delta_ticks;
    m_camera.rotateY (-ROTATE_SPEED * delta_ticks);
  }

  if (m_rotate_left || m_rotate_right) {
    m_dir = PointF (cos ((- m_rot[0] - 270) * M_PI / 180),
		    0,
		    sin ((- m_rot[0] - 270) * M_PI / 180));
  }

  if (m_move_forward) {
    m_pos += m_dir * (MOVE_SPEED * delta_ticks);
  }

  if (m_move_backward) {
    m_pos += m_dir * - (MOVE_SPEED * delta_ticks);
  }

  getNode ().setRotate (m_rot);
  getNode ().setPosition (m_pos);
  m_camera.setPosition (m_pos
			+ m_dir * (-CAMERA_DISTANCE)
			+ PointF (0, CAMERA_HEIGHT, 0));
}

void Goblin::handleCollision (Entity& col)
{
  Mushroom* mush;
  try{
    //si col es mushroom devuelve el puntero y sino devuelve null
    mush = dynamic_cast <Mushroom*>(&col);
    if (mush != 0)
      {
	m_mush_count++;
	m_hat->setMaterial (mush ->getColor(),
			    Point4F(0.50, 0.11, 0.00, 0.0),
			    Point4F(0.95, 0.73, 0.00, 0.0), 93);
	std::cout << "Quedan " << 20 - m_mush_count << endl;
	Mix_PlayChannel (-1, m_sound, 0);
      }
  } catch (...) {};
}
