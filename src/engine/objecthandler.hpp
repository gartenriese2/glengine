#ifndef _OBJECTHANDLER_
#define _OBJECTHANDLER_

#include "gl/loop.hpp"
#include "glmincludes.hpp"

#include <initializer_list>

using ObjectID = unsigned long;

class ObjectHandler {

	public:

		ObjectHandler() {}

		ObjectID createObject(Loop &, std::function<void(ObjectID)>);

};

#endif // _OBJECTHANDLER_