#version 420 core

layout(location = 0) out vec4 result;

uniform sampler2D tex;

void main() {

	result = texelFetch(tex, ivec2(gl_FragCoord.xy), 0);

}