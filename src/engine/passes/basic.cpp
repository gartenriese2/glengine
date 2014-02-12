#include "basic.hpp"

Basic::Basic() {

	Shader vert("shader/basic.vert");
	Shader frag("shader/basic.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

}

void Basic::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	for (const auto obj : m_objects) {

		obj->draw();

	}

}

void Basic::addObjects(const Object & obj) {

	m_objects.emplace_back(& obj);

}
