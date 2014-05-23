#ifndef _RAYTRACINGRENDER_
#define _RAYTRACINGRENDER_

#include "render.hpp"

#include "raycastingpass.hpp"
#include "raycomputingpass.hpp"
#include "texturepass.hpp"
#include "../gl/fbo.hpp"
#include "../gl/texture.hpp"
#include "../camera.hpp"

#include <vector>
#include <memory>

class RaytracingRender : public Render {

	public:

		RaytracingRender(Camera &, std::vector<std::shared_ptr<Light>>);

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_raycastingPass.addObjects(vec);
			m_raycomputingPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_raycastingPass.removeObject(id);
			m_raycomputingPass.removeObject(id); }

		void changeBaseSize(unsigned int w, unsigned int h);

	private:

		Camera & m_cam;
		std::vector<std::shared_ptr<Light>> m_lights;
		FBO m_fbo;
		Texture m_colorTex;
		Texture m_positionTex;
		Texture m_reflectedTex;
		Texture m_depthAttachment;
		Texture m_result;
		RaycastingPass m_raycastingPass;
		RaycomputingPass m_raycomputingPass;
		TexturePass m_texturePass;

};

#endif // _RAYTRACINGRENDER_
