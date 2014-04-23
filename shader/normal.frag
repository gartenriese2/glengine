#version 420 core

layout(location = 0) out vec4 result;

in vec3 normal_View;

void main() {

	result = vec4(normalize(normal_View), 1.f);

}