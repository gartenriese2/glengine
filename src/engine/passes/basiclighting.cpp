#include "basiclighting.hpp"

#include "../objects/objectinterface.hpp"
#include "../debug.hpp"
#include "../light.hpp"

BasicLighting::BasicLighting() {

	Shader vert("shader/basic.vert");
	Shader frag("shader/basiclighting.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

	m_lightBuffer.bindTo(0);
	m_materialBuffer.bindTo(1);

}

void BasicLighting::draw(const Camera & cam, const std::vector<std::shared_ptr<Light>> lights) {

	glViewport(0, 0, cam.getWidth(), cam.getHeight());

	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	int size = lights.size();
	std::vector<LightData> data;
	for (const auto & light : lights) {
		data.emplace_back(light->getData());
	}	
	m_lightBuffer.addData(data, size);
struct materialData {

	float shininess;
	float strength;

};

materialData m,m2;
m.shininess = 50.f;
m.strength = 0.5f;
m2.shininess = 50.f;
m2.strength = 0.5f;
std::vector<materialData> data2;
data2.emplace_back(m);
data2.emplace_back(m2);
m_materialBuffer.addData(data2, 2);

	for (auto id : m_objects) {

		// vertex
		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * ObjectInterface::getModelMatrix(id);
		m_program["MV_IT"] = glm::inverse(glm::transpose(cam.getViewMat() * ObjectInterface::getModelMatrix(id)));
		m_program["M"] = ObjectInterface::getModelMatrix(id);

		// fragment
		m_program["camPos"] = cam.getPos();
		m_program["viewDir"] = cam.getDir();
		m_program["lightDataSize"] = size;

		ObjectInterface::draw(id);

	}

}
