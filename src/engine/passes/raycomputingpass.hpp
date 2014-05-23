#ifndef _RAYCOMPUTINGPASS_
#define _RAYCOMPUTINGPASS_

#include "pass.hpp"
#include "../gl/buffer.hpp"
#include "../gl/indexbuffer.hpp"
#include "../gl/texture.hpp"
#include "../gl/shaderstoragebuffer.hpp"

class FBO;

class RaycomputingPass : public Pass {

	public:

		RaycomputingPass(Texture &, Texture &, Texture &);

		void draw(const Camera &, const FBO &);

	private:

		Texture & m_positionTex;
		Texture & m_directionTex;
		Texture & m_result;

		ShaderStorageBuffer m_objectBuffer;

};

#endif // _RAYCOMPUTINGPASS_