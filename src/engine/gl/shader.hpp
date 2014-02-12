#ifndef _SHADER_
#define _SHADER_

#include "glincludes.hpp"

#include <string>

class Shader {

  	public:

  		Shader(const std::string &);
  		~Shader();

  		GLuint operator()() const { return m_shader; }

  	private:

  		GLuint m_shader;

  		const std::string getShaderCode(const std::string &);

};

#endif // _SHADER_