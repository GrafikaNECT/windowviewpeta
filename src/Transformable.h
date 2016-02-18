#ifndef Transformable_h
#define Transformable_h

#include "Rotateable.h"
#include "Scaleable.h"
#include "Translateable.h"

class Transformable: public Rotateable, public Scaleable, public Translateable{

};

#endif
