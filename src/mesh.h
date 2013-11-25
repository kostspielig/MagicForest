
#ifndef MGE_MESH_H
#define MGE_MESH_H

#include <vector>
#include "drawable.h"
#include "point.h"
#include "point2.h"
#include "point4.h"
#include "triangle.h"
#include "file_ply_stl.h"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>

namespace mge
{
  
  class Mesh : public Drawable
  {
  public:
    enum Mode {
      TRIANGLES = GL_TRIANGLES,
      QUADS = GL_QUADS
    };

    enum Normal {
      NONE = 0,
      FACE,
      VERTEX
    };
    
  private:
    struct Block {
      struct PointState {
	Point2F tex;
	PointF point;
	PointF colour;
	PointF norm;
	bool has_color;
	bool has_tex;
      };

      struct FaceState {
	Triangle tri;
	PointF norm;
      };

      
      GLuint texture;
      PointF curr_colour;
      Point2F curr_tex;
      Mode mode;
      Normal normal;
      
      std::vector<PointState> vertex;
      std::vector<FaceState> faces;

      bool m_faces_normal;
      bool m_vertex_normal;
      bool has_color;
      bool has_tex;
      bool has_blend;

      Point4F ambient;
      Point4F diffuse;
      Point4F specular;
      int brillo;
      Point4F blend_level;
      int p_count;
      
      Block() :
	m_faces_normal(false),
	m_vertex_normal(false),
	has_color(false),
	has_tex(false),
	texture(-1),
	has_blend(false),
	ambient(Point4F(0.5f, 0.5f, 0.5f, 1.0)),
	diffuse(Point4F(0.7, 0.7, 0.7, 1.0)),
	specular(Point4F(1.0, 1.0, 1.0, 1.0)),
	brillo(128){
      }
    };

    std::vector<Block> m_blocks;

    void normalizeFaces(Block& b);
    void normalizeVertex(Block& b);

    void makeTexture (SDL_Surface * surf, GLuint * tex, GLint filter);
  public:
   
    
    void begin(Mode mode, int n_vertex_est = 0, Normal normal = VERTEX);
    int  loadPly(const char *plyName);
    void point(const PointF& p);
    void texCoord(const Point2F & t);
    void colour(const PointF& p);
    bool setMaterial(const Point4F& ambient,
		     const Point4F& diffuse,
		     const Point4F& specular,
		     int brillo);
    bool setTexture(const char* texname);
    void blending(const Point4F& level);
    void end();

  public:
    void draw();
  };
  
} /* namespace mge */

#endif /* MGE_MESH_H */

