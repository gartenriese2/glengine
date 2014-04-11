#ifndef _PASS_
#define _PASS_

#include "../gl/program.hpp"
#include "../camera.hpp"
#include "../debug.hpp"

#include <set>
#include <vector>
#include <memory>

class Light;

class Pass {
	
	public:
	
		Pass() {}
		Pass(const Pass &) = delete;
		Pass(Pass &&) = delete;
		Pass & operator=(const Pass &) = delete;
		Pass & operator=(Pass &&) = delete;

		virtual void draw(const Camera &) {}
		virtual void draw(const Camera &, const std::vector<std::shared_ptr<Light>>) {}

		void addObjects(std::set<unsigned long> set) { m_objects.insert(set.cbegin(), set.cend()); }
		void removeObject(unsigned long id) { m_objects.erase(id); }

	protected:

		Program m_program;
		std::set<unsigned long> m_objects;
};

#endif // _PASS_