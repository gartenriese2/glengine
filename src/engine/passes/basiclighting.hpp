#ifndef _BASICLIGHTING_
#define _BASICLIGHTING_

#include "pass.hpp"

class BasicLighting : public Pass {

 	public:

 		BasicLighting();

 		void draw(const Camera &, const Light &);

 	private:

};

#endif // _BASICLIGHTING_