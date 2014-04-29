#include "fbo.hpp"

#include "texture.hpp"
#include "../debug.hpp"

FBO::FBO()
  : m_colorAttachments(0)
{

	glGenFramebuffers(1, &m_name);

}

FBO::~FBO() {

	glDeleteFramebuffers(1, &m_name);

}

void FBO::bind(GLenum target) const {

	glBindFramebuffer(target, m_name);

}

void FBO::unbind(GLenum target) const {

	glBindFramebuffer(target, 0);

}

void FBO::attachColorTexture(const Texture & tex, GLenum target) {

	bind(target);
	tex.bind();
	glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0 + m_colorAttachments++, GL_TEXTURE_2D, tex(), 0);
	tex.unbind();
	checkError(target);
	unbind(target);

}

void FBO::attachDepthTexture(const Texture & tex, GLenum target) {

	bind(target);
	tex.bind();
	glFramebufferTexture2D(target, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex(), 0);
	tex.unbind();
	checkError(target);
	unbind(target);

}

void FBO::checkError(GLenum target) const {

	GLenum err = glCheckFramebufferStatus(target);
	if (err != GL_FRAMEBUFFER_COMPLETE) {
		switch(err) {
			case GL_FRAMEBUFFER_UNDEFINED:
				Debug::log("undefined fbo");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				Debug::log("incomplete attachment");
				break;
			default:
				Debug::log("some fbo error");
		};
	}

}
