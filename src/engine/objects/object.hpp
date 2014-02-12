#ifndef _OBJECT_
#define _OBJECT_

#include "../gl/glincludes.hpp"

class Object {

	public:
	
		Object();
		virtual void draw() const = 0;

	protected:

		GLuint m_vertexBuffer;
		GLuint m_vertexArray;

};

#endif // _OBJECT_