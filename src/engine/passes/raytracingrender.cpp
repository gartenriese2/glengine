#include "raytracingrender.hpp"

RaytracingRender::RaytracingRender(Camera & cam, std::vector<std::shared_ptr<Light>> lights)
  : m_cam(cam),
  	m_lights(lights),
  	m_colorTex(cam.getWidth(), cam.getHeight()),
  	m_positionTex(cam.getWidth(), cam.getHeight(), GL_RGB32F),
  	m_reflectedTex(cam.getWidth(), cam.getHeight(), GL_RGB32F),
  	m_depthAttachment(cam.getWidth(), cam.getHeight(), GL_DEPTH_COMPONENT32F),
  	m_result(cam.getWidth(), cam.getHeight(), GL_RGBA32F),
  	m_raycomputingPass(m_positionTex, m_reflectedTex, m_colorTex, m_result),
  	m_texturePass(m_result)
{

	m_fbo.attachColorTexture(m_colorTex);
	m_fbo.attachColorTexture(m_positionTex);
	m_fbo.attachColorTexture(m_reflectedTex);
	m_fbo.attachDepthTexture(m_depthAttachment);

}

void RaytracingRender::draw() {

	m_raycastingPass.draw(m_cam, m_fbo, m_lights);

	m_raycomputingPass.draw(m_cam, m_lights);

	m_texturePass.draw();

}

void RaytracingRender::changeBaseSize(unsigned int w, unsigned int h) {

	m_cam.resize(w, h);

	m_result.resize(w, h);

	m_fbo.bind(GL_DRAW_FRAMEBUFFER);

	m_colorTex.resize(w, h);
	m_positionTex.resize(w, h);
	m_reflectedTex.resize(w, h);
	m_depthAttachment.resize(w, h);

	m_colorTex.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, m_colorTex(), 0);
	m_colorTex.unbind();

	m_positionTex.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, m_positionTex(), 0);
	m_positionTex.unbind();

	m_reflectedTex.bind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 2, GL_TEXTURE_2D, m_reflectedTex(), 0);
	m_reflectedTex.unbind();

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
