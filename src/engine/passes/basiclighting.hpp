#ifndef _BASICLIGHTING_
#define _BASICLIGHTING_

#include "pass.hpp"
#include "../gl/shaderstoragebuffer.hpp"

#include <vector>

class BasicLighting : public Pass {

 	public:

 		BasicLighting();

 		void draw(const Camera &, const std::vector<std::shared_ptr<Light>>);

 	private:

 		ShaderStorageBuffer m_lightBuffer;

};

#endif // _BASICLIGHTING_