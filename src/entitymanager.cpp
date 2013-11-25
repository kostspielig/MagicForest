/**
 * @file entitymanager.cpp
 * @brief Implemention of Data Type EntityManager
 * @author María Carrasco Rodríguez
 *
 */

#include <algorithm>
#include "entitymanager.h"

using namespace std;

namespace mge
{
  EntityManager::~EntityManager()
  {
    list<Entity*>::iterator iter;
    for (iter = m_ents_static.begin (); iter != m_ents_static.end (); ++iter)
      delete *iter;
    
    for (iter = m_ents_dyn.begin (); iter != m_ents_dyn.end (); ++iter)
      delete *iter;

  }

  void EntityManager::update (float delta_ticks)
  {
    /* Comprobar las colisiones. */
    list<Entity*>::iterator iter1, iter2;
    for (iter1 = m_ents_dyn.begin (); iter1 != m_ents_dyn.end (); ++iter1)
      for (iter2 = m_ents_dyn.begin (); iter2 != iter1; ++iter2)
	if ( (*iter1)->getNode().getDistance((*iter2)->getNode()) <
	     (*iter1)->getRadius() + (*iter2)->getRadius())
	  {
	    (*iter1)->handleCollision( **iter2 );
	    (*iter2)->handleCollision( **iter1 );
	    
	  }
    for (iter1 = m_ents_dyn.begin (); iter1 != m_ents_dyn.end (); ++iter1)
      for (iter2 = m_ents_static.begin (); iter2 != m_ents_static.end(); ++iter2)
	if ( (*iter1)->getNode().getDistance((*iter2)->getNode()) <
	     (*iter1)->getRadius() + (*iter2)->getRadius())
	  {
	    (*iter1)->handleCollision( **iter2 );
	    (*iter2)->handleCollision( **iter1 );
	    
	  }
    
    /* Actualizar todas las entidades estaticas. */
    for (iter1 = m_ents_static.begin (); iter1 != m_ents_static.end (); ++iter1)
      (*iter1)->update(delta_ticks);

    /* Actualizar todas las entidades dinamicas. */
    for (iter1 = m_ents_dyn.begin (); iter1 != m_ents_dyn.end (); ++iter1)
      (*iter1)->update(delta_ticks);
    
    
    /* Borrar las entidades que tengan que morir. */
    for (iter1 = m_ents_static.begin (); iter1 != m_ents_static.end ();)
      if ((*iter1)->mustDie()) {
	delete *iter1;
	m_ents_static.erase (iter1++);
      } else
	++iter1;

    
    for (iter1 = m_ents_dyn.begin (); iter1 != m_ents_dyn.end ();)
      if ((*iter1)->mustDie()) {
	delete *iter1;
	m_ents_dyn.erase (iter1++);
      } else
	++iter1;
  }
  
} /* namespace mge*/
