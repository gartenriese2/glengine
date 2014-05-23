#version 420 core

layout(location = 0) in vec4 inPosition;

void main() {

	gl_Position = inPosition;

}