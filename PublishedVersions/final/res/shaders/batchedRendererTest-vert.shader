#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 v_col;
layout(location = 2) in vec2 v_textPos;
layout(location = 3) in float v_textSlot;

out vec4 u_col;
out vec2 u_textPos;
out float u_textSlot;

uniform mat4 projection;
void main()
{
	gl_Position = projection * vec4(position, 1.0);
	u_col = v_col;
	u_textPos = v_textPos;
	u_textSlot = v_textSlot;
}