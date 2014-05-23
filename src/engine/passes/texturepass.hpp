#ifndef _TEXTUREPASS_
#define _TEXTUREPASS_

#include "pass.hpp"

#include "../gl/buffer.hpp"
#include "../gl/indexbuffer.hpp"
#include "../gl/texture.hpp"

class TexturePass : public Pass {

 	public:

 		TexturePass(Texture &);
 		~TexturePass();

 		void draw();

 	private:

 		GLuint m_vertexArray;
 		Buffer m_vertexBuffer;
 		IndexBuffer m_indexBuffer;
 		Texture & m_tex;

};

#endif // _TEXTUREPASS_