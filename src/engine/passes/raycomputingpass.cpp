#include "raycomputingpass.hpp"

#include "../camera.hpp"
#include "../objects/objectinterface.hpp"
#include "../debug.hpp"
#include "../light.hpp"

RaycomputingPass::RaycomputingPass(Texture & positionTex, Texture & directionTex, Texture & color, Texture & result)
  : m_positionTex(positionTex),
  	m_directionTex(directionTex),
  	m_colorTex(color),
  	m_result(result)
{

	Shader comp(k_dir + "raytracing.comp");
	m_program.attachShader(comp);

}

void RaycomputingPass::draw(const Camera & cam, const std::vector<std::shared_ptr<Light>> lights) {

	m_program.use();

	glBindImageTexture(3, m_result, 0, false, 0, GL_READ_WRITE, GL_RGBA32F);

	m_program["windowWidth"] = cam.getWidth();
	m_program["windowHeight"] = cam.getHeight();

	m_program["positionTex"] = 0;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_positionTex);

	m_program["directionTex"] = 1;
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_directionTex);

	m_program["colorTex"] = 2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_colorTex);

	m_triangleBuffer.bindTo(0);
	m_lightBuffer.bindTo(1);

	std::vector<Tri> triVec;

	for (auto id : m_objects) {

		glm::mat4 m = ObjectInterface::getModelMatrix(id);

		for (Tri tri : ObjectInterface::getObjectTriangles(id)) {

			tri.mult(m);
			triVec.emplace_back(tri);

		}

	}

	m_triangleBuffer.addData(triVec, triVec.size());
	m_program["numTri"] = static_cast<int>(triVec.size());

	int size = lights.size();
	std::vector<LightData> data;
	for (const auto & light : lights) {
		data.emplace_back(light->getData());
	}	

	m_lightBuffer.addData(data, size);
	m_program["numLights"] = size;

	glDispatchCompute(cam.getWidth() / 16, cam.getHeight() / 16 , 1);
	glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);

}
