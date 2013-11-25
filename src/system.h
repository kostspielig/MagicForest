
#ifndef SYSTEM_H
#define SYSTEM_H

#include "videolistener.h"

#include "camera.h"
#include "scenenode.h"
#include "singleton.h"

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_mixer.h>

namespace mge
{
  /*
    Hacer esta clase singleton esta justificado en el hecho de que
    SDL tiene un estado global y no pueden inicializarse varias instancias
    de SDL por separado.
   */
  class System : public Singleton <System>,
		 public VideoListener
  {
    friend class Singleton <System>; //para dar permiso de creación de una clase.
    
  public:
    static const int DEFAULT_SCREEN_WIDTH = 640;
    static const int DEFAULT_SCREEN_HEIGHT = 480;
    static const bool DEFAULT_FULLSCREEN = false;
    
  private:
    
    enum Mode {
      FILL = GL_FILL,
      LINE = GL_LINE,
      POINT = GL_POINT,
    };
    bool m_isinit;
    
    int m_sc_width;
    int m_sc_height;
   
    bool m_fullsc;
    std::string m_title;

    Camera* m_camera;
    SceneNode m_root;
    
    void changeProjection ();
    void initialize ();

    System() :
      m_isinit (false),
      m_sc_width (DEFAULT_SCREEN_WIDTH),
      m_sc_height (DEFAULT_SCREEN_HEIGHT),
      m_fullsc (DEFAULT_FULLSCREEN)
 
    {};

    bool doInit();

    ~System() {
      if (m_isinit)
	close ();
    }
    
  public:
   

    bool isInit () {
      return m_isinit;
    }
    
    bool handleVideoResize (SDL_Event& ev);
    bool handleVideoUpdate (SDL_Event& ev);
    
    bool init(int sc_w = DEFAULT_SCREEN_WIDTH,
	      int sc_h = DEFAULT_SCREEN_HEIGHT,
	      bool fs = DEFAULT_FULLSCREEN) {
      m_sc_width = sc_w;
      m_sc_height = sc_h;
      m_fullsc = fs;
      return doInit();
    }

    bool init(const std::string& title, int sc_w = DEFAULT_SCREEN_WIDTH,
	      int sc_h = DEFAULT_SCREEN_HEIGHT,
	      bool fs = DEFAULT_FULLSCREEN) {
      m_title = title;
      m_sc_width = sc_w;
      m_sc_height = sc_h;
      m_fullsc = fs;
      return doInit();
    }

    void close();

    SceneNode& getRootNode() {
      return m_root;
    }

    Camera* getCamera () {
      return m_camera;
    }

    const Camera* getCamera () const {
      return m_camera;
    }

    void setCamera (Camera* cam) {
      m_camera = cam;
    }

    void setMode (int mode = GL_FILL);
    

    void update();
  };
  
} /* namespace mge */

#endif /* SYSTEM_H */
