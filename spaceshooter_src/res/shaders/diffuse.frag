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
    vec3 lightDirection = vec3(0.0, -1.0, -1.0);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-lightDirection);

    //diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);

    FragColor = vec4(diff * color * vec3(1.0), 1.0);
}