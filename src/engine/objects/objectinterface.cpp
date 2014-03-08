#include "objectinterface.hpp"

#include "triangle.hpp"
#include "quadrilateral.hpp"
#include "../debug.hpp"

#include <algorithm>
#include <mutex>

static std::mutex s_mutex;
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

	std::lock_guard<std::mutex> lock(s_mutex);
	
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

ObjectID ObjectInterface::copyObject(ObjectID id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	return addObject(instance().m_objects.at(id)->getCopy());

}

void ObjectInterface::draw(ObjectID id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	instance().m_objects.at(id)->draw();

}

const glm::mat4 & ObjectInterface::getModelMatrix(ObjectID id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	return instance().m_objects.at(id)->getModelMatrix();

}

void ObjectInterface::rotate(ObjectID id, float rad, const glm::vec3 & axis) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->rotate(rad, axis);

	if (obj->hasAttachments()) {
		for (auto ob : obj->m_attachedObjects) {
			instance().m_objects.at(ob)->rotateAround(rad, axis, obj->m_actualPosition);
		}
	}

}

void ObjectInterface::rotateAround(ObjectID id, float rad, const glm::vec3 & axis, const glm::vec3 & point) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->rotateAround(rad, axis, point);

	if (obj->hasAttachments()) {
		for (auto ob : obj->m_attachedObjects) {
			instance().m_objects.at(ob)->rotateAround(rad, axis, point);
		}
	}

}

void ObjectInterface::rotateAround(ObjectID id, float rad, const glm::vec3 & axis, ObjectID around) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	instance().checkID(around);

	auto & obj = instance().m_objects.at(id);
	auto & aroundObj = instance().m_objects.at(around);
	obj->rotateAround(rad, axis, aroundObj->m_actualPosition);

	if (obj->hasAttachments()) {
		for (auto ob : obj->m_attachedObjects) {
			instance().m_objects.at(ob)->rotateAround(rad, axis, aroundObj->m_actualPosition);
		}
	}

}

void ObjectInterface::move(ObjectID id, float val, const glm::vec3 & dir) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->move(val, dir);

	if (obj->hasAttachments()) {
		for (auto o : obj->m_attachedObjects) {
			instance().m_objects.at(o)->move(val, dir);
		}
	}

}

void ObjectInterface::moveTo(ObjectID id, const glm::vec3 & to) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	auto old = obj->m_actualPosition;
	obj->moveTo(to);

	if (obj->hasAttachments()) {
		auto diff = obj->m_actualPosition - old;
		for (auto ob : obj->m_attachedObjects) {
			auto & o = instance().m_objects.at(ob);
			o->moveTo(o->m_actualPosition + diff);
		}
	}
	

}

void ObjectInterface::scale(ObjectID id, const glm::vec3 & val) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->scale(val);

	if (obj->hasAttachments()) {
		
		for (auto ob : obj->m_attachedObjects) {
			auto & o = instance().m_objects.at(ob);

			o->scale(val);
			o->moveTo(obj->m_actualPosition + val * (o->m_actualPosition - obj->m_actualPosition));
			
		}
	}

}

void ObjectInterface::attach(ObjectID id, ObjectID attachment) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	instance().checkID(attachment);
	auto & v = instance().m_objects.at(id)->m_attachedObjects;
	auto it = std::find(v.cbegin(), v.cend(), attachment);
	if (it == v.cend()) {
		v.emplace_back(attachment);
	}

}
