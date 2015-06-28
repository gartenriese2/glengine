#ifndef _RAYTRACINGDEMO_
#define _RAYTRACINGDEMO_

#include "engine/engine.hpp"

#include <vector>

class RaytracingDemo {

	public:

		RaytracingDemo();
		~RaytracingDemo();

		void run();

	private:

		void initControls();
		void initObjects();
		void initLights();

		Engine m_engine;
		WindowID m_window;
		CameraID m_cam;
		//RenderID m_render;

		std::vector<ObjectID> m_objects;
		std::vector<LightID> m_lights;

};

#endif // _RAYTRACINGDEMO_
