#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Tangent;
in vec3 Bitangent;

uniform vec3 color;

void main()
{
	FragColor = vec4(color, 1.0);
} 