#include "program.hpp"

#include "../debug.hpp"

#include <vector>

Program::Program()
  : m_linked(false)
{

	m_program = glCreateProgram();
	if (m_program == 0) {
		Debug::log("Error creating Program!");
	}

}

Program::~Program() {

	glDeleteProgram(m_program);

}

void Program::attachShader(const Shader & shader) {
	
	glAttachShader(m_program, shader());

}

void Program::use() {

	if (!m_linked) {

		glLinkProgram(m_program);

		GLint success = GL_FALSE;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		
		if (!success) {

			GLint logSize = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);

			std::vector<char> tmp;
			tmp.reserve(logSize);
			glGetProgramInfoLog(m_program, logSize, NULL, &tmp[0]);

			Debug::log("Program linking failed with the following error:\n");
			if (tmp.size() != 0) Debug::log(tmp[0]);
			exit(0);

		}

		m_linked = true;

	}

	glUseProgram(m_program);

}

void Program::transmit(const std::string & name, const glm::mat4 & value) {

	GLuint handle;
	if (m_handles.count(name) == 0) {
		handle = glGetUniformLocation(m_program, name.c_str());
		m_handles[name] = handle;
	} else {
		handle = m_handles[name];
	}

	glUniformMatrix4fv(handle, 1, GL_FALSE, & value[0][0]);

}
