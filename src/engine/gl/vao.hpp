#ifndef _VAO_
#define _VAO_

#include "glincludes.hpp"

#include <string>

namespace gl {

class VBO;
class IBO;

class VAO {

	public:

		VAO();
		VAO(VAO &&);
		VAO & operator=(VAO &&) &;
		~VAO();

		operator GLuint() const { return m_name; }

		const std::string getLabel() const;
		void setLabel(const std::string &);

		void attachVBO(const gl::VBO &, GLuint, GLuint);
		void attachIBO(const gl::IBO &);

	private:

		VAO(const VAO &) = delete;
		VAO & operator=(const VAO &) & = delete;

		void attachBuffer(GLuint, GLint, GLenum, bool, GLuint, GLuint, GLsizei, GLuint);
		void attachIndexBuffer(GLuint);

		GLuint m_name;

};

} // namespace gl

#endif // _VAO_
