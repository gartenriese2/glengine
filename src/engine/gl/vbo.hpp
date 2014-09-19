#ifndef _VBO_
#define _VBO_

#include "glincludes.hpp"
#include "buffer.hpp"

#include <vector>

namespace gl {

class VBO : public gl::Buffer {

	public:

		VBO();
		VBO(GLuint);
		VBO(const VBO &);
		VBO(VBO &&);
		VBO & operator=(const VBO &) &;
		VBO & operator=(VBO &&);
		~VBO() {}

		GLuint getChannels() const { return m_channels; }
		GLenum getType() const { return GL_FLOAT; }
		GLuint getTypeSize() const { return sizeof(GLfloat); }
		bool normalized() const { return false; }

		void insertData(const std::vector<GLfloat> &, GLenum = GL_STATIC_DRAW);

	private:

		GLuint m_channels;

};

} // namespace gl

#endif // _VBO_
