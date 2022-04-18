#version 330 core

in vec3 WorldPos;

out vec4 FragColor;

uniform samplerCube environmentMap;

const float Pi = 3.14159265359;

void main()
{
	vec3 N = normalize(WorldPos);
	vec3 irradiance = vec3(0.0f);

	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	vec3 right = normalize(cross(up, N));
	up = normalize(cross(N, right));

	float sampleDelta = 0.025f;
	float nrSamples = 0.0f;
	for (float phi = 0.0f; phi < 2.0f * Pi; phi += sampleDelta)
	{
		for (float theta = 0.0f; theta < 0.5f * Pi; theta += sampleDelta)
		{
			vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
			vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;

			irradiance += texture(environmentMap, sampleVec).rgb * cos(theta) * sin(theta);
			nrSamples++;
		}
	}
	irradiance = Pi * irradiance * (1.0f / float(nrSamples));
	FragColor = vec4(irradiance, 1.0f);
}