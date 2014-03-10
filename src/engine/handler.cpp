#include "handler.hpp"

#include "objects/objectinterface.hpp"
#include "gl/loop.hpp"
#include "debug.hpp"

ObjectID::ObjectID(WindowID & win)
  : m_window(win)
{

	static unsigned long objectID = 0;
	m_id = ++objectID;

}

void ObjectID::rotate(float angle, const glm::vec3 & axis) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::rotate(m_id, angle, axis);
	});

}

void ObjectID::rotateAround(float angle, const glm::vec3 & axis, const glm::vec3 & point) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::rotateAround(m_id, angle, axis, point);
	});

}

void ObjectID::rotateAround(float angle, const glm::vec3 & axis, const ObjectID & obj) {

	if (m_window.hasObject(obj)) {
		m_window.getLoop().addCommand([=](){
			ObjectInterface::rotateAround(m_id, angle, axis, obj());
		});
	}

}

void ObjectID::move(float distance, const glm::vec3 & direction) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::move(m_id, distance, direction);
	});

}

void ObjectID::moveTo(const glm::vec3 & point) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::moveTo(m_id, point);
	});

}

void ObjectID::scale(const glm::vec3 & value) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::scale(m_id, value);
	});

}

void ObjectID::attachTo(const ObjectID & other) {

	if (m_window.hasObject(other)) {
		m_window.getLoop().addCommand([=](){
			ObjectInterface::attach(other(), m_id);
		});
	}

}

WindowID::WindowID(std::shared_ptr<Window> ptr)
  : m_window(ptr)
{

	static unsigned long windowID = 0;
	m_id = ++windowID;

}

ObjectID WindowID::createCopy(const ObjectID & id) {

	if (hasObject(id)) {
		m_objects.emplace_back(*this);
		Loop & loop = m_window->getLoop();

		loop.addCommand([&](){
			ObjectInterface::copyObject(id(), m_objects.back()());
			loop.addObjectToRender(m_objects.back()());
		});

		return m_objects.back();
	}
	return id;

}

ObjectID WindowID::createTriangle(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & color) {

	m_objects.emplace_back(*this);
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createTriangle(m_objects.back()(), a, b, c, color);
		loop.addObjectToRender(m_objects.back()());
	});

	return m_objects.back();
	
}

ObjectID WindowID::createTriangle(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const std::initializer_list<glm::vec3> & colors) {

	m_objects.emplace_back(*this);
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createTriangle(m_objects.back()(), a, b, c, colors);
		loop.addObjectToRender(m_objects.back()());
	});

	return m_objects.back();

}

ObjectID WindowID::createQuadrilateral(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const glm::vec3 & color) {

	m_objects.emplace_back(*this);
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createQuadrilateral(m_objects.back()(), a, b, c, d, color);
		loop.addObjectToRender(m_objects.back()());
	});

	return m_objects.back();

}

ObjectID WindowID::createQuadrilateral(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	m_objects.emplace_back(*this);
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createQuadrilateral(m_objects.back()(), a, b, c, d, colors);
		loop.addObjectToRender(m_objects.back()());
	});

	return m_objects.back();

}
