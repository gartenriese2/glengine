#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include "object.hpp"
#include "../debug.hpp"

class ObjectInterface;

class Primitive : public Object {

 	public:
	
		Primitive(Primitive &&) = delete;
		Primitive & operator=(const Primitive &) = delete;
		Primitive & operator=(Primitive &&) = delete;

		virtual ~Primitive() {}

 	protected:

 		friend ObjectInterface;

 		Primitive() {}
 		Primitive(const Primitive & p) : Object(p) {}

		virtual void draw() const = 0;

};

#endif // _PRIMITIVE_