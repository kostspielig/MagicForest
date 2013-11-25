/**
 * @file point2.h
 * Implementation of Data Type Point2
 * @author María Carrasco Rodríguez
 * 
 */

#ifndef MGE_POINT2_H
#define MGE_POINT2_H

#include <iostream>
#include <cmath>

namespace mge
{

  template <class T>
  class Point2 {
      
  private:

    //! Vector de puntos [x,y]
    T p[2];


  public:

    Point2();

    Point2(T x, T y);

    Point2(const Point2& org);

    void set(T nx, T ny);
    void setX(T x);
    void setY(T y);

    T x () const;
    T y () const;


    Point2& operator += (const Point2 &p);
    Point2 operator +(const Point2 &p) const;
    Point2 operator -(const Point2 &p) const;
    T length() const;
    T sqrLength() const;
    Point2 operator *(const T & t) const;
    Point2 operator * (const Point2 & p) const;
    Point2 dot(const Point2 & p) const;
    bool operator < (const Point2& p) const;
    Point2 & operator=(const Point2 &p);
    bool operator==(const Point2<T> &p);
    bool operator!=(const Point2<T> &p);
    T & operator[] (const int indice);

  };

  /**
   * Implementation of functions of Point2
   */
  typedef Point2<float> Point2F;

  template <class T>
  inline std::ostream& operator<< (std::ostream& os, const Point2<T>& p)
  {
    return os << '(' << p.x() << ',' << p.y() <<  ')';
  }

  
  template <class T>
  inline std::istream& operator>> (std::istream& is, Point2<T>& p)
  {
    char caracter;
    T x,y,z;
    is >> caracter >> x >> caracter >> y >> caracter;
    p = Point2<T> (x,y);
    return is;
  }

  
  template <class T> Point2<T>::Point2()
  {
    this->p[0] = 0;
    this->p[1] = 0;
  }


  template <class T> Point2<T>::Point2(T x, T y )
  {
    this->p[0] = x;
    this->p[1] = y;

  }


  template <class T> Point2<T>::Point2(const Point2<T> &orig)
  {
    p[0] = orig.x();
    p[1] = orig.y();
  }


  template <class T> void Point2<T>::set(T x, T y)
  {
    this->p[0] = x;
    this->p[1] = y;

  }


  template <class T> void Point2<T>::setX(T x)
  {
    this->p[0] = x;
  }


  template <class T> void Point2<T>::setY(T y)
  {
    this->p[1] = y;
  }


  template <class T> T Point2<T>::x() const
  {
    return this->p[0];
  }


  template <class T> T Point2<T>::y() const
  {
    return this->p[1];
  }


  template <class T>
  Point2<T> & Point2<T>::operator=(const Point2<T> &po)
  {
    p[0] = po.x();
    p[1] = po.y();
    return (*this);
  }


  template <class T>
  bool Point2<T>::operator==(const Point2<T> &po)
  {
    return ((p[0] == po.x()) && (p[1] == po.y()) ?1:0); 
  }


  template <class T>
  bool Point2<T>::operator!=(const Point2<T> &po)
  {
    return ((p[0] != po.x()) || (p[1] != po.y()) ?1:0); 
  }


  template <class T>
  T &Point2<T>::operator[](const int indice)
  {
    if ((indice < 0) && (indice>2)){
      std::cerr << "\nError indice incorrecto \n\n";
    }
    return p[indice];
  }


  template<class T>
  Point2<T>& Point2<T>::operator += (const Point2<T> &v) {
    p[0] += v.p[0];
    p[1] += v.p[1];
    return *this;
  }
  

  template<class T>
  Point2<T> Point2<T>::operator +(const Point2<T> &v) const {
    return Point2<T>(v.p[0] + p[0], v.p[1] + p[1]);
  }
  
  
  template<class T>
  Point2<T> Point2<T>::operator -(const Point2 &v) const {
    return Point2<T>(p[0] - v. p[0], p[1] - v.p[1]);
  }

  
  template<class T>
  T Point2<T>::length() const {
    return std::sqrt(p[0]*p[0] + p[1]*p[1]);
  }


  template<class T>
  T Point2<T>::sqrLength() const {
    return p[0]*p[0] + p[1]*p[1];
  }


  template<class T>
  Point2<T> Point2<T>::operator *(const T & t) const
  {
    return Point2<T>(t * p[0], t * p[1]);
  }


  template<class T>
  Point2<T> Point2<T>::operator * (const Point2 & v) const
  {
    return Point2<T>(v.p[0] * p[0], v.p[1] * p[1]);
  }


  template<class T>
  Point2<T> Point2<T>::dot (const Point2 & v) const
  {
    return Point2<T>(v.p[0] * p[0], v.p[1] * p[1]);
  }


  template<class T>
  bool Point2<T>::operator < (const Point2<T>& v) const
  {
    return
      p[0] == v.p[0] ?
      p[1] <  v.p[1] :
      p[0] <  v.p[0] ;
  }
  
} /* namespace mge */


#endif /* MGE_POINT2_H */
