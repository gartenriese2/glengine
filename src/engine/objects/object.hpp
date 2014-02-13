#ifndef _OBJECT_
#define _OBJECT_

#include "../gl/glincludes.hpp"
#include "../glmincludes.hpp"

class Object {

	public:
	
		Object();
		virtual void draw() const = 0;

		const glm::mat4 & getModelMatrix() const { return m_modelMatrix; }

		void rotate(float radians, const glm::vec3 &);

	protected:

		GLuint m_vertexBuffer;
		GLuint m_vertexArray;

		glm::mat4 m_modelMatrix;

};

#endif // _OBJECT_