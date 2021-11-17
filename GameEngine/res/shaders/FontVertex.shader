#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textPos;

out vec2 u_textPos;

uniform mat4 projection;
uniform mat4 model;
void main()
{
	gl_Position = vec4(position, 0.0f, 1.0f);
	u_textPos = textPos;
}