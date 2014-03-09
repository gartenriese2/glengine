#include "objecthandler.hpp"

#include "objects/objectinterface.hpp"

static ObjectID id = 0;

ObjectID ObjectHandler::createObject(Loop & loop, std::function<void(ObjectID)> f) {

	loop.addCommand([=, &loop](){
		f(++id);
		loop.addObjectToRender(id);
	});
	return id;

}
