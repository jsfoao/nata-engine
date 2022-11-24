#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D diffuse0;

void main()
{
	vec3 tex = vec3(texture(diffuse0, TexCoords));
	FragColor = vec4(tex, 1.0);
} 