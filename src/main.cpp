/**
 * @file main.cpp
 *
 * @author María Carrasco Rodríguez
 *
 */

#include "system.h"
#include "game.h"

#define VERSION "0.1"
#define PROGRAM "Magic Forest"

using namespace mge;

int main (int argc, char* argv[])
{
  bool must_quit = false;

  System& sys = System::instance ();
  EventManager evmgr;

  sys.init (PROGRAM VERSION, 640, 480, false);
  evmgr.addVideoListener (&sys);

  Game game (&evmgr);
  game.run ();
    
  sys.close ();
}
