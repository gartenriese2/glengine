#ifndef _CUBOID_
#define _CUBOID_

#include "object.hpp"
#include "../glmincludes.hpp"
#include "../debug.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Cuboid : public Object {

	public:
	
		Cuboid(Cuboid &&) = delete;
		Cuboid & operator=(const Cuboid &) = delete;
		Cuboid & operator=(Cuboid &&) = delete;

		virtual ~Cuboid() {}

	protected:

		friend ObjectInterface;

		Cuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, 
			const glm::vec3 &);
		Cuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});
		Cuboid(const Cuboid & t) : Object(t) {}

		std::shared_ptr<Object> getCopy();

		void draw() const;

	private:

		void init(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::vector<GLfloat> &);

		unsigned int m_indices;

};

#endif // _CUBOID_