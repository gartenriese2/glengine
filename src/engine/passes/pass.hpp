#ifndef _PASS_
#define _PASS_

#include "../objects/objectinterface.hpp"
#include "../gl/program.hpp"
#include "../camera.hpp"

#include <vector>

class Pass {
	
	public:
	
		Pass();
		Pass(const Pass &) = delete;
		Pass(Pass &&) = delete;
		Pass & operator=(const Pass &) = delete;
		Pass & operator=(Pass &&) = delete;

		virtual void draw(const Camera &) = 0;

		void addObjects(ObjectID);

	protected:

		Program m_program;
		std::vector<ObjectID> m_objects;
};

#endif // _PASS_