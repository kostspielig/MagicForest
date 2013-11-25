/**
 * @file point4.h
 * Implementation of Data Type Point$
 * @author María Carrasco Rodríguez
 * 
 */

#ifndef MGE_POINT4_H
#define MGE_POINT4_H

#include <iostream>

namespace mge
{

  template <class T>
  class Point4 {
      
  private:

    //! Vector de puntos [x,y,z,t]
    T p[4];


  public:

    Point4();

    Point4(T x, T y, T z, T t);

    Point4(const Point4& org);

    void Set(T nx, T ny, T nz, T nt);
    void SetX(T x);
    void SetY(T y);
    void SetZ(T z);
    void SetT(T t);

    T x () const;
    T y () const;
    T z () const;
    T t () const;

    Point4 & operator=(const Point4 &p);
    bool operator==(const Point4<T> &p);
    bool operator!=(const Point4<T> &p);
    T & operator[] (const int indice);

  };

  /**
   * Implementation of Functions of Point4
   */
  typedef Point4<float> Point4F;

  template <class T>
  inline std::ostream& operator<< (std::ostream& os, const Point4<T>& p)
  {
    return os << '(' << p.x() << ',' << p.y() << ',' << p.z() <<',' << p.t() <<  ')';
  }


  template <class T>
  inline std::istream& operator>> (std::istream& is, Point4<T>& p)
  {
    char caracter;
    T x,y,z,t;
    is >> caracter >> x >> caracter >> y >> caracter >> z >> caracter >> t >> caracter;
    p = Point4<T> (x,y,z,t);
    return is;
  }


  template <class T> Point4<T>::Point4()
  {
    this->p[0] = 0;
    this->p[1] = 0;
    this->p[2] = 0;
    this->p[3] = 0;
  }


  template <class T> Point4<T>::Point4(T x, T y, T z, T t)
  {
    this->p[0] = x;
    this->p[1] = y;
    this->p[2] = z;
    this->p[3] = t;

  }


  template <class T> Point4<T>::Point4(const Point4<T> &orig)
  {
    p[0] = orig.x();
    p[1] = orig.y();
    p[2] = orig.z();
    p[3] = orig.t();
  }


  template <class T> void Point4<T>::Set(T x, T y, T z, T t)
  {
    this->p[0] = x;
    this->p[1] = y;
    this->p[2] = z;
    this->p[3] = t;

  }


  template <class T> void Point4<T>::SetX(T x)
  {
    this->p[0] = x;
  }


  template <class T> void Point4<T>::SetY(T y)
  {
    this->p[1] = y;
  }


  template <class T> void Point4<T>::SetZ(T z)
  {
    this->p[2] = z;
  }


  template <class T> void Point4<T>::SetT(T t)
  {
    this->p[3] = t;
  }


  template <class T> T Point4<T>::x() const
  {
    return this->p[0];
  }


  template <class T> T Point4<T>::y() const
  {
    return this->p[1];
  }


  template <class T> T Point4<T>::z() const
  {
    return this->p[2];
  }


  template <class T> T Point4<T>::t() const
  {
    return this->p[3];
  }


  template <class T>
  Point4<T> & Point4<T>::operator=(const Point4<T> &po)
  {
    p[0] = po.x();
    p[1] = po.y();
    p[2] = po.z();
    p[3] = po.t();
    return (*this);
  }


  template <class T>
  bool Point4<T>::operator==(const Point4<T> &po)
  {
    return ((p[0] == po.x()) && (p[1] == po.y()) && (p[2] == po.z()&& (p[3] == po.t()) ?1:0)); 
  }


  template <class T>
  bool Point4<T>::operator!=(const Point4<T> &po)
  {
    return (( (p[0] != po.x()) || (p[1] != po.y()) || (p[2] != po.z()) || (p[3] != po.t()) ?1:0 )) ; 
  }


  template <class T>
  T &Point4<T>::operator[](const int indice)
  {
    if ((indice < 0) && (indice>4)){
      std::cerr << "\nError indice incorrecto \n\n";
    }
    return p[indice];
  }

}

#endif /* MGE_POINT4_H */

