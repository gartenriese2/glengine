#ifndef _BASICRENDER_
#define _BASICRENDER_

#include "render.hpp"
#include "basic.hpp"
#include "../camera.hpp"

#include <set>

class BasicRender : public Render {

	public:

		BasicRender(Camera & cam) : m_cam(cam) {}

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_basicPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_basicPass.removeObject(id); }

	private:

		Camera & m_cam;
		Basic m_basicPass;

};

#endif // _BASICRENDER_