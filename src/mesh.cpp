/** 
 * @file mesh.cpp	
 * @brief Implementation of Data Type Mesh
 * @author María Carrasco Rodríguez
 *
 */

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "mesh.h"
#include <map>

namespace mge
{
  
  static int power_of_two(int input)
  {
    int value = 1;

    while ( value < input ) {
      value <<= 1;
    }
    return value;
  }

  void Mesh::begin(Mode mode, int n_vertex_est, Normal normal)
  {
    Block new_block;
    new_block.mode = mode;
    new_block.normal = normal;
    new_block.vertex.reserve(n_vertex_est);
    new_block.curr_colour = PointF(0,0,0);
    new_block.p_count = 0;
    m_blocks.push_back(new_block);
  }
   
  void Mesh::point(const PointF& p)
  {
    Block& b = *(m_blocks.end()-1);
    Block::PointState s;
    s.point = p;
    s.colour = b.curr_colour;
    s.tex = b.curr_tex;
    s.has_color = b.has_color;
    s.has_tex = b.has_tex;
    b.has_color = false;
    b.has_color = false;
    b.vertex.push_back(s);
    b.p_count++;
    
    switch(b.mode) {
    case TRIANGLES:
      // We have finished adding a new triangle? 
      if (b.vertex.size() % 3 == 0)
	{
	  Block::FaceState s;
	  s.tri = Triangle((b.vertex.end()-3)->point,
			   (b.vertex.end()-2)->point,
			   (b.vertex.end()-1)->point);
	  b.faces.push_back(s);
	}
      break;

    case GL_QUADS:
      // We have finished adding a new quad?
      if(b.p_count % 4 == 0)
	{
	  Block::FaceState s;
	  s.tri = Triangle((b.vertex.end()-4)->point,
			   (b.vertex.end()-3)->point,
			   (b.vertex.end()-2)->point);
	  b.faces.push_back(s);
	
	  s.tri = Triangle((b.vertex.end()-1)->point,
			   (b.vertex.end()-4)->point, 
			   (b.vertex.end()-2)->point);
	  b.faces.push_back(s);

	  b.vertex.push_back (*(b.vertex.end()-4));
	  b.vertex.push_back (*(b.vertex.end()-3));
	
	}
      break;
    default:
      // TODO: Not implemented. 
      break;
    }
  }

  
  int Mesh::loadPly(const char* plyName)
  {
    Block& b = *(m_blocks.end()-1);

    vector<float> vert;
    vector<int> fac;
    
    _file_ply File1;
   
    if (! File1.open(const_cast<char*>(plyName))){
      File1.read(vert, fac);
      File1.close();
    }

    PointF p1;
    
    colour(PointF(0.7, 0.3, 0.7));

    for(int i = 0; i < fac.size(); ++i)
      {
	p1 = PointF(vert[fac[i]*3],
		    vert[fac[i]*3+1],
		    vert[fac[i]*3+2]);
	point(p1);
      }
  }
  void Mesh::texCoord(const Point2F& tex)
  {
    Block& b = *(m_blocks.end()-1);
    b.has_tex = true;
    b.curr_tex = tex;

  }
  
  void Mesh::colour(const PointF& c)
  {
    Block& b = *(m_blocks.end()-1);
    b.has_color = true;
    b.curr_colour = c;      
  }

  
  void Mesh::normalizeVertex(Block& bloque)
  {
    if (!bloque.m_vertex_normal){
      if (!bloque.m_faces_normal)
	normalizeFaces(bloque);

      map<PointF, pair<PointF, int> > norm;
      
      for(vector<Block::FaceState>::iterator it = bloque.faces.begin();
	  it != bloque.faces.end();
	  ++it)
	{
	  norm[it->tri[0]].first += it->norm; ++norm[it->tri[0]].second;
	  norm[it->tri[1]].first += it->norm; ++norm[it->tri[1]].second;
	  norm[it->tri[2]].first += it->norm; ++norm[it->tri[2]].second;
	}

      for(vector<Block::PointState>::iterator it = bloque.vertex.begin();
	  it != bloque.vertex.end();
	  ++it)
	{
	  it->norm = norm[it->point].first * (1.0f / norm[it->point].second);
	}
      
      bloque.m_vertex_normal = true;
    }
  }
  
  void Mesh::normalizeFaces(Block& bloque)
  {
    if (!bloque.m_faces_normal) {
      for (int j = 0; j < bloque.faces.size(); j++ ) {
	Triangle& tri = bloque.faces[j].tri;
	bloque.faces[j].norm = (tri[1]-tri[0]).normal(tri[2]-tri[0]);
      }
      bloque.m_faces_normal = true;
    }
  }
  
  void Mesh::end()
  {
    switch ((m_blocks.end()-1)->normal) {
    case VERTEX:
      normalizeVertex(*(m_blocks.end()-1));
      break;
    case FACE:
      normalizeFaces(*(m_blocks.end()-1));
      break;
    default:
      break;
    }
  }

