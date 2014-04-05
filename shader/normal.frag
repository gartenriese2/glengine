#version 420 core

layout(location = 0) out vec4 result;

in vec3 normal;

void main() {

	result = normalize(vec4(normal, 1.f));

}