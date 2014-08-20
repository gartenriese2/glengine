#include "texturepass.hpp"

#include "../camera.hpp"
#include "../objects/objectinterface.hpp"
#include "../debug.hpp"

TexturePass::TexturePass(Texture & tex)
  : m_vertexBuffer{3},
  	m_tex{tex}
{

	Shader vert {k_dir + "ssq.vert"};
	Shader frag {k_dir + "texture.frag"};
	m_program.attachShader(vert);
	m_program.attachShader(frag);

	m_vertexBuffer.insertData({
		-1.f, -1.f, 0.f,
	   	1.f, -1.f, 0.f,
	   	1.f, 1.f, 0.f,
	   	-1.f, 1.f, 0.f
	});
	m_vertexArray.attachVBO(m_vertexBuffer, 0, 0);
	
	m_indexBuffer.insertData({
		0, 1, 2,
		2, 3, 0
	});
	m_vertexArray.attachIBO(m_indexBuffer);

}

void TexturePass::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	m_program["tex"] = {0};
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);

}
