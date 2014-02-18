#ifndef _QUADRILATERAL_
#define _QUADRILATERAL_

#include "primitive.hpp"
#include "../glmincludes.hpp"

#include <initializer_list>
#include <vector>

class Quadrilateral : public Primitive {

	public:

		Quadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		Quadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});

		void draw() const;

	private:

		void init(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::vector<GLfloat> &);

};

#endif // _QUADRILATERAL_