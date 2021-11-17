#version 450 core

layout(location = 0) out vec4 color;

in vec2 u_textPos;

uniform vec3 u_col;

uniform sampler2D ourTexture;

void main()
{
	color = vec4(u_col, texture2D(ourTexture, u_textPos).a);
}