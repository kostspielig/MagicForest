/**
 * @file game.cpp
 * @brief Implemention of Data Type Game
 * @author María Carrasco Rodríguez
 *
 */

#include <cstdlib>
#include <sstream>

#include "game.h"

#include "plymesh.h"
#include "goblin.h"
#include "ground.h"
#include "mushroom.h"
#include "treeent.h"
#include "cylinder.h"
#include "cone.h"

using namespace mge;
using namespace std;

static const int MAX_CHAMPIS = 20;
static const int MAX_TREES = 5;
static const float GROUND_SIZE = 400;
  
Game::Game (mge::EventManager* evmgr)
{
  m_evmgr = evmgr;
  evmgr->addKeyListener (this);
  createScene ();
}

Game::~Game ()
{
  delete m_treemesh;
}

static string toStr (int i)
{
  ostringstream str;
  str << i;
  return str.str ();
}

void Game::createScene ()
{
  System& sys = System::instance ();

  m_cam1.setPosition (PointF (200, 30, 200));
  m_cam2.setPosition (PointF (200, 30, -200));
  m_cam3.setPosition (PointF (200, 10, 100));
  m_cam1.rotateY (45);
  m_cam2.rotateY (135);
  m_cam3.rotateY (100);
  
  /* Creamos el prota */
  m_goblin = new Goblin ();
  m_entmgr.attachEntityDynamic (m_goblin);
  m_evmgr->addKeyListener (m_goblin);
  sys.setCamera (m_goblin->getCamera ());
  sys.getRootNode().attach ("goblin", &m_goblin->getNode ());

  /* Creamos el suelo */
  sys.getRootNode().attachDrawable (new Ground ());

  /* Creamos los champis */
  for (int i = 0; i < MAX_CHAMPIS; i++) {
    Entity* mush = new Mushroom (Point4F ((float) rand() / RAND_MAX,
					  (float) rand() / RAND_MAX,
					  (float) rand() / RAND_MAX,
					  1));
    mush->getNode().setPosition (PointF ((float) rand() / RAND_MAX * GROUND_SIZE - GROUND_SIZE/2,
					 0,
					 (float) rand() / RAND_MAX * GROUND_SIZE - GROUND_SIZE/2));
    m_entmgr.attachEntityStatic (mush);
    sys.getRootNode().attach (string ("mush") + toStr (i), &mush->getNode());
  }

  /* Creamos los arboles */
  m_treemesh = new PlyMesh ("models/fracttree.ply");
  m_treemesh->setMaterial (mge::Point4F (0.25, 0.125, 0, 1),
			   mge::Point4F (0.3, 0.3, 0.3, 1),
			   mge::Point4F (0.3, 0.3, 0.3, 1),
			   40);
  for (int i = 0; i < MAX_TREES; ++i) {
    Entity* tree = new TreeEnt (m_treemesh);
    tree->getNode().setPosition (PointF ((float) rand() / RAND_MAX * GROUND_SIZE - GROUND_SIZE/2,
					 5,
					 (float) rand() / RAND_MAX * GROUND_SIZE - GROUND_SIZE/2));
    m_entmgr.attachEntityStatic (tree);
    sys.getRootNode().attach (string ("tree") + toStr (i), &tree->getNode());
  }

  /* Creamos ároboles manuales*/
  for (int i = 0; i < MAX_TREES; ++i) {
    Entity* treeP = new TreeEnt (createTree());
    treeP->getNode().setPosition (PointF ((float) rand() / RAND_MAX * GROUND_SIZE - GROUND_SIZE/2,
					  5,
					  (float) rand() / RAND_MAX * GROUND_SIZE - GROUND_SIZE/2));
    m_entmgr.attachEntityStatic (treeP);
    sys.getRootNode().attach (string ("treeP") + toStr (i), &treeP->getNode());
  }
}

void Game::run ()
{
  
  Mix_Music *musica;
  int canal;
  musica = Mix_LoadMUS("./sounds/lucy.mp3"); 
  canal = Mix_PlayMusic(musica, -1);
  
  bool must_quit = false;
  m_timer.update ();

  while (!must_quit) {
    must_quit = !m_evmgr->update ();
    m_timer.update ();
    m_entmgr.update (m_timer.deltaTicks ());
    System::instance().update ();
  }
  

  
  Mix_HaltMusic();
  Mix_FreeMusic(musica);
  
}


bool Game::handleKeyPress (SDL_Event& event)
{
  System& sys = System::instance ();
  
  switch (event.key.keysym.sym)
    {
    case SDLK_F1:
      sys.setCamera (m_goblin->getCamera ());
      return true;
    case SDLK_F2:
      sys.setCamera (&m_cam1);
      return true;
    case SDLK_F3:
      sys.setCamera (&m_cam2);
      return true;
    case SDLK_F4:
      sys.setCamera (&m_cam3);
      return true;
    case SDLK_F8:
      sys.setMode(GL_LINE);
      return true;
    case SDLK_F9:
      sys.setMode(GL_POINT);
      return true;
    case SDLK_F10:
      sys.setMode(GL_FILL);
      return true;
    default:
	return false;
    }
}

bool Game::handleKeyRelease (SDL_Event& event)
{
  return false;
}

Drawable* Game::createTree ()
{
  SceneNode* node = new SceneNode;
  Mesh* mesh = new Cylinder;
  node->getChild ("trunk").attachDrawable (mesh);
  mesh->setMaterial (mge::Point4F (0.25, 0.125, 0, 1),
		     mge::Point4F (0.3, 0.3, 0.3, 1),
		     mge::Point4F (0.3, 0.3, 0.3, 1),
		     40);
  
  mesh->blending(Point4F(0.5,0.5,0.5,0.5));
  node->getChild("trunk"). setPosition (PointF(0,-4, 0));
  node->getChild("trunk"). setScale(PointF(-0.4, 1, -0.4));

  mesh = new Cone;
  node->getChild ("top").attachDrawable (mesh);
  
  mesh->setMaterial(Point4F(0, 0, 0, 0.0),
		    Point4F(0.1, 0.35, 0.1, 0.0),
		    Point4F(0.45, 0.55, 0.45, 0.0), 25);
  
  node->getChild("top"). setScale(PointF(2, 5, 2));
  node->getChild ("top").getChild ("topp").attachDrawable (mesh);
  node->getChild ("top").getChild ("topp").setPosition(PointF(0, -0.5, 0));
  node->setScale (PointF(0.7, 0.7, 0.7));
  node->setPosition (PointF(0, -1, 0));
  
  

  return node;
  
}
