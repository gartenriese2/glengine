#ifndef _OBJECT_
#define _OBJECT_

#include "../gl/glincludes.hpp"
#include "../glmincludes.hpp"
#include "../gl/buffer.hpp"
#include "../gl/indexbuffer.hpp"

#include <vector>
#include <initializer_list>

class ObjectInterface;

class Object {

	public:
	
		Object(Object &&) = delete;
		Object & operator=(const Object &) = delete;
		Object & operator=(Object &&) = delete;

		virtual ~Object();

	protected:

		friend ObjectInterface;

		Object();
		Object(const Object &);

		virtual std::shared_ptr<Object> getCopy() = 0;

		virtual void draw() const = 0;
		const glm::mat4 & getModelMatrix() const { return m_modelMatrix; }
		void rotate(float, const glm::vec3 &);
		void rotateAround(float, const glm::vec3 &, const glm::vec3 &);
		void move(float, const glm::vec3 &);
		void moveTo(const glm::vec3 &);
		void scale(const glm::vec3 &);
		void scaleColor(float);
		void setColor(const std::initializer_list<glm::vec3> & = {});
		void setColor(const glm::vec3 &);

		bool hasAttachments() const { return !m_attachedObjects.empty(); }

		GLuint m_vertexArray;
		Buffer m_vertexBuffer;
		Buffer m_colorBuffer;
		Buffer m_normalBuffer;
		IndexBuffer m_indexBuffer;

		glm::mat4 m_modelMatrix;
		glm::mat4 m_scaleMatrix;
		glm::mat4 m_rotationMatrix;
		glm::mat4 m_translationMatrix;

		glm::vec3 m_center;
		glm::vec3 m_actualPosition;
		glm::vec3 m_actualScale;

		std::vector<unsigned long> m_attachedObjects;

		void setCenter(const glm::vec3 &);

		const std::vector<GLfloat> getColorVector(const std::initializer_list<glm::vec3> &, unsigned int) const;
		const std::vector<GLfloat> getColorVector(const glm::vec3 &, unsigned int) const;

};

#endif // _OBJECT_