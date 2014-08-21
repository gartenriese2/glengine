#ifndef _VAO_
#define _VAO_

#include "glincludes.hpp"
#include "globject.hpp"

#include <string>

namespace gl {

class VBO;
class IBO;

class VAO : public gl::Object {

	public:

		VAO();
		VAO(VAO && v) : gl::Object{std::forward<gl::Object>(v)} {}
		VAO & operator=(VAO &&) &;
		~VAO();

		bool isValid() const;

		void attachVBO(const gl::VBO &, GLuint, GLuint);
		void attachIBO(const gl::IBO &);

	private:

		VAO(const VAO &) = delete;
		VAO & operator=(const VAO &) & = delete;

		void attachBuffer(GLuint, GLint, GLenum, bool, GLuint, GLuint, GLsizei, GLuint);
		void attachIndexBuffer(GLuint);

};

} // namespace gl

#endif // _VAO_
