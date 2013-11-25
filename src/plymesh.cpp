/** 
 * @file Plymesh.cpp	
 * Implementation of the Data Type Ply Mesh
 * @author María Carrasco Rodríguez
 *
 */
#include <iostream>
#include <cassert>
#include "plymesh.h"

namespace mge
{

  PlyMesh::PlyMesh()
  {
    m_ply_name = "";
  }


  PlyMesh::PlyMesh(const char* name)
  {
    m_ply_name = name;
    begin(Mesh::TRIANGLES);
    loadPly(m_ply_name);
    end();
  }


  void PlyMesh::open()
  {
    loadPly(m_ply_name);
  }
  
} /* namespace mge */
