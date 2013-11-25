/**
 * @file main.cpp
 * @author María Carrasco Rodríguez
 *
 */

#include "point4.h"
#include "point.h"
#include "system.h"
#include "eventmanager.h"
#include "plymesh.h"
#include "sphere.h"
#include "ground.h"
#include "cube.h"
#include "cone.h"
#include "sphere.h"
#include "hemisphere.h"
#include "cylinder.h"
#include "mushroom.h"

#define VERSION "0.1"
#define PROGRAM "Magic Forest"


class CameraTest : public mge::KeyListener
{
  mge::SceneNode* m_walk_node;
  mge::SceneNode* m_beth_node;
  mge::SceneNode* m_ground_node;
  mge::Camera m_camera_one;
  mge::Camera m_camera_two;

  Mushroom m_mushroom;
  
public:
  CameraTest ():
    m_camera_one(mge::PointF(5.0, 5.0, 10.0)){
    mge::Mesh* mesh;
    
    m_walk_node = new mge::SceneNode;
    m_beth_node = new mge::SceneNode;
    m_ground_node = new mge::SceneNode;
    mesh = new mge::PlyMesh ("models/ant.ply");
    
    m_walk_node->attachDrawable(mesh);
    mesh->setMaterial(mge::Point4F(0.33, 0.26, 0.23, 0.0),
		      mge::Point4F(0.50, 0.11, 0.00, 0.0),
		      mge::Point4F(0.95, 0.73, 0.00, 0.0), 93);
    mesh = new mge::PlyMesh ("models/beethoven.ply");
    mesh->setMaterial(mge::Point4F(0.57,0.40,0.00,0.00),
		      mge::Point4F(0.22,0.15,0.00,0.00),
		      mge::Point4F(0.71, 0.70, 0.56, 0.00), 16);
    //mesh->blending(mge::Point4F(0.5, 0.5, 0.5, 0.5));
    m_beth_node->attachDrawable(mesh);
    //m_beth_node->attachDrawable(new mge::PlyMesh ("models/walkman.ply"));

    m_ground_node->attachDrawable(new mge::Ground);
    m_ground_node->attach ("mush", &m_mushroom.getNode ());
#if 0
    mge::Mesh* me;
    me = new mge::Cylinder;
    //m_ground_node->attachDrawable(new mge::Sphere);
    //m_ground_node->attachDrawable(new mge::Cone);
    m_ground_node->getChild("seta").attachDrawable(new mge::Hemisphere);
    m_ground_node->getChild("seta").setRotate(mge::Point4F(90,-1,0,0));
    m_ground_node->getChild("seta").setScale(mge::PointF(0.7,0.7,0.7));
    me->setMaterial(mge::Point4F(0.57,0.40,0.00,0.00),
		    mge::Point4F(0.22,0.15,0.00,0.00),
		    mge::Point4F(0.71, 0.70, 0.56, 0.00), 16);
    m_ground_node->getChild("me").attachDrawable(me);
    //m_ground_node->getChild("me").setRotate(mge::Point4F(90,-1,0,0));
    m_ground_node->getChild("me").setScale(mge::PointF(0.3,0.3,0.3));
    m_ground_node->getChild("me").setPosition(mge::PointF(0,-0.5,0));
#endif    

    mge::System::instance().setCamera(&m_camera_one);
    m_camera_one.rotateY(1);
    m_camera_two.rotateY(-1);
  }

  ~CameraTest () {
    mge::System::instance().getRootNode().detach("test_node");
    delete m_walk_node;
    delete m_beth_node;
    m_ground_node->detach ("mush");
    delete m_ground_node;
  }
  
  bool handleKeyPress (SDL_Event& ev)
  {
    mge::System& sys = mge::System::instance();
    
    switch (ev.key.keysym.sym) {
    case SDLK_F1:
      sys.setCamera(&m_camera_one);
      sys.update ();
      return true;

    case SDLK_F2:
      sys.setCamera(&m_camera_two);
      sys.update ();
      return true;
      
    case SDLK_1:
      sys.getRootNode().detach("test_node");
      sys.getRootNode().attach("test_node", m_walk_node);
      sys.update();
      return true;

    case SDLK_2:
      sys.getRootNode().detach("test_node");
      sys.getRootNode().attach("test_node", m_beth_node);
      sys.update();
      return true;
      
    case SDLK_3:
      sys.getRootNode().detach("test_node");
      sys.getRootNode().attach("test_node", m_ground_node);
      sys.update();
      return true;

    case SDLK_4:
      sys.getRootNode().detach("test_node");
      sys.getRootNode().attach("test_node", m_ground_node);
      sys.getCamera()->setPosition( mge::PointF(5,5,20) );
      sys.update();
      return true;
      
    case SDLK_a:
      sys.getCamera()->rotateY(5.0f);
      sys.update();
      return true;

    case SDLK_d:
      sys.getCamera()->rotateY(-5.0f);
      sys.update();
      return true;

    case SDLK_w:
      sys.getCamera()->moveForward(-0.1f);
      sys.update();
      return true;

    case SDLK_s:
      sys.getCamera()->moveForward(0.1f);
      sys.update();
      return true;

    case SDLK_x:		
      sys.getCamera()->rotateX(5.0);
      sys.update();
      return true;
    case SDLK_y:		
      sys.getCamera()->rotateX(-5.0);
      sys.update();
      return true;
      
    case SDLK_LEFT:
      sys.getCamera()->strafeRight(-0.1);
      sys.update();
      return true;

    case SDLK_RIGHT:
      sys.getCamera()->strafeRight(0.1);
      sys.update();
      return true;
      
    case SDLK_UP:
      sys.getCamera()->moveForward(-0.1);
      sys.update();
      return true;

    case SDLK_DOWN:
      sys.getCamera()->moveForward(0.1);
      sys.update();
      return true;
    default:
      return false;
    }
  }

  bool handleKeyRelease (SDL_Event& ev)
  {
    return false;
  }
};


using namespace mge;

int main (int argc, char* argv[])
{
  System& sys = System::instance();
  sys.init(PROGRAM VERSION, 640, 480, false);
  
  EventManager evmgr;
  CameraTest controller;
    
  evmgr.addVideoListener (&sys);
  evmgr.addKeyListener (&controller);
  
  sys.getCamera()->move(PointF(0.0, 0.0, 3.0 ) );
  sys.getCamera()->moveForward(1.0 );

#if 0  	
  //Set a new projection matrix
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();
  //Angle of view:40 degrees
  //Near clipping plane distance: 0.5
  //Far clipping plane distance: 20.0
  gluPerspective(40.0,(GLdouble)1/(GLdouble)1,0.5,20.0);

  glMatrixMode(GL_MODELVIEW);
  glViewport(0,0,1,1);  //Use the whole window for rendering
#endif
  
#if 1
  Mix_Music *musica;
  int canal;
  musica = Mix_LoadMUS("./sounds/beboy.mp3"); 
  if (musica == NULL) {
    /* horror terror pastel de costo! */
    printf("No pude cargar sonido: %s\n", Mix_GetError());
    exit(1);
  }
  canal = Mix_PlayMusic(musica, -1);
#endif
  
  //glTranslatef(0.0,-1 ,0.0);

  //sys.getRootNode().attachDrawable(new PlyMesh("models/beethoven.ply"));
  //sys.getRootNode().attachDrawable(new Sphere);
  
  
  while (evmgr.update ());

#if 1
  Mix_HaltMusic();
  Mix_FreeMusic(musica);
#endif
  
  sys.close ();
}
