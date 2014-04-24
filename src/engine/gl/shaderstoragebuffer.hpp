#ifndef _SHADERSTORAGEBUFFER_
#define _SHADERSTORAGEBUFFER_

#include "glincludes.hpp"

#include <vector>

class ShaderStorageBuffer {

	public:

		ShaderStorageBuffer();
		~ShaderStorageBuffer();

		void bindTo(unsigned int);

		template <class T>
		void addData(std::vector<T> & data, unsigned int count) {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_name);
			glBufferData(GL_SHADER_STORAGE_BUFFER, count * sizeof(T), NULL, GL_STATIC_DRAW);
			GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
			T * ld = (T *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, count * sizeof(T), bufMask);
			for (unsigned int i = 0; i < count; ++i) {
				ld[i] = data[i];
			}
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		}

	private:

		GLuint m_name;

};

#endif // _SHADERSTORAGEBUFFER_