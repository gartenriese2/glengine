#ifndef _BUFFER_
#define _BUFFER_

#include "glincludes.hpp"
#include "globject.hpp"

#include <vector>

namespace gl {

class Buffer : public gl::Object {

	public:

		Buffer();
		Buffer(const Buffer &);
		Buffer(Buffer &&);
		Buffer & operator=(const Buffer &);
		Buffer & operator=(Buffer &&) &;
		virtual ~Buffer();

		virtual bool isValid() const override;

		GLuint getSize() const;

};

}

#endif // _BUFFER_