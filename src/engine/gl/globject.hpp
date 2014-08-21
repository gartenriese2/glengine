#ifndef _GL_OBJECT_
#define _GL_OBJECT_

#include "glincludes.hpp"

#include <string>

namespace gl {

class Object {

	public:

		virtual ~Object() {}

		operator GLuint() const { return m_name; }

		virtual bool isValid() const = 0;

		const std::string getLabel() const;
		void setLabel(const std::string &);

	protected:

		Object();
		Object(GLenum);
		Object(const Object &);
		Object(Object &&);
		Object & operator=(const Object &) { return *this; }
		Object & operator=(Object &&) { return *this; }

		GLuint m_name;
		GLenum m_identifier;

};

} // namespace gl

#endif // _GL_OBJECT_
