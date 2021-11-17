#version 450 core

layout(location = 0) out vec4 color;
in flat vec4 u_col;

void main()
{
	color = u_col;
}