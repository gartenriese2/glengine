#ifndef _UNIFORM_
#define _UNIFORM_

#include "glincludes.hpp"
#include "../glmincludes.hpp"
#include "../debug.hpp"

class Uniform {

 	public:

 		void operator=(const int val) {
		    if (m_loc != -1) {
			    glUniform1i(m_loc, val);
			}
		}

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

		void operator=(const glm::vec3 & vec) {
		    if (m_loc != -1) {
			    glUniform3fv(m_loc, 1, glm::value_ptr(vec));
			}
		}

 	private:

 		friend class Program;
    	explicit Uniform(GLuint loc) : m_loc{loc} {}

    	GLuint m_loc;

};

#endif // _UNIFORM_