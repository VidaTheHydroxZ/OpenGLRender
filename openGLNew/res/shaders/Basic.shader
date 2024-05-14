#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 TextureCoordinates;

uniform mat4 u_MVP; // model view projection matrix

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    TextureCoordinates = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 TextureCoordinates;

uniform sampler2D MyTexture;
uniform sampler2D MyTexture2;

void main()
{
    color = mix(texture(MyTexture, TextureCoordinates), texture(MyTexture2, vec2(TextureCoordinates.x, TextureCoordinates.y)), 0.2);
}
