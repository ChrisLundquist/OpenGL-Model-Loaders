#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 color;

smooth out vec4 fColor;
void main()
{
    gl_Position = vec4(position,1.0f);
    fColor = vec4(position,1.0f);
}
