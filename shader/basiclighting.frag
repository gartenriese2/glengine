#version 420 core

layout(location = 0) out vec4 result;

in vec4 color;
in vec3 normal_World;
in vec3 position_World;

uniform vec3 ambientLight;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec3 lightColor;
uniform vec3 viewDir;
uniform float shininess;
uniform float strength;
uniform float attenuation;

void main() {

	vec3 fragToLight = normalize(lightPos - position_World);
	vec3 fragNormal = normalize(normal_World);
	vec3 fragToCam = normalize(camPos - position_World);

	float diffuse = max(0.f, dot(fragNormal, fragToLight));
	
	float specular = max(0.f, dot(reflect(-fragToLight, fragNormal), fragToCam));
	if (diffuse == 0.f) specular = 0.f;
	else specular = pow(specular, shininess) * strength;

	float dist = length(position_World - lightPos);
	float quadraticAttenuation = min(1.f, 1.f / (attenuation * dist * dist));

	vec3 scatteredLight = ambientLight + lightColor * diffuse * quadraticAttenuation;

	vec3 reflectedLight = lightColor * specular * quadraticAttenuation;

	result = vec4(min(color.rgb * scatteredLight + reflectedLight, vec3(1.f)), color.a);

}