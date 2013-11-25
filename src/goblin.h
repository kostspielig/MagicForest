
#ifndef GOBLIN_H
#define GOBLIN_H

#include <SDL/SDL_mixer.h>

#include "entity.h"
#include "keylistener.h"
#include "camera.h"
#include "plymesh.h"

class Goblin : public mge::Entity,
	      public mge::KeyListener
{ 
  mge::Camera m_camera;
  mge::PlyMesh* m_model;
  mge::PointF m_pos;
  mge::PointF m_dir;
  mge::Point4F m_rot;

  mge::Mesh* m_hat;
  int m_mush_count;
  bool m_rotate_left;
  bool m_rotate_right;
  bool m_move_forward;
  bool m_move_backward;

    Mix_Chunk* m_sound;
    
public:
  Goblin ();
    ~Goblin ();
    
  mge::Camera* getCamera () {
    return &m_camera;
  }
  
  virtual bool handleKeyPress (SDL_Event& event);
  virtual bool handleKeyRelease (SDL_Event& event);
  virtual void update (float delta_ticks);
  virtual void handleCollision (Entity& col);
};

#endif /* GOBLIN_H */
