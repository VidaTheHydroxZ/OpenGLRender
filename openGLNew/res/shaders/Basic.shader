#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 triangleColor;

out vec3 Color;
out vec3 outputPosition;

uniform mat4 u_MVP; // model view projection matrix

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    outputPosition = position;
    Color = triangleColor;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 Color;
in vec3 outputPosition;

//uniform vec4 u_Color;
//uniform sampler2D u_Texture;
//uniform vec4 u_Texture;

void main()
{
    //vec4 texColor = texture(u_Texture, v_TexCoord);
    color = vec4(outputPosition, 1.0);
};
