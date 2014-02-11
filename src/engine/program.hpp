#ifndef _PROGRAM_
#define _PROGRAM_

#include "shader.hpp"

class Program {

 	public:

 		Program();
 		~Program();

 		void attachShader(const Shader &);
 		void use();

 	private:

 		GLuint m_program;
 		bool m_linked;

};

#endif // _PROGRAM_