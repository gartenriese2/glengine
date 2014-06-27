#ifndef _SPLINE_
#define _SPLINE_

#include "object.hpp"
#include "../glmincludes.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Spline : public Object {

	public:
	
		Spline(Spline &&) = delete;
		Spline & operator=(const Spline &) = delete;
		Spline & operator=(Spline &&) = delete;

		virtual ~Spline() {}

	protected:

		friend ObjectInterface;

		Spline(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, float, float, unsigned int, float, const glm::vec3 &);
		Spline(const std::vector<glm::vec3> &, const glm::vec3 &, float, const glm::vec3 &);
		Spline(const Spline & t) : Object(t) {}

		std::shared_ptr<Object> getCopy();

		void draw() const;

		unsigned int getType() const { return SPLINE; }

	private:

		void init(const std::vector<glm::vec3> &, const glm::vec3 &, const glm::vec3 &);

		unsigned int m_indices;

};

#endif // _SPLINE_