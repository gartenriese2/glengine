#ifndef _OBJECTINTERFACE_
#define _OBJECTINTERFACE_

#include "../glmincludes.hpp"
#include "object.hpp"

#include <initializer_list>
#include <map>
#include <memory>

using ObjectID = unsigned long;

class ObjectInterface {

	public:

		// TRIANGLE
		static ObjectID createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		static ObjectID createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});

		// QUADRILATERAL
		static ObjectID createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		static ObjectID createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &,	const std::initializer_list<glm::vec3> & = {});


		static void draw(ObjectID);
		static const glm::mat4 & getModelMatrix(ObjectID);
		static void rotate(ObjectID, float, const glm::vec3 &);
		static void rotateAround(ObjectID, float, const glm::vec3 &, const glm::vec3 &);
		static void rotateAround(ObjectID, float, const glm::vec3 &, ObjectID);
		static void move(ObjectID, float, const glm::vec3 &);
		static void moveTo(ObjectID, const glm::vec3 &);

		static void attach(ObjectID, ObjectID);

	private:

		static ObjectInterface & instance() { static ObjectInterface obj; return obj; }
		static ObjectID addObject(const std::shared_ptr<Object>);

		ObjectID nextID() const;
		void checkID(ObjectID) const;

		std::map<ObjectID, std::shared_ptr<Object>> m_objects;

};

#endif // _OBJECTINTERFACE_