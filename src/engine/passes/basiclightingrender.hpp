#ifndef _BASICLIGHTINGRENDER_
#define _BASICLIGHTINGRENDER_

#include "render.hpp"
#include "basiclighting.hpp"
#include "../camera.hpp"

#include <set>

class BasicLightingRender : public Render {

	public:

		BasicLightingRender(Camera & cam, Light & light) : m_cam(cam), m_light(light) {}

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_basicLightingPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_basicLightingPass.removeObject(id); }

		void changeBaseSize(unsigned int w, unsigned int h) { m_cam.resize(w, h); }

	private:

		Camera & m_cam;
		Light & m_light;
		BasicLighting m_basicLightingPass;

};

#endif // _BASICLIGHTINGRENDER_