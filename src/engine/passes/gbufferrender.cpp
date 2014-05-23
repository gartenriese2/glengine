#include "gbufferrender.hpp"

GBufferRender::GBufferRender(Camera & cam)
  : m_cam(cam),
  	m_colorTex(cam.getWidth(), cam.getHeight()),
  	m_depthTex(cam.getWidth(), cam.getHeight(), GL_R32F),
  	m_normalTex(cam.getWidth(), cam.getHeight(), GL_RGB32F),
  	m_positionTex(cam.getWidth(), cam.getHeight(), GL_RGB32F),
  	m_depthAttachment(cam.getWidth(), cam.getHeight(), GL_DEPTH_COMPONENT32F)
{

	m_fbo.attachColorTexture(m_colorTex);
	m_fbo.attachColorTexture(m_depthTex);
	m_fbo.attachColorTexture(m_normalTex);
	m_fbo.attachColorTexture(m_positionTex);
	m_fbo.attachDepthTexture(m_depthAttachment);

}

void GBufferRender::draw() {

	m_gbufferPass.draw(m_cam, m_fbo);

	m_fbo.bind(GL_READ_FRAMEBUFFER);

	glDrawBuffer(GL_BACK);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0, 0, m_cam.getWidth(), m_cam.getHeight(),
		0, m_cam.getHeight() / 2.f, m_cam.getWidth() / 2.f, m_cam.getHeight(),
		GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT1);

	glBlitFramebuffer(0, 0, m_cam.getWidth(), m_cam.getHeight(),
		m_cam.getWidth() / 2.f, m_cam.getHeight() / 2.f, m_cam.getWidth(), m_cam.getHeight(),
		GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT2);
	glBlitFramebuffer(0, 0, m_cam.getWidth(), m_cam.getHeight(),
		0, 0, m_cam.getWidth() / 2.f, m_cam.getHeight() / 2.f,
		GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT3);
	glBlitFramebuffer(0, 0, m_cam.getWidth(), m_cam.getHeight(),
		m_cam.getWidth() / 2.f, 0, m_cam.getWidth(), m_cam.getHeight() / 2.f,
		GL_COLOR_BUFFER_BIT, GL_LINEAR);

	m_fbo.unbind();

}

void GBufferRender::changeBaseSize(unsigned int w, unsigned int h) {

	m_cam.resize(w, h);

	m_fbo.bind(GL_DRAW_FRAMEBUFFER);

	m_colorTex.resize(w, h);
	m_depthTex.resize(w, h);
	m_normalTex.resize(w, h);
	m_positionTex.resize(w, h);
	m_depthAttachment.resize(w, h);

	m_colorTex.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, m_colorTex(), 0);
	m_colorTex.unbind();

	m_depthTex.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, m_depthTex(), 0);
	m_depthTex.unbind();

	m_normalTex.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 2, GL_TEXTURE_2D, m_normalTex(), 0);
	m_normalTex.unbind();

	m_positionTex.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 3, GL_TEXTURE_2D, m_positionTex(), 0);
	m_positionTex.unbind();

	m_depthAttachment.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment(), 0);
	m_depthAttachment.unbind();

	GLenum err = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
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

	m_fbo.unbind(GL_DRAW_FRAMEBUFFER);

}
