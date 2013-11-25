
#ifndef GAME_H
#define GAME_H

#include "system.h"
#include "eventmanager.h"
#include "entitymanager.h"
#include "timer.h"
#include "keylistener.h"
#include "mesh.h"
#include "drawable.h"

class Goblin;

class Game : public mge::KeyListener
{
 
  mge::EntityManager m_entmgr;
  mge::Timer m_timer;
  mge::EventManager* m_evmgr;

  mge::Camera m_cam1;
  mge::Camera m_cam2;
  mge::Camera m_cam3;

  mge::Mesh* m_treemesh;
  Goblin* m_goblin;
  
  mge::Drawable* createTree ();
  
 
  void createScene ();
  
public:
  Game (mge::EventManager* evmgr);
  ~Game();
  void run ();

  virtual bool handleKeyPress (SDL_Event& event);
  virtual bool handleKeyRelease (SDL_Event& event);

};

#endif /* GAME_H */
