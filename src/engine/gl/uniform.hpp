#ifndef _UNIFORM_
#define _UNIFORM_

#include "glincludes.hpp"
#include "../glmincludes.hpp"

class Uniform {

 	public:

 		void operator=(const float val) {
		    if (m_loc != -1) {
			    glUniform1f(m_loc, val);
			}
		}

		void operator=(const glm::mat4& mat) {
		    if (m_loc != -1) {
			    glUniformMatrix4fv(m_loc, 1, GL_FALSE, glm::value_ptr(mat));
			}
		}

 	private:

 		friend class Program;
    	explicit Uniform(GLuint loc) : m_loc{loc} {}

    	GLuint m_loc;

};

#endif // _UNIFORM_