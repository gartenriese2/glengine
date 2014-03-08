#ifndef _BASICRENDER_
#define _BASICRENDER_

#include "render.hpp"
#include "basic.hpp"
#include "../camera.hpp"

class BasicRender : public Render {

	public:

		BasicRender(const Camera & cam) : m_cam(cam) {}

		void draw();

		void addObjects(ObjectID id) { m_basicPass.addObjects(id); }
		void addObjects(std::vector<ObjectID> vec) { m_basicPass.addObjects(vec); }

	private:

		const Camera & m_cam;
		Basic m_basicPass;

};

#endif // _BASICRENDER_