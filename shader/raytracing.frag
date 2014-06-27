#version 430 core

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec3 position;
layout(location = 2) out vec3 reflectedRay;

in vec4 color;
in vec3 normal_World;
in vec3 position_World;

uniform vec3 camPos;
uniform vec3 viewDir;
uniform int lightDataSize;

struct lightData {
	
	vec4 bools; // isEnabled, isLocal, isSpot, 0
	vec4 position;
	vec4 color;
	vec4 ambient;
	vec4 direction;
	vec4 attenuation; // constant, linear, quadratic, 0
	vec4 spot; // spotCosCutoff, spotExponent, 0, 0
	
};

struct materialData {

	vec3 emission;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

};

layout(std430, binding = 0) buffer LightBuffer {
	lightData lights[];
};

uniform	materialData material;

void main() {

	reflectedRay = normalize(reflect(position_World - camPos, normalize(normal_World)));

	position = position_World;

	vec3 scatteredLight = vec3(0.f);
	vec3 reflectedLight = vec3(0.f);

	vec3 fragNormal = normalize(normal_World);
	vec3 fragToCam = normalize(camPos - position_World);

	for (int i = 0; i < lightDataSize; ++i) {

		if (lights[i].bools.x == 0.f) continue;

		float diffuse = 0.f;
		float specular = 0.f;
		float attenuation = 1.f;

		if (lights[i].bools.y == 0.f) {
			// directional light

			vec3 lightDir = normalize(-lights[i].direction.xyz);

			diffuse = max(0.f, dot(fragNormal, lightDir));

			specular = max(0.f, dot(reflect(-lightDir, fragNormal), fragToCam));

		} else {
			// local light

			vec3 fragToLight = lights[i].position.xyz - position_World;
			float dist = length(fragToLight);

			attenuation = 1.f / (lights[i].attenuation.x
										+ lights[i].attenuation.y * dist
										+ lights[i].attenuation.z * dist * dist);

			if (lights[i].bools.z == 1.f) {
				// spot light

				float spotCos = dot(normalize(fragToLight), normalize(-lights[i].direction.xyz));
				if (spotCos < lights[i].spot.x) attenuation = 0.f;
				else attenuation *= pow(spotCos, lights[i].spot.y);

			}

			diffuse = max(0.f, dot(fragNormal, -lights[i].direction.xyz));
			specular = max(0.f, dot(reflect(lights[i].direction.xyz, fragNormal), fragToCam));


		}

		if (diffuse == 0.f) specular = 0.f;
		else specular = pow(specular, material.shininess);

		scatteredLight += material.ambient * lights[i].ambient.xyz * attenuation
						+ material.diffuse * lights[i].color.xyz * vec3(diffuse) * min(attenuation, 1.f);
		reflectedLight += material.specular * lights[i].color.xyz * vec3(specular) * attenuation;

	}

	outColor = vec4(min(material.emission + color.rgb * scatteredLight + reflectedLight, 1.f), color.a);

}