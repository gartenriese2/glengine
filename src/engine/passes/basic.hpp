#ifndef _BASIC_
#define _BASIC_

#include "../objects/object.hpp"
#include "../gl/program.hpp"

#include <vector>
#include <memory>

class Basic {

 	public:

 		Basic();

 		void draw();

 		void addObjects(const Object &);

 	private:

 		std::vector<const Object *> m_objects;
 		Program m_program;

};

#endif // _BASIC_