#version 420 core

layout(location = 0) out vec4 result;

in vec4 color;

void main() {

	result = color;

}