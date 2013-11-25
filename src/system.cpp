/** 
 * @file system.cpp	
 * @brief Implementation of Data Type System
 * @author María Carrasco Rodríguez
 *
 */

#include <SDL/SDL_mixer.h>

#include "system.h"

namespace mge
{
  
  void System::changeProjection ()
  {

    
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();

    gluPerspective(40.0, (GLdouble) m_sc_width/( GLdouble)m_sc_height, 0.5, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0, m_sc_width, m_sc_height); 

  }

  
  void System::initialize ()
  {
    float spot_direction[] = {3.0, 0.0, 10.0}; // <- Direccion cono de luz
    
    glClearColor(0.5, 0.5, 0.9, 1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    float Luz0[4]={1,1,1,0};
    float LightAmbient[] ={0.5f, 0.5f, 0.5f, 1.0f};
    float LightDiffuse[] ={1.0f, 1.0f, 1.0f, 1.0f};
    float LightPosition[] ={0.0f, 0.0f, 2.0f, 1.0f};
    //glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_direction); // Cono de luz!
    glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);
    glLightfv(GL_LIGHT1,GL_POSITION,LightPosition);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //_vertex4f Componente_ambiente[4]={1,1,1,1};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Componente_ambiente);
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

    /* Material por defecto */
    float fpAmbient[]  = {0.3f,0.3f,0.3f,0.0f};
    float fpDiffuse[]  = {0.7f,0.7f,0.7f,0.0f};
    float fpSpecular[] = {1.0f,1.0f,1.0f,0.0f};
		
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,fpAmbient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,fpDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,fpSpecular);
    glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS,128);
     
    changeProjection();
    
    glViewport(0, 0, m_sc_width, m_sc_height);
  }

  
  bool System::doInit ()
  {
    int flags;
    if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0) {
      printf("No se puede inicializar SDL");
      exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    /*
      SDL_GL_SetAttribute( SDL_GL_RED_SIZE,8);
      SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8);
      SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,8);
      SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,24);
      SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1);
    */
    flags = SDL_OPENGL | SDL_RESIZABLE;
    if (m_fullsc)
      flags |= SDL_FULLSCREEN;
    
    if (SDL_SetVideoMode(m_sc_width, m_sc_height, 32, flags) == NULL){
      printf("No se puede inciacializar OpenGL\n");
      SDL_Quit();
      exit(1);
    }

    initialize();

    SDL_EnableKeyRepeat(300,50);
    SDL_WM_SetCaption(m_title.c_str(), NULL);
  
    if(Mix_OpenAudio(44100, AUDIO_S16, 2, 4096)) {
      printf("No se puede inicializar SDL_mixer %s\n",Mix_GetError());
      exit(1);
    }
    
    atexit (SDL_Quit);
    atexit (Mix_CloseAudio);

    m_isinit = true;
  }


  void System::close ()
  {
    if (m_isinit)
      SDL_Quit ();
    /* TODO */
  }


  bool System::handleVideoResize (SDL_Event& ev)
  {
    m_sc_width = ev.resize.w;
    m_sc_height = ev.resize.h;
    SDL_SetVideoMode(ev.resize.w, ev.resize.h, 32, SDL_OPENGL|SDL_RESIZABLE);
    glViewport(0, 0, ev.resize.w, ev.resize.h);
    return false;
  }
  

  bool System::handleVideoUpdate (SDL_Event& ev)
  {
    update();
    return false;
  }
  

  void System::update ()
  {
    
    //glPolygonMode(GL_BACK, m_mode);
    //glPolygonMode(GL_FRONT, m_mode);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );    
    glPushMatrix();

    if (m_camera)
      m_camera->draw();
    m_root.draw();

    glPopMatrix();
    SDL_GL_SwapBuffers();
  }

  void System::setMode(int mode )
  {
    
    glPolygonMode(GL_BACK, mode);
    glPolygonMode(GL_FRONT,mode);
  }
  
} /* namespace mge */
