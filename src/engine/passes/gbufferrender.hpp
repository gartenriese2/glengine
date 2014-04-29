#ifndef _GBUFFERRENDER_
#define _GBUFFERRENDER_

#include "render.hpp"

#include "gbufferpass.hpp"
#include "../gl/fbo.hpp"
#include "../gl/texture.hpp"
#include "../camera.hpp"

class GBufferRender : public Render {

	public:

		GBufferRender(Camera & cam);

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_gbufferPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_gbufferPass.removeObject(id); }

		void changeBaseSize(unsigned int w, unsigned int h);

	private:

		Camera & m_cam;
		FBO m_fbo;
		Texture m_colorTex;
		Texture m_depthTex;
		Texture m_normalTex;
		Texture m_positionTex;
		Texture m_depthAttachment;
		GBufferPass m_gbufferPass;

};

#endif // _GBUFFERRENDER_
