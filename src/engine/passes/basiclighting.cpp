#include "basiclighting.hpp"

#include "../objects/objectinterface.hpp"
#include "../debug.hpp"
#include "../light.hpp"

BasicLighting::BasicLighting() {

	Shader vert("shader/basic.vert");
	Shader frag("shader/basiclighting.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

}

void BasicLighting::draw(const Camera & cam, const Light & light) {

	glViewport(0, 0, cam.getWidth(), cam.getHeight());

	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	for (auto id : m_objects) {

		// vertex
		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * ObjectInterface::getModelMatrix(id);
		m_program["MV_IT"] = glm::inverse(glm::transpose(cam.getViewMat() * ObjectInterface::getModelMatrix(id)));
		m_program["M"] = ObjectInterface::getModelMatrix(id);

		// fragment
		m_program["ambientLight"] = light.getAmbientColor();
		m_program["lightDir"] = light.getDir();
		m_program["lightColor"] = light.getColor();
		m_program["viewMat"] = cam.getViewMat();

		ObjectInterface::draw(id);

	}

}
