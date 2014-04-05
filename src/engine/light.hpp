#ifndef _LIGHT_
#define _LIGHT_

#include "glmincludes.hpp"

class Light {

	public:

		Light(const glm::vec3 &, const glm::vec3 &);

		const glm::vec3 & getDir() const { return m_dir; }
		void setDir(const glm::vec3 & dir) { m_dir = dir; }
		const glm::vec3 & getColor() const { return m_color; }
		void setColor(const glm::vec3 & color) { m_color = color; }

		void rotate(float, const glm::vec3 &);

	private:

		glm::vec3 m_dir;
		glm::vec3 m_color;

};

#endif // _LIGHT_