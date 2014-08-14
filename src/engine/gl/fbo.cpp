#include "fbo.hpp"

#include "texture.hpp"
#include "../debug.hpp"

FBO::FBO()
  : m_colorAttachments{0}
{

	glCreateFramebuffers(1, &m_name);

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

	glNamedFramebufferTexture(m_name, GL_COLOR_ATTACHMENT0 + m_colorAttachments++, tex, 0);
	checkError(target);

}

void FBO::attachDepthTexture(const Texture & tex, GLenum target) {

	glNamedFramebufferTexture(m_name, GL_DEPTH_ATTACHMENT, tex, 0);
	checkError(target);

}

void FBO::checkError(GLenum target) const {

	GLenum err = glCheckNamedFramebufferStatus(m_name, target);
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
