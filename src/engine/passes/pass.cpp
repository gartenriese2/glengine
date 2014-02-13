#include "pass.hpp"

Pass::Pass() {
}

void Pass::addObjects(const Object & obj) {

	m_objects.emplace_back(& obj);

}
