#ifndef _QUADRILATERAL_
#define _QUADRILATERAL_

#include "primitive.hpp"
#include "../glmincludes.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Quadrilateral : public Primitive {

	public:
	
		Quadrilateral(Quadrilateral &&) = delete;
		Quadrilateral & operator=(const Quadrilateral &) = delete;
		Quadrilateral & operator=(Quadrilateral &&) = delete;

		virtual ~Quadrilateral() {}

	protected:

		friend ObjectInterface;

		Quadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		Quadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});
		Quadrilateral(const Quadrilateral & q) : Primitive(q) {}

		std::shared_ptr<Object> getCopy();

		void draw() const;

	private:

		void init(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::vector<GLfloat> &);

};

#endif // _QUADRILATERAL_