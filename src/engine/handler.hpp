#ifndef _HANDLER_
#define _HANDLER_

#include "glmincludes.hpp"
#include "window.hpp"

#include <memory>

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
		void attachTo(const ObjectID &);

	private:

		unsigned long m_id;
		WindowID & m_window;

};

#include <initializer_list>

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

		ObjectID createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		ObjectID createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});
		ObjectID createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		ObjectID createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});
		ObjectID createCopy(const ObjectID &);

	private:

		unsigned long m_id;
		std::shared_ptr<Window> m_window;
		std::vector<ObjectID> m_objects;

};

#endif // _HANDLER_