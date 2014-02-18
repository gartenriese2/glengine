#ifndef _LOOP_
#define _LOOP_

#include "glincludes.hpp"

class Loop {

	public:

		Loop();
		Loop(const Loop &) = delete;
		Loop(Loop &&) = delete;
		Loop & operator=(const Loop &) = delete;
		Loop & operator=(Loop &&) = delete;

		void start(GLFWwindow *) const;

};

#endif // _LOOP_