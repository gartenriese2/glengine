#ifndef _PROGRAM_
#define _PROGRAM_

#include "shader.hpp"
#include "../glmincludes.hpp"

#include <map>

class Program {

 	public:

 		Program();
 		~Program();

 		// const int & operator[](const std::string & idx) const; // TODO!
 		void transmit(const std::string &, const glm::mat4 &);

 		void attachShader(const Shader &);
 		void use();

 	private:

 		GLuint m_program;
 		bool m_linked;

 		std::map<const std::string, GLuint> m_handles;

};

#endif // _PROGRAM_