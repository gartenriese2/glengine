#ifndef _RAYCASTINGPASS_
#define _RAYCASTINGPASS_

#include "pass.hpp"
#include "../gl/buffer.hpp"
#include "../gl/indexbuffer.hpp"
#include "../gl/texture.hpp"

#include "../gl/program.hpp"

class FBO;

class RaycastingPass : public Pass {

	public:

		RaycastingPass();

		void draw(const Camera &, const FBO &);

	private:

		Program m_compProg;

};

#endif // _RAYCASTINGPASS_
