#ifndef _GBUFFERPASS_
#define _GBUFFERPASS_

#include "pass.hpp"

class FBO;

class GBufferPass : public Pass {

	public:

		GBufferPass();

		void draw(const Camera &, const FBO &);

};

#endif // _GBUFFERPASS_
