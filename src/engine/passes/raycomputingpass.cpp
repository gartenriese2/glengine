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

	m_objectBuffer.bindTo(0);

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

	struct Primitive {
		glm::vec4 A, B, C, D;
	};

	struct Object {
		Primitive p;
		glm::vec4 type; // enum {QUADRILATERAL = 1, CIRCLE, CONE, CUBOID, SPHERE, SPLINE, TRIANGLE};
	};

	std::vector<Object> objVec;

	for (auto id : m_objects) {

		std::vector<glm::vec4> v = ObjectInterface::getObjectData(id);
		glm::mat4 m = ObjectInterface::getModelMatrix(id);
		Primitive p;
		p.A = v[0];
		p.B = v[1];
		p.C = v[2];
		p.D = v[3];
		Object o;
		o.p = p;
		o.type = glm::vec4(ObjectInterface::getObjectType(id));

		switch(static_cast<int>(o.type[0])) {
			case 1:
			case 4:
				o.p.A = m * o.p.A;
				o.p.B = m * o.p.B;
				o.p.C = m * o.p.C;
				o.p.D = m * o.p.D;
				break;
			default:
				break;
		}

		objVec.emplace_back(o);

	}

	m_objectBuffer.addData(objVec, objVec.size());
	m_program["numObj"] = static_cast<int>(objVec.size());

	glDispatchCompute(cam.getWidth() / 16, cam.getHeight() / 16 , 1);
	glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);

}
