#ifndef _TEXTUREPASS_
#define _TEXTUREPASS_

#include "pass.hpp"

#include "../gl/vbo.hpp"
#include "../gl/ibo.hpp"
#include "../gl/vao.hpp"
#include "../gl/texture.hpp"

class TexturePass : public Pass {

 	public:

 		TexturePass(Texture &);
 		~TexturePass() {}

 		void draw();

 	private:

 		gl::VAO m_vertexArray;
 		gl::VBO m_vertexBuffer;
 		gl::IBO m_indexBuffer;
 		Texture & m_tex;

};

#endif // _TEXTUREPASS_