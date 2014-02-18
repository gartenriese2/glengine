#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "primitive.hpp"
#include "../glmincludes.hpp"

#include <initializer_list>
#include <vector>

class Triangle : public Primitive {

	public:

		Triangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		Triangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});

		void draw() const;

	private:

		void init(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const std::vector<GLfloat> &);

};

#endif // _TRIANGLE_