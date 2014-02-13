#include "basic.hpp"

Basic::Basic() {

	Shader vert("shader/basic.vert");
	Shader frag("shader/basic.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

}

void Basic::draw(const Camera & cam) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	for (const auto obj : m_objects) {

		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * obj->getModelMatrix();
		// m_program.transmit("MVP", cam.getProjMat() * cam.getViewMat() * obj->getModelMatrix());
		obj->draw();

	}

}
