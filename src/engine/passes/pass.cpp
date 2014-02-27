#include "pass.hpp"

Pass::Pass() {
}

void Pass::addObjects(ObjectID id) {

	m_objects.emplace_back(id);

}
