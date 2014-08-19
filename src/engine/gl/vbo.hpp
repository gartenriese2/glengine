#ifndef _VBO_
#define _VBO_

#include "glincludes.hpp"

#include <vector>

namespace gl {

class VBO {

	public:

		VBO();
		VBO(GLuint, GLenum = GL_FLOAT, bool = GL_FALSE);
		VBO(const VBO &);
		VBO(VBO &&);
		VBO & operator=(const VBO &) &;
		IBO & operator=(IBO &&) &;
		~VBO();

		operator GLuint() const { return m_name; }

		bool isValid() const;

		GLuint getSize() const { return m_size; }
		GLenum getType() const { return m_type; }
		bool normalized() const { return m_normalized; }

	private:

		GLuint m_name;
		GLuint m_size;
		GLenum m_type;
		bool m_normalized;

};

} // namespace gl

#endif // _VBO_
