#ifndef _FBO_
#define _FBO_

#include "glincludes.hpp"
#include "globject.hpp"

class Texture;

class FBO : public gl::Object {

	public:

		FBO();
		~FBO();

		bool isValid() const;

		void bind(GLenum = GL_FRAMEBUFFER) const;
		void unbind(GLenum = GL_FRAMEBUFFER) const;
		void attachColorTexture(const Texture &, GLenum = GL_FRAMEBUFFER);
		void attachDepthTexture(const Texture &, GLenum = GL_FRAMEBUFFER);

		void checkError(GLenum = GL_FRAMEBUFFER) const;

		void blit(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint,
			GLbitfield = GL_COLOR_BUFFER_BIT, GLenum = GL_LINEAR);

	private:		

		unsigned int m_colorAttachments;

};

#endif // _FBO_
