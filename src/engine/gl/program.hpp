#ifndef _PROGRAM_
#define _PROGRAM_

#include "shader.hpp"
#include "../glmincludes.hpp"
#include "uniform.hpp"

#include <map>

class Program {

 	public:

		Program();
		~Program();

 		Uniform operator[](const std::string & name) const;

		void attachShader(const Shader &) const;
		void use();

 	private:

		void link();

		GLuint m_program;
		bool m_linked;

		std::map<const std::string, GLuint> m_uniforms;

};

#endif // _PROGRAM_