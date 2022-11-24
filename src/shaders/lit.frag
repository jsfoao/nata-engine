#version 330 core
out vec4 FragColor;

struct PointLight 
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 color;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 color;
};

#define NR_POINT_LIGHTS 2

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform float shininess;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 color);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = CalcDirLight(dirLight, norm, viewDir, dirLight.color);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, pointLights[i].color);    
    }    
    FragColor = vec4(result, 1.0);

}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(diffuse0, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse0, TexCoords)) * color;
    vec3 specular = light.specular * spec * vec3(texture(specular0, TexCoords)) * color;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 color)
{   
    vec3 lightDir = normalize(-light.direction);
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(diffuse0, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse0, TexCoords)) * color;
    vec3 specular = light.specular * spec * vec3(texture(specular0, TexCoords)) * color;
    return (ambient + diffuse + specular);
}