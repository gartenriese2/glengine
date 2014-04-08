#ifndef _LIGHT_
#define _LIGHT_

#include "glmincludes.hpp"

class Light {

	public:

		Light(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);

		const glm::vec3 & getPos() const { return m_pos; }
		void setPos(const glm::vec3 & pos) { m_pos = pos; }
		const glm::vec3 & getDir() const { return m_dir; }
		void setDir(const glm::vec3 & dir) { m_dir = dir; }
		const glm::vec3 & getColor() const { return m_color; }
		void setColor(const glm::vec3 & color) { m_color = color; }
		void setAmbientTerm(float f) { m_ambientTerm = f; }
		const glm::vec3 getAmbientColor() const { return m_color * m_ambientTerm; }
		float getShininess() const { return m_shiniess; }
		void setShiniess(float f) { m_shiniess = f; }
		float getStrength() const { return m_strength; }
		void setStrength(float f) { m_strength = f; }
		float getAttenuation() const { return m_attenuation; }
		void setAttenuation(float f) { m_attenuation = f; }

		void rotate(float, const glm::vec3 &);

	private:

		glm::vec3 m_pos;
		glm::vec3 m_dir;
		glm::vec3 m_color;
		float m_ambientTerm;
		float m_shiniess;
		float m_strength;
		float m_attenuation;

};

#endif // _LIGHT_