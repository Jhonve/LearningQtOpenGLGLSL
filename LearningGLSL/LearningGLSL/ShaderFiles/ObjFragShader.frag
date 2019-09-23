#version 450 core

in VSOUT
{
	vec3 worldPos;
	vec3 normal;
	vec3 color;
}fsIn;

uniform vec3 alightPos;
uniform vec3 blightPos;
uniform vec3 viewPos;

out vec4 fragColor;

float computeDiff(vec3 normal, vec3 lightDir);
float computeSpec(vec3 lightDir, vec3 viewDir);

void main()
{
	float ambientWeight = 0.3;
	float specularWeight = 0.3;
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

	vec3 ambient = ambientWeight * lightColor;

	vec3 alightDir = normalize(alightPos - fsIn.worldPos);
	vec3 blightDir = normalize(blightPos - fsIn.worldPos);
	vec3 viewDir = normalize(viewPos - fsIn.worldPos);

	// diff
	vec3 normal = normalize(fsIn.normal);
	float diff = computeDiff(normal, alightDir) + computeDiff(normal, blightDir);
	vec3 diffuse = diff * lightColor;

	// specular  Blinn-Phong
	float spec = computeSpec(alightDir, viewDir) + computeSpec(blightDir, viewDir);
	vec3 specular = spec * specularWeight * lightColor;

	vec3 total = ambient + diffuse + specular;

	// fragColor = vec4(vec3(1.0, 1.0f, 1.0f) * total, 1.0f);
	fragColor = vec4(fsIn.color * total, 1.0f);
}

float computeDiff(vec3 normal, vec3 lightDir)
{
	return max(dot(lightDir, normal), 0.0f);
}

float computeSpec(vec3 lightDir, vec3 viewDir)
{
	vec3 halfwayDir = normalize(lightDir + viewDir);
	return pow(max(dot(viewDir, halfwayDir), 0.0f), 16.0f);
}
