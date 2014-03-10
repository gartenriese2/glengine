#ifndef _OBJECTINTERFACE_
#define _OBJECTINTERFACE_

#include "../glmincludes.hpp"
#include "object.hpp"

#include <initializer_list>
#include <map>
#include <memory>

class ObjectInterface {

	public:

		// TRIANGLE
		static void createTriangle(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		static void createTriangle(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});

		// QUADRILATERAL
		static void createQuadrilateral(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		static void createQuadrilateral(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &,	const std::initializer_list<glm::vec3> & = {});

		static void copyObject(unsigned long, unsigned long);


		static void draw(unsigned long);
		static const glm::mat4 & getModelMatrix(unsigned long);
		static void rotate(unsigned long, float, const glm::vec3 &);
		static void rotateAround(unsigned long, float, const glm::vec3 &, const glm::vec3 &);
		static void rotateAround(unsigned long, float, const glm::vec3 &, unsigned long);
		static void move(unsigned long, float, const glm::vec3 &);
		static void moveTo(unsigned long, const glm::vec3 &);
		static void scale(unsigned long, const glm::vec3 &);

		static void attach(unsigned long, unsigned long);

	private:

		static ObjectInterface & instance() { static ObjectInterface obj; return obj; }
		static void addObject(unsigned long, const std::shared_ptr<Object>);

		unsigned long nextID() const;
		void checkID(unsigned long) const;

		std::map<unsigned long, std::shared_ptr<Object>> m_objects;

};

#endif // _OBJECTINTERFACE_