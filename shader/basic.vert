#version 420 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec3 inNormal;

out vec4 color;
out vec3 normal;

uniform mat4 MVP;
uniform mat4 MV_IT;

void main() {

	gl_Position = MVP * inPosition;
	color = inColor;
	normal = (MV_IT * vec4(inNormal, 1.f)).xyz;

}