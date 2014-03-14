#ifndef _CIRCLE_
#define _CIRCLE_

#include "object.hpp"
#include "../glmincludes.hpp"
#include "../debug.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Circle : public Object {

	public:
	
		Circle(Circle &&) = delete;
		Circle & operator=(const Circle &) = delete;
		Circle & operator=(Circle &&) = delete;

		virtual ~Circle() {}

	protected:

		friend ObjectInterface;

		Circle(const glm::vec3 &, const glm::vec3 &, float, unsigned int, const glm::vec3 &);
		Circle(const glm::vec3 &, const glm::vec3 &, float, unsigned int, const std::initializer_list<glm::vec3> & = {});
		Circle(const Circle & t) : Object(t) {}

		std::shared_ptr<Object> getCopy();

		void draw() const;

	private:

		void init(const glm::vec3 &, const glm::vec3 &, float, unsigned int, const std::vector<GLfloat> &);

		unsigned int m_indices;

};

#endif // _CIRCLE_