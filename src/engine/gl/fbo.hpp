#ifndef _FBO_
#define _FBO_

#include "glincludes.hpp"

class Texture;

class FBO {

	public:

		FBO();
		~FBO();

		void bind(GLenum = GL_FRAMEBUFFER) const;
		void unbind(GLenum = GL_FRAMEBUFFER) const;
		void attachColorTexture(const Texture &, GLenum = GL_FRAMEBUFFER);
		void attachDepthTexture(const Texture &, GLenum = GL_FRAMEBUFFER);

	private:

		void checkError(GLenum = GL_FRAMEBUFFER) const;

		GLuint m_name;
		unsigned int m_colorAttachments;

};

#endif // _FBO_
