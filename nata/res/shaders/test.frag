#version 330 core

in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixing;

void main()
{
	vec2 reverseCoords = vec2(1 - TexCoord.x, TexCoord.y);
	vec2 centeredCoords = vec2(reverseCoords.x + 0.5, reverseCoords.y + 0.5);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, centeredCoords), mixing) * vec4(Color, 1.0);
} 