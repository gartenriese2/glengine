#include "raycastingpass.hpp"

#include "../camera.hpp"
#include "../objects/objectinterface.hpp"
#include "../gl/fbo.hpp"
#include "../debug.hpp"

RaycastingPass::RaycastingPass() {

	Shader vert(k_dir + "basic.vert");
	Shader frag(k_dir + "raytracing.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

}

void RaycastingPass::draw(const Camera & cam, const FBO & fbo) {

	fbo.bind();

	glViewport(0, 0, cam.getWidth(), cam.getHeight());

	GLenum db[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, db);

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	m_program.use();

	m_program["camPos"] = cam.getPos();

	for (auto id : m_objects) {

		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * ObjectInterface::getModelMatrix(id);
		m_program["M_IT"] = glm::inverse(glm::transpose(ObjectInterface::getModelMatrix(id)));
		m_program["M"] = ObjectInterface::getModelMatrix(id);
		ObjectInterface::draw(id);

	}
		
	fbo.unbind();

}
