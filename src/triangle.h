
#ifndef MGE_TRIANGLE_H
#define MGE_TRIANGLE_H

#include <vector>
#include "drawable.h"
#include "point.h"

namespace mge
{
  
  class Triangle
  {
    
  private:
    //! Vector de puntos [a,b,c]
    PointF t[3];

  public:
    Triangle() {};
    inline Triangle(PointF a, PointF b, PointF c);
    inline PointF first() const;
    inline PointF second() const;
    inline PointF third() const;
    inline PointF & operator [] (const int indice);
    
  };

  Triangle::Triangle(PointF a, PointF b, PointF c)
    {
      this->t[0] = a;
      this->t[1] = b;
      this->t[2] = c;
    }

  PointF Triangle::first() const
    {
      return this->t[0];
    }

  PointF Triangle::second() const
    {
      return this->t[1];
    }

  PointF Triangle::third() const
    {
      return this->t[2];
    }
    
  PointF &Triangle::operator [] (const int index)
    {
      
      if ((index < 0) && (index>3)){
	std::cerr << "\nError indice incorrecto \n\n";
      }
      return t[index];

    }
  
  inline std::ostream &operator<< (std::ostream& os, const Triangle& p)
  {
    return os << '<' << p.first() << ',' << p.second() << ',' << p.third() <<  '>';
  }


} /* namespace mge */



#endif /* MGE_TRIANGLE_H */
