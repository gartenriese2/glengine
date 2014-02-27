#include "objectinterface.hpp"

#include "triangle.hpp"
#include "quadrilateral.hpp"
#include "../debug.hpp"

static ObjectID id = 1;

ObjectID ObjectInterface::nextID() const {
	return ++id;
}

void ObjectInterface::checkID(ObjectID id) const {
	if (m_objects.count(id) == 0) {
		Debug::log("No Object with ID " + std::to_string(id));
		exit(0);
	}
}

ObjectID ObjectInterface::addObject(const std::shared_ptr<Object> ptr) {

	ObjectID id = instance().nextID();
	instance().m_objects.emplace(id, ptr);
	return id;

}

ObjectID ObjectInterface::createTriangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & col) {

	return addObject(std::shared_ptr<Object>(new Triangle(a, b, c, col)));

}

ObjectID ObjectInterface::createTriangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const std::initializer_list<glm::vec3> & colors) {

	return addObject(std::shared_ptr<Object>(new Triangle(a, b, c, colors)));

}

ObjectID ObjectInterface::createQuadrilateral(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & d, const glm::vec3 & col) {

	return addObject(std::shared_ptr<Object>(new Quadrilateral(a, b, c, d, col)));

}

ObjectID ObjectInterface::createQuadrilateral(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	return addObject(std::shared_ptr<Object>(new Quadrilateral(a, b, c, d, colors)));

}

void ObjectInterface::draw(ObjectID id) {

	instance().checkID(id);
	instance().m_objects.at(id)->draw();

}

const glm::mat4 & ObjectInterface::getModelMatrix(ObjectID id) {

	instance().checkID(id);
	return instance().m_objects.at(id)->getModelMatrix();

}

void ObjectInterface::rotate(ObjectID id, float rad, const glm::vec3 & axis) {

	instance().checkID(id);
	instance().m_objects.at(id)->rotate(rad, axis);

}
