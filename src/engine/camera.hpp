#ifndef _CAMERA_
#define _CAMERA_

#include "glmincludes.hpp"

class Camera {

	public:

		Camera(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float, int, int, float, float);
		// Camera(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float, float, float, float);
		Camera(Camera &&) = default;
		Camera & operator=(Camera &&) = default;

		const glm::mat4 & getViewMat() const { return m_view; }
		const glm::mat4 & getProjMat() const { return m_proj; }

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

		void reset();
		void move(float, float, float);
		// void rotate(float, float);
		// void rotateAround(float);
		// bool zoom(int);

	private:

		int m_width;
		int m_height;

		float m_fov;

		glm::mat4 m_view;
		glm::mat4 m_proj;

		glm::vec3 m_pos;
		glm::vec3 m_dir;
		glm::vec3 m_up;

		glm::vec3 m_initPos;
		glm::vec3 m_initDir;
		glm::vec3 m_initUp;

};

#endif