#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;

out vec3 Normal;
out vec2 TextureCoordinates;
out vec3 FragmentPosition;

uniform mat4 modelMatrix;
uniform mat4 u_MVP; // model view projection matrix


void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    Normal = mat3(transpose(inverse(modelMatrix))) * normals;
    FragmentPosition = vec3(modelMatrix * vec4(position, 1.0));
    TextureCoordinates = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 FragmentPosition;
in vec3 Normal;
in vec2 TextureCoordinates;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewerPosition;

void main()
{
    float ambientStrength = 0.1;
    float specularStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 viewDir = normalize(viewerPosition - FragmentPosition);

    vec3 norm = normalize(Normal);
    
    vec3 lightDir = normalize(lightPos - FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0);
}
