#ifndef _RENDER_
#define _RENDER_

#include <vector>

using ObjectID = unsigned long;

class Render {

	public:

		Render() {}
		Render(const Render &) = delete;
		Render(Render &&) = delete;
		Render & operator=(const Render &) = delete;
		Render & operator=(Render &&) = delete;

		virtual void draw() = 0;
		virtual void addObjects(std::vector<ObjectID>) = 0;

};

#endif // _RENDER_