#ifndef _HANDLER_
#define _HANDLER_

#include "glmincludes.hpp"
#include "window.hpp"

#include <memory>
#include <initializer_list>

class WindowID;

class ObjectID {

	public:

		ObjectID(WindowID &);

		bool operator==(const ObjectID & other) const { return this->m_id == other.m_id; }
		bool operator<(const ObjectID & other) const { return this->m_id < other.m_id; }
		unsigned long operator()() const { return m_id; }

		void rotate(float, const glm::vec3 &);
		void rotateAround(float, const glm::vec3 &, const glm::vec3 &);
		void rotateAround(float, const glm::vec3 &, const ObjectID &);
		void move(float, const glm::vec3 &);
		void moveTo(const glm::vec3 &);
		void scale(const glm::vec3 &);
		void scaleColor(float);
		void setColor(const std::initializer_list<glm::vec3> & = {});
		void setColor(const glm::vec3 &);
		void attachTo(const ObjectID &);

	private:

		unsigned long m_id;
		WindowID & m_window;

};

class CameraID;
class RenderID;
class LightID;

class WindowID {

	public:

		WindowID(std::shared_ptr<Window>);
		WindowID(const WindowID & other) { m_id = other.m_id; }
		WindowID(WindowID && other) { m_id = other.m_id; }
		WindowID & operator=(const WindowID &) = delete;
		WindowID & operator=(WindowID &&) = delete;

		bool operator==(const WindowID & other) const { return this->m_id == other.m_id; }
		bool operator<(const WindowID & other) const { return this->m_id < other.m_id; }
		unsigned long operator()() const { return m_id; }

		Loop & getLoop() { return m_window->getLoop(); }
		bool hasObject(ObjectID id) const { return std::find(m_objects.cbegin(), m_objects.cend(), id) != m_objects.cend(); }

		void close() { glfwSetWindowShouldClose(m_window->getGLFWWindow(), GL_TRUE); }

		const ObjectID & createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		const ObjectID & createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});

		const ObjectID & createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		const ObjectID & createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});

		const ObjectID & createCircle(const glm::vec3 &, const glm::vec3 &, float, unsigned int,
			const glm::vec3 &);
		const ObjectID & createCircle(const glm::vec3 &, const glm::vec3 &, float, unsigned int,
			const std::initializer_list<glm::vec3> & = {});

		const ObjectID & createCuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		const ObjectID & createCuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});

		const ObjectID & createCopy(const ObjectID &);

		const RenderID & createBasicRendering(CameraID &);
		const RenderID & createNormalRendering(CameraID &);

		const CameraID & createCamera(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);

		const LightID & createLight(const glm::vec3 &, const glm::vec3 & = {1.f, 1.f, 1.f});

		void addKeyEvent(int key, std::function<void()> f) { getLoop().addKeyEvent(key, f); }
		void removeKeyEvent(int key) { getLoop().removeKeyEvent(key); }
		bool isKeyPressed(int key) { return GLFW_PRESS == glfwGetKey(m_window->getGLFWWindow(), key); }

		void addMouseClickEvent(int key, std::function<void()> f) { getLoop().addMouseClickEvent(key, f); }
		void removeMouseClickEvent(int key) { getLoop().removeMouseClickEvent(key); }
		void setMouseMoveEvent(std::function<void(double, double)> f) { getLoop().setMouseMoveEvent(f); }
		void setScrollEvent(std::function<void(double, double)> f) { getLoop().setScrollEvent(f); }
		bool isMouseButtonPressed(int key) { return GLFW_PRESS == glfwGetMouseButton(m_window->getGLFWWindow(), key); }
		
		bool isLeftMouseButtonPressed() { return isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT); }
		bool isRightMouseButtonPressed() { return isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT); }
		bool isEscapePressed() { return isKeyPressed(GLFW_KEY_ESCAPE); }
		bool isShiftPressed() { return isKeyPressed(GLFW_KEY_LEFT_SHIFT) || isKeyPressed(GLFW_KEY_RIGHT_SHIFT); }

	private:

		unsigned long m_id;
		std::shared_ptr<Window> m_window;
		std::vector<ObjectID> m_objects;
		std::vector<RenderID> m_renders;
		std::vector<CameraID> m_cameras;
		std::vector<LightID> m_lights;

};

class RenderID {

	public:

		RenderID(WindowID &);

		bool operator==(const RenderID & other) const { return this->m_id == other.m_id; }
		bool operator<(const RenderID & other) const { return this->m_id < other.m_id; }
		unsigned long operator()() const { return m_id; }

		void set();
		void addObjects(const std::set<ObjectID> &);
		void removeObject(const ObjectID &);

	private:

		unsigned long m_id;
		WindowID & m_window;

};

#include "camera.hpp"

class CameraID {

	public:

		CameraID(const Camera &);

		unsigned long operator()() const { return m_id; }

		Camera & getCam() { return m_cam; }

		const glm::vec3 & getPos() const { return m_cam.getPos(); }
		const glm::vec3 & getDir() const { return m_cam.getDir(); }
		const glm::vec3 & getUp() const { return m_cam.getUp(); }

		void reset() { m_cam.reset(); }
		void move(const glm::vec3 & change) { m_cam.move(change); }
		void moveTo(const glm::vec3 & to) { m_cam.moveTo(to); }
		void rotate(float radians, const glm::vec3 & axis) { m_cam.rotate(radians, axis); }
		void rotateAround(float radians, const glm::vec3 & axis, const glm::vec3 & point)
			{ m_cam.rotateAround(radians, axis, point); }
		void yaw(float radians) { m_cam.rotate(radians, getUp()); }
		void pitch(float radians) { m_cam.rotate(radians, glm::cross(getUp(), getDir())); }

	private:

		unsigned long m_id;
		Camera m_cam;

};

#include "light.hpp"

class LightID {

	public:

		LightID(const Light &);

		unsigned long operator()() const { return m_id; }

		Light & getLight() { return m_light; }

		const glm::vec3 & getDir() const { return m_light.getDir(); }
		void setDir(const glm::vec3 & dir) { m_light.setDir(dir); }
		const glm::vec3 & getColor() const { return m_light.getColor(); }
		void setColor(const glm::vec3 & color) { m_light.setColor(color); }

		void rotate(float radians, const glm::vec3 & axis) { m_light.rotate(radians, axis); }

	private:

		unsigned long m_id;
		Light m_light;

};

#endif // _HANDLER_