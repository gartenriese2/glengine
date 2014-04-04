#include "basic.hpp"

#include "../objects/objectinterface.hpp"
#include "../debug.hpp"

Basic::Basic() {

	Shader vert("shader/basic.vert");
	Shader frag("shader/basic.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

}

void Basic::draw(const Camera & cam) {

	glViewport(0, 0, cam.getWidth(), cam.getHeight());

	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	for (auto id : m_objects) {

		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * ObjectInterface::getModelMatrix(id);
		ObjectInterface::draw(id);

	}

}
