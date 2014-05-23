#version 420 core

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec3 position;
layout(location = 2) out vec3 reflectedRay;

in vec4 color;
in vec3 normal_World;
in vec3 position_World;

uniform vec3 camPos;

void main() {

	vec3 fragToCam = position_World - camPos;
	reflectedRay = normalize(reflect(fragToCam, normalize(normal_World)));

	outColor = color;
	position = position_World;

}