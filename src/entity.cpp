/**
 * @file entity.cpp
 * @brief Implemention of Data Type Entity
 * @author María Carrasco Rodríguez
 *
 */

#include <iostream>
#include "entity.h"

namespace mge
{

  Entity::~Entity ()
  {
    if (m_node.getParent ())
      m_node.getParent()->detach (m_node.getName());
  }
  
} /* namespace mge */
