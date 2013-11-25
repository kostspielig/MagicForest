/**
 * @file point.h
 * Implementation of Data Type Point
 * @author María Carrasco Rodríguez
 * 
 */

#ifndef MGE_POINT_H
#define MGE_POINT_H

#include <iostream>
#include <cmath>

namespace mge
{

  template <class T>
  class Point {
      
  private:

    //! Vector de puntos [x,y,z]
    T p[3];


  public:

    Point();

    Point(T x, T y, T z);

    Point(const Point& org);

    void set(T nx, T ny, T nz);
    void setX(T x);
    void setY(T y);
    void setZ(T z);

    T x () const;
    T y () const;
    T z () const;

    Point& operator += (const Point &p);
    Point operator +(const Point &p) const;
    Point operator -(const Point &p) const;
    T length() const;
    T sqrLength() const;
    Point operator *(const T & t) const;
    Point operator * (const Point & p) const;
    Point cross(const Point & p) const;
    Point dot(const Point & p) const;
    Point normalize() const;
    Point normal(const Point & p) const;
    bool operator < (const Point& p) const;

    
    Point & operator=(const Point &p);
    bool operator==(const Point<T> &p);
    bool operator!=(const Point<T> &p);
    T & operator[] (const int indice);

  };

  /**
   * Implementation of the functions of Point
   */
  typedef Point<float> PointF;

  
  template <class T>
  inline std::ostream& operator<< (std::ostream& os, const Point<T>& p)
  {
    return os << '(' << p.x() << ',' << p.y() << ',' << p.z() <<  ')';
  }

  
  template <class T>
  inline std::istream& operator>> (std::istream& is, Point<T>& p)
  {
    char caracter;
    T x,y,z;
    is >> caracter >> x >> caracter >> y >> caracter >> z >> caracter;
    p = Point<T> (x,y,z);
    return is;
  }

 
  template <class T> Point<T>::Point()
  {
    this->p[0] = 0;
    this->p[1] = 0;
    this->p[2] = 0;
  }


  template <class T> Point<T>::Point(T x, T y, T z)
  {
    this->p[0] = x;
    this->p[1] = y;
    this->p[2] = z;

  }


  template <class T> Point<T>::Point(const Point<T> &orig)
  {
    p[0] = orig.x();
    p[1] = orig.y();
    p[2] = orig.z();
  }


  template <class T> void Point<T>::set(T x, T y, T z)
  {
    this->p[0] = x;
    this->p[1] = y;
    this->p[2] = z;

  }


  template <class T> void Point<T>::setX(T x)
  {
    this->p[0] = x;
  }


  template <class T> void Point<T>::setY(T y)
  {
    this->p[1] = y;
  }


  template <class T> void Point<T>::setZ(T z)
  {
    this->p[2] = z;
  }


  template <class T> T Point<T>::x() const
  {
    return this->p[0];
  }


  template <class T> T Point<T>::y() const
  {
    return this->p[1];
  }


  template <class T> T Point<T>::z() const
  {
    return this->p[2];
  }


  template <class T>
  Point<T> & Point<T>::operator=(const Point<T> &po)
  {
    p[0] = po.x();
    p[1] = po.y();
    p[2] = po.z();
    return (*this);
  }


  template <class T>
  bool Point<T>::operator==(const Point<T> &po)
  {
    return ((p[0] == po.x()) && (p[1] == po.y()) && (p[2] == po.z()) ?1:0); 
  }


  template <class T>
  bool Point<T>::operator!=(const Point<T> &po)
  {
    return ((p[0] != po.x()) || (p[1] != po.y()) || (p[2] != po.z()) ?1:0); 
  }


  template <class T>
  T &Point<T>::operator[](const int indice)
  {
    if ((indice < 0) && (indice>3)){
      std::cerr << "\nError indice incorrecto \n\n";
    }
    return p[indice];
  }


  template<class T>
  Point<T>& Point<T>::operator += (const Point<T> &v) {
    p[0] += v.p[0];
    p[1] += v.p[1];
    p[2] += v.p[2];
    return *this;
  }
  

  template<class T>
  Point<T> Point<T>::operator +(const Point<T> &v) const {
    return Point<T>(v.p[0] + p[0], v.p[1] + p[1], v.p[2] + p[2]);
  }
  
  
  template<class T>
  Point<T> Point<T>::operator -(const Point &v) const {
    return Point<T>(p[0] - v. p[0], p[1] - v.p[1], p[2] - v.p[2]);
  }

  
  template<class T>
  T Point<T>::length() const {
    return std::sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
  }


  template<class T>
  T Point<T>::sqrLength() const {
    return p[0]*p[0] + p[1]*p[1] + p[2]*p[2];
  }


  template<class T>
  Point<T> Point<T>::operator *(const T & t) const
  {
    return Point<T>(t * p[0], t * p[1], t * p[2]);
  }


  template<class T>
  Point<T> Point<T>::operator * (const Point & v) const
  {
    return Point<T>(v.p[0] * p[0], v.p[1] * p[1], v.p[2] * p[2]);
  }


  template<class T>
  Point<T> Point<T>::dot (const Point & v) const
  {
    return Point<T>(v.p[0] * p[0], v.p[1] * p[1], v.p[2] * p[2]);
  }


  template<class T>
  Point<T> Point<T>::cross (const Point & v) const
  {
    return Point<T>(p[1]*v.p[2] - p[2]*v.p[1],
		    p[2]*v.p[0] - p[0]*v.p[2],
		    p[0]*v.p[1] - p[1]*v.p[0]);
  }
 

  template<class T>
  Point<T> Point<T>::normalize () const
  {
    float l = length();
    if (l == 0.0f) return Point<T>(0,0,0);
    return *this * (1.0f / l);
  }


  template<class T>
  Point<T> Point<T>::normal (const Point & v) const
  {
    Point<T> n = cross(v);
    T l = n.length();
    if (l == 0)
      return Point<T>(0, 0, 0);

    return n * (1.0f / l);
  }


  template<class T>
  bool Point<T>::operator < (const Point<T>& v) const
  {
    return
      p[0] == v.p[0] ?
      p[1] == v.p[1] ?
      p[2] <  v.p[2] :
      p[1] <  v.p[1] :
      p[0] <  v.p[0];
  }
  
} /* namespace mge */


#endif /* MGE_POINT_H */

