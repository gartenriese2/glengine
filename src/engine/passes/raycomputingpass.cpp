#include "raycomputingpass.hpp"

#include "../camera.hpp"
#include "../objects/objectinterface.hpp"
#include "../gl/fbo.hpp"
#include "../debug.hpp"

RaycomputingPass::RaycomputingPass(Texture & positionTex, Texture & directionTex, Texture & result)
  : m_positionTex(positionTex),
  	m_directionTex(directionTex),
  	m_result(result)
{

	Shader comp(k_dir + "raytracing.comp");
	m_program.attachShader(comp);

	m_triangleBuffer.bindTo(0);

}

void RaycomputingPass::draw(const Camera & cam, const FBO & fbo) {

	m_program.use();

	glBindImageTexture(2, m_result(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);

	m_program["windowWidth"] = cam.getWidth();
	m_program["windowHeight"] = cam.getHeight();

	m_program["positionTex"] = 0;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_positionTex());

	m_program["directionTex"] = 1;
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_directionTex());

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

	glDispatchCompute(cam.getWidth() / 16, cam.getHeight() / 16 , 1);
	glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);

}
