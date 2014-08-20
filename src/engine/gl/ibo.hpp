#ifndef _IBO_
#define _IBO_

#include "glincludes.hpp"
#include "buffer.hpp"

#include <vector>

namespace gl {

class IBO : public gl::Buffer {

	public:

		IBO() {}
		IBO(const IBO &);
		IBO(IBO &&) {}
		IBO & operator=(const IBO &) &;
		IBO & operator=(IBO &&) { return *this; }
		~IBO() {}

		void insertData(const std::vector<GLushort> &);

};

} // namespace gl

#endif // _IBO_
