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

	}

	glUseProgram(m_program);

}
