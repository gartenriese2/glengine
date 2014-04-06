#ifndef _SPHERE_
#define _SPHERE_

#include "object.hpp"
#include "../glmincludes.hpp"
#include "../debug.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Sphere : public Object {

	public:
	
		Sphere(Sphere &&) = delete;
		Sphere & operator=(const Sphere &) = delete;
		Sphere & operator=(Sphere &&) = delete;

		virtual ~Sphere() {}

	protected:

		friend ObjectInterface;

		Sphere(const glm::vec3 &, float, unsigned int, unsigned int,
			const glm::vec3 &);
		Sphere(const glm::vec3 &, float, unsigned int, unsigned int,
			const std::initializer_list<glm::vec3> & = {});
		Sphere(const Sphere & t) : Object(t) {}

		std::shared_ptr<Object> getCopy();

		void draw() const;

	private:

		void init(const glm::vec3 &, float, unsigned int, unsigned int,
			const std::vector<GLfloat> &);

		unsigned int m_indices;

};

#endif // _SPHERE_