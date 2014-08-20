#ifndef _RAYCOMPUTINGPASS_
#define _RAYCOMPUTINGPASS_

#include "pass.hpp"
#include "../gl/shaderstoragebuffer.hpp"

class FBO;
class Texture;

class RaycomputingPass : public Pass {

	public:

		RaycomputingPass(Texture &, Texture &, Texture &, Texture &);

		void draw(const Camera &, const std::vector<std::shared_ptr<Light>>);

	private:

		Texture & m_positionTex;
		Texture & m_directionTex;
		Texture & m_colorTex;
		Texture & m_result;

		ShaderStorageBuffer m_triangleBuffer;
		ShaderStorageBuffer m_lightBuffer;

};

#endif // _RAYCOMPUTINGPASS_
