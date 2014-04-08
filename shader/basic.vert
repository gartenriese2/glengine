#version 420 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec3 inNormal;

out vec4 color;
out vec3 normal_View;
out vec3 normal_World;

uniform mat4 MVP;
uniform mat4 MV_IT;
uniform mat4 M;

void main() {

	gl_Position = MVP * inPosition;
	color = inColor;
	normal_View = (MV_IT * vec4(inNormal, 1.f)).xyz;
	normal_World = (M * vec4(inNormal, 1.f)).xyz;

}