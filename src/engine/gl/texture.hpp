#ifndef _TEXTURE_
#define _TEXTURE_

#include "glincludes.hpp"

class Texture {

	public:

		Texture(unsigned int, unsigned int, GLenum = GL_RGBA32F);
		~Texture();

		operator GLuint() const { return m_name; }
		
		void resize(unsigned int, unsigned int);

	private:

		const GLenum m_target {GL_TEXTURE_2D};

		GLuint m_name;
		unsigned int m_width;
		unsigned int m_height;
		GLenum m_format;

};

#endif // _TEXTURE_
