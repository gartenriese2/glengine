#ifndef _CONE_
#define _CONE_

#include "object.hpp"
#include "../glmincludes.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Cone : public Object {

	public:
	
		Cone(Cone &&) = delete;
		Cone & operator=(const Cone &) = delete;
		Cone & operator=(Cone &&) = delete;

		virtual ~Cone() {}

	protected:

		friend ObjectInterface;

		Cone(const glm::vec3 &, const glm::vec3 &, float, float, float, unsigned int, const glm::vec3 &);
		Cone(const glm::vec3 &, const glm::vec3 &, float, float, float, unsigned int, const std::initializer_list<glm::vec3> & = {});
		Cone(const Cone & t) : Object(t) {}

		std::shared_ptr<Object> getCopy();

		void draw() const;

	private:

		void init(const glm::vec3 &, const glm::vec3 &, float, float, float, unsigned int, const std::vector<GLfloat> &);

		unsigned int m_indices;

};

#endif // _CONE_