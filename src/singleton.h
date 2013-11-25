
#ifndef MGE_SINGLETON_H
#define MGE_SINGLETON_H

namespace mge
{
  template <class T>
  class Singleton
  {
    Singleton (const Singleton& s) {}
    Singleton& operator = (const Singleton& s) {}
    
  protected:
    Singleton () {}
    ~Singleton () {}

  public:
    static T& instance () {
      static T single_instance;
      return single_instance;
    }
  };
} /* namespace mge */

#endif /* MGE_SINGLETON_H */
