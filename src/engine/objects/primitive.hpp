#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include "object.hpp"

class Primitive : public Object {

 	public:

		virtual void draw() const = 0;

};

#endif // _PRIMITIVE_