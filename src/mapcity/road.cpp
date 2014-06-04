#include "road.hpp"

#include "../engine/debug.hpp"

constexpr float k_width = 5.f;
constexpr float k_height = 0.1f;
constexpr float k_smoothness = 250.f;
const glm::vec3 k_color {0.8f, 0.8f, 0.f};

Road::Road(const std::vector<glm::vec2> & points, WindowID & win, RenderID & render)
  : m_points(points)
{

	for (unsigned int i = 0; i < points.size() - 1; ++i) {

		glm::vec3 start {points[i][0], k_height, points[i][1]};
		glm::vec3 end {points[i + 1][0], k_height, points[i + 1][1]};
		glm::vec3 beforeStart, afterEnd;
		if (i == 0) {
			beforeStart = start;
		} else {
			beforeStart = {points[i - 1][0], k_height, points[i - 1][1]};
		}

		if (i == points.size() - 2) {
			afterEnd = end;
		} else {
			afterEnd = {points[i + 2][0], k_height, points[i + 2][1]};
		}
		glm::vec3 dirStart = glm::normalize(end - beforeStart);
		glm::vec3 dirEnd = glm::normalize(afterEnd - start);

		int steps = glm::length(end - start) / 0.1f;

		m_objects.emplace_back(win.createSpline(start, dirStart, end, dirEnd, {0.f, 1.f, 0.f},
			k_width, k_width, steps, k_smoothness, k_color));
		render.addObjects({m_objects.back()});

	}

}
