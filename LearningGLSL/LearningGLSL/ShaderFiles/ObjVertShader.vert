#version 450 core
// in
layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec3 color;

// uniform values
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

// out
out VSOUT
{
	vec3 worldPos;
	vec3 normal;
	vec3 color;
}vsOut;

void main()
{
	gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
	vsOut.worldPos = vec3(modelMat * vec4(position, 1.0f));
	vsOut.normal = mat3(transpose(inverse(modelMat))) * normal;
	vsOut.color = color;
}