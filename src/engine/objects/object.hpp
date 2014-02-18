#ifndef _OBJECT_
#define _OBJECT_

#include "../gl/glincludes.hpp"
#include "../glmincludes.hpp"

#include <vector>
#include <initializer_list>

class Object {

	public:
	
		Object();
		Object(const Object &) = delete;
		Object(Object &&) = delete;
		Object & operator=(const Object &) = delete;
		Object & operator=(Object &&) = delete;

		virtual ~Object();

		virtual void draw() const = 0;

		const glm::mat4 & getModelMatrix() const { return m_modelMatrix; }

		void rotate(float radians, const glm::vec3 &);

	protected:

		GLuint m_vertexBuffer;
		GLuint m_colorBuffer;
		GLuint m_indexBuffer;
		GLuint m_vertexArray;

		glm::mat4 m_modelMatrix;

		glm::vec3 m_center;

		const std::vector<GLfloat> getColorVector(const std::initializer_list<glm::vec3> &, unsigned int) const;
		const std::vector<GLfloat> getColorVector(const glm::vec3 &, unsigned int) const;

		void bindVertices(const std::vector<GLfloat> & v) { bindToIndex(v, m_vertexBuffer, 0); }
		void bindColors(const std::vector<GLfloat> & v) { bindToIndex(v, m_colorBuffer, 1); }
		void bindIndices(const std::vector<GLushort> & v);

	private:

		template <class T>
		void bufferData(GLenum target, const std::vector<T> & v, GLenum usage) {
    		glBufferData(target, v.size() * sizeof(T), &v[0], usage);
		}

		template <class T>
		void bindToIndex(const std::vector<T> & v, const GLuint id, unsigned int index) {
			glBindBuffer(GL_ARRAY_BUFFER, id);
			bufferData(GL_ARRAY_BUFFER, v, GL_STATIC_DRAW);
			glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
			glEnableVertexAttribArray(index);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

};

#endif // _OBJECT_