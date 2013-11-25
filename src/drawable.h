/**
 * @file drawable.h
 * Interface Drawable.
 * @author María Carrasco Rodríguez.
 * @date March 2008
 */

#ifndef MGE_DRAWABLE_H
#define MGE_DRAWABLE_H

namespace mge
{

  class Drawable
  {
    
  public:
    virtual ~Drawable() {}
    virtual void draw() = 0;
  };


} /* namespace mge */

#endif /* MGE_DRAWABLE_H */
