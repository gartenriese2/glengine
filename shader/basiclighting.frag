#version 420 core

layout(location = 0) out vec4 result;

in vec4 color;
in vec3 normal_World;

uniform vec3 ambientLight;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 viewDir;
uniform float shininess;
uniform float strength;

void main() {

	float diffuse = max(0.f, dot(normalize(normal_World), -lightDir));
	
	float specular = max(0.f, dot(reflect(-lightDir, normalize(normal_World)), viewDir));
	if (diffuse == 0.f) specular = 0.f;
	else specular = pow(specular, shininess);

	vec3 scatteredLight = ambientLight + lightColor * diffuse;

	vec3 reflectedLight = lightColor * specular * strength;

	result = vec4(min(color.rgb * scatteredLight + reflectedLight, vec3(1.f)), color.a);

}