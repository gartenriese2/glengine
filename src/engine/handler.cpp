#include "handler.hpp"

#include "debug.hpp"

#include "objects/objectinterface.hpp"
#include "gl/loop.hpp"
#include "passes/basicrender.hpp"
#include "passes/normalrender.hpp"
#include "passes/basiclightingrender.hpp"

/*
*
*	ObjectID
*
*/

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

void ObjectID::scaleColor(float scale) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::scaleColor(m_id, scale);
	});

}

void ObjectID::setColor(const std::initializer_list<glm::vec3> & colors) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::setColor(m_id, colors);
	});

}

void ObjectID::setColor(const glm::vec3 & color) {

	m_window.getLoop().addCommand([=](){
		ObjectInterface::setColor(m_id, color);
	});

}

void ObjectID::attachTo(const ObjectID & other) {

	if (m_window.hasObject(other)) {
		m_window.getLoop().addCommand([=](){
			ObjectInterface::attach(other(), m_id);
		});
	}

}

/*
*
*	WindowID
*
*/

WindowID::WindowID(std::shared_ptr<Window> ptr)
  : m_window(ptr)
{

	static unsigned long windowID = 0;
	m_id = ++windowID;

}

const ObjectID & WindowID::createCopy(const ObjectID & id) {

	// Only copy if it is an Object in the same window
	if (hasObject(id)) {
		m_objects.emplace_back(*this);
		unsigned long origid = id();
		unsigned long copyid = m_objects.back()();
		Loop & loop = m_window->getLoop();

		loop.addCommand([=, &loop](){
			ObjectInterface::copyObject(origid, copyid);
		});

		return m_objects.back();
	}
	return id;

}

const ObjectID & WindowID::createTriangle(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & color) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createTriangle(id, a, b, c, color);
	});

	return m_objects.back();
	
}

const ObjectID & WindowID::createTriangle(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const std::initializer_list<glm::vec3> & colors) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createTriangle(id, a, b, c, colors);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createQuadrilateral(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const glm::vec3 & color) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createQuadrilateral(id, a, b, c, d, color);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createQuadrilateral(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createQuadrilateral(id, a, b, c, d, colors);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createCircle(const glm::vec3 & center, const glm::vec3 & axis, float radius,
	unsigned int edges, const glm::vec3 & color) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createCircle(id, center, axis, radius, edges, color);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createCircle(const glm::vec3 & center, const glm::vec3 & axis, float radius,
	unsigned int edges,	const std::initializer_list<glm::vec3> & colors) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createCircle(id, center, axis, radius, edges, colors);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createCuboid(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const glm::vec3 & color) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createCuboid(id, a, b, c, d, color);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createCuboid(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createCuboid(id, a, b, c, d, colors);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createSphere(const glm::vec3 & center, float radius, unsigned int rings,
	unsigned int sectors, const glm::vec3 & color) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createSphere(id, center, radius, rings, sectors, color);
	});

	return m_objects.back();

}

const ObjectID & WindowID::createSphere(const glm::vec3 & center, float radius, unsigned int rings,
	unsigned int sectors,	const std::initializer_list<glm::vec3> & colors) {

	m_objects.emplace_back(*this);
	unsigned long id = m_objects.back()();
	Loop & loop = m_window->getLoop();

	loop.addCommand([=, &loop](){
		ObjectInterface::createSphere(id, center, radius, rings, sectors, colors);
	});

	return m_objects.back();

}

const RenderID & WindowID::createBasicRendering(CameraID & camID) {

	m_renders.emplace_back(*this);
	unsigned long id = m_renders.back()();
	Loop & loop = m_window->getLoop();
	Camera & cam = camID.getCam();

	loop.addCommand([=, &loop, &cam](){
		std::shared_ptr<Render> r(new BasicRender(cam));
		loop.addRendering(id, r);
	});

	return m_renders.back();

}

const RenderID & WindowID::createNormalRendering(CameraID & camID) {

	m_renders.emplace_back(*this);
	unsigned long id = m_renders.back()();
	Loop & loop = m_window->getLoop();
	Camera & cam = camID.getCam();

	loop.addCommand([=, &loop, &cam](){
		std::shared_ptr<Render> r(new NormalRender(cam));
		loop.addRendering(id, r);
	});

	return m_renders.back();

}

const RenderID & WindowID::createBasicLightingRendering(CameraID & camID, const std::vector<LightID> lightIDs) {

	m_renders.emplace_back(*this);
	unsigned long id = m_renders.back()();
	Loop & loop = m_window->getLoop();
	Camera & cam = camID.getCam();
	std::vector<std::shared_ptr<Light>> lights;
	for (const auto & ids : lightIDs) {
		lights.emplace_back(ids.getLight());
	}

	loop.addCommand([=, &loop, &cam](){
		std::shared_ptr<Render> r(new BasicLightingRender(cam, lights));
		loop.addRendering(id, r);
	});

	return m_renders.back();

}

const CameraID & WindowID::createCamera(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & up) {

	m_cameras.emplace_back(Camera(pos, dir, up, 45.f, m_window->getWidth(), m_window->getHeight(), 0.01f, 1000.f));

	return m_cameras.back();

}

const LightID & WindowID::createLight(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & color) {

	m_lights.emplace_back(std::shared_ptr<Light>(new Light(pos, dir, color)));

	return m_lights.back();

}

/*
*
*	RenderID
*
*/

RenderID::RenderID(WindowID & win)
  : m_window(win)
{

	static unsigned long renderID = 0;
	m_id = ++renderID;

}

void RenderID::set() {

	Loop & loop = m_window.getLoop();

	loop.addCommand([=, &loop](){
		loop.setRendering(loop.getRendering(m_id));
	});

}

void RenderID::addObjects(const std::set<ObjectID> & set) {

	Loop & loop = m_window.getLoop();

	std::set<unsigned long> IDs;
	for (const ObjectID & o : set) {
		IDs.emplace(o());
	}

	loop.addCommand([=, &loop](){
		loop.addObjectsToRender(m_id, IDs);
	});

}

void RenderID::removeObject(const ObjectID & id) {

	Loop & loop = m_window.getLoop();

	unsigned long ID = id();
	
	loop.addCommand([=, &loop](){
		loop.removeObjectFromRender(m_id, ID);
	});

}

/*
*
*	CameraID
*
*/

CameraID::CameraID(const Camera & cam)
  : m_cam(cam)
{

	static unsigned long cameraID = 0;
	m_id = ++cameraID;

}

/*
*
*	LightID
*
*/

LightID::LightID(const std::shared_ptr<Light> light)
  : m_light(light)
{

	static unsigned long lightID = 0;
	m_id = ++lightID;

}