  void Mesh::makeTexture (SDL_Surface * surf, GLuint * tex, GLint filter)
  {
    Uint32 saved_flags;
    Uint8  saved_alpha;
    Uint32 w, h;
    SDL_Surface *conv = NULL;
    
    w = power_of_two(surf->w);
    h = power_of_two(surf->h),
    
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      conv = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, surf->format->BitsPerPixel,
				  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
#else
    conv = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, surf->format->BitsPerPixel,
				0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
#endif
    
    /* Save the alpha blending attributes */
    saved_flags = surf->flags; //&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surf->format->alpha;
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA )
      {
        SDL_SetAlpha(surf, 0, 0);
      }
    
    SDL_BlitSurface(surf, 0, conv, 0);
    
    /* Restore the alpha blending attributes */
    if ( (saved_flags & SDL_SRCALPHA)
	 == SDL_SRCALPHA ) {
      SDL_SetAlpha(surf, saved_flags, saved_alpha);
    }
    
    glGenTextures(1, &*tex);
    glBindTexture(GL_TEXTURE_2D , *tex);
      
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
      
    glPixelStorei(GL_UNPACK_ROW_LENGTH, conv->pitch / conv->format->BytesPerPixel);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, conv->pixels);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    
    SDL_FreeSurface(conv);
  }


  bool Mesh::setMaterial(const Point4F& ambient,
			 const Point4F& diffuse,
			 const Point4F& specular,
			 int brillo)
  {
    for( int i = 0; i < m_blocks.size(); ++i ) {
      Block& b = m_blocks[i];

      //Block& b = *(m_blocks.end()-1);
      b.ambient = ambient;
      b.diffuse = diffuse;
      //colour(PointF(0.1, 0.9, 0.1));
      b.specular = specular;
      b.brillo = brillo;
    }
    return false;
  }

  bool Mesh::setTexture(const char *texName)
  {
    Block& b = *(m_blocks.end()-1);
    bool status = false;
    SDL_Surface* tex_image;

    if(tex_image = IMG_Load( const_cast<char*> (texName) )  )
      {
	status = true;
#if 0	
	status = true;
	/* Create The Texture */
	glGenTextures( 1, &b.texture );

	/* Typical Texture Generation Using Data From The Bitmap */
	glBindTexture( GL_TEXTURE_2D, b.texture );

	/* Generate The Texture */
	glTexImage2D( GL_TEXTURE_2D, 0, 3, tex_image->w,
		      tex_image->h, 0, GL_BGR,
		      GL_UNSIGNED_BYTE, tex_image->pixels );

	/* Linear Filtering */
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
#endif

	makeTexture (tex_image, &b.texture, GL_LINEAR);
	SDL_FreeSurface(tex_image);
      }
        
    return status;
  }
  
  void Mesh::blending(const Point4F& level){
    Block& b = *(m_blocks.end()-1);
    b.has_blend = true;
    b.blend_level = level;
    /* Blending Function For Translucency Based On Source Alpha Value  */
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE );
  }
  
  void Mesh::draw()
  {
    for( int i = 0; i < m_blocks.size(); ++i ) {
      Block& bloque = m_blocks[i];

      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&bloque.ambient[0]);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,&bloque.diffuse[0]);
      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&bloque.specular[0]);
      glMaterialf (GL_FRONT_AND_BACK,GL_SHININESS, bloque.brillo);

      if( bloque.texture != -1) {
	/* Select Our Texture */	
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL); // <- Habilitar color (glColor)
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture( GL_TEXTURE_2D, bloque.texture );
      }

      if(bloque.has_blend == true){
	//glEnable( GL_BLEND );
	//glDisable( GL_DEPTH_TEST );
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4ub(bloque.blend_level[0], bloque.blend_level[1],
	//	   bloque.blend_level[2], bloque.blend_level[3]);

      }
      
      glBegin(GL_TRIANGLES);

      for (int j = 0; j < bloque.vertex.size(); ++j ) {
	if (bloque.m_faces_normal &&
	    !bloque.m_vertex_normal &&
	    j % 3 == 0)
	  glNormal3fv(&bloque.faces[j/3].norm[0]);
	if(&bloque.vertex[j].has_color)
	  glColor3fv(&bloque.vertex[j].colour[0]);
	if(&bloque.vertex[j].has_tex)
	  glTexCoord2f(bloque.vertex[j].tex[0],
		       bloque.vertex[j].tex[1]);
	if (bloque.m_vertex_normal)
	  glNormal3fv(&bloque.vertex[j].norm[0]);
	glVertex3fv(&bloque.vertex[j].point[0]);
      }

      glEnd();

      if(bloque.has_blend == true){
	glDisable( GL_BLEND );
	glEnable(GL_DEPTH_TEST);
      }
	    
      if(bloque.texture != -1) {
	glDisable(GL_TEXTURE_2D);
      }
    }
  }
  
  
} /* namespace mge */

