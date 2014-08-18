#ifndef _IBO_
#define _IBO_

#include "glincludes.hpp"

#include <vector>

namespace gl {

class IBO {

	public:

		IBO();
		IBO(const IBO &);
		IBO & operator=(const IBO &) &;
		IBO(IBO &&);
		IBO & operator=(IBO &&) &;
		~IBO();

		operator GLuint() const { return m_name; }

		bool isValid() const;

		GLuint getSize() const;

		void insertData(const std::vector<GLushort> &);

	private:

		GLuint m_name;

};

} // namespace gl

#endif // _IBO_
