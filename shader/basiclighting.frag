#version 420 core

layout(location = 0) out vec4 result;

in vec4 color;
in vec3 normal_World;

uniform vec3 ambientLight;
uniform vec3 lightDir;
uniform vec3 lightColor;

uniform mat4 viewMat;

void main() {

	float diffuse = max(0.f, dot(normalize(normal_World), -lightDir));
	// float specular = max(0.f, dot(reflect(-lightDir, normalize(normal_World)), ))

	vec3 scatteredLight = ambientLight + lightColor * diffuse;

	// vec3 reflectedLight = lightColor * (diffuse == 0.f)

	result = vec4(min(color.rgb * scatteredLight , vec3(1.f)), color.a);
	// result = vec4(reflect(-lightDir, normalize(normal_World)), 1.f);

}