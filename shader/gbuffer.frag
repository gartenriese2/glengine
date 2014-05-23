#version 420 core

layout(location = 0) out vec4 outColor;
layout(location = 3) out vec3 position;
layout(location = 2) out vec3 normal;
layout(location = 1) out float depth;

in vec4 color;
in vec3 normal_World;
in vec3 position_World;

void main() {

	outColor = color;
	position = position_World;
	normal = normal_World;
	depth = gl_FragCoord.z;

}