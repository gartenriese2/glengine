#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include "object.hpp"

class ObjectInterface;

class Primitive : public Object {

 	public:
	
		Primitive(const Primitive &) = delete;
		Primitive(Primitive &&) = delete;
		Primitive & operator=(const Primitive &) = delete;
		Primitive & operator=(Primitive &&) = delete;

		virtual ~Primitive() {}

 	protected:

 		friend ObjectInterface;

 		Primitive() {}

		virtual void draw() const = 0;

};

#endif // _PRIMITIVE_