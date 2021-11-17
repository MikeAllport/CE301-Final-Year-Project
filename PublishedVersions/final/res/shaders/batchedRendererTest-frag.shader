#version 450 core

layout(location = 0) out vec4 color;
in vec4 u_col;
in vec2 u_textPos;
in flat float u_textSlot;

uniform float time;
uniform sampler2D textures[32];

void main()
{
	if (u_textSlot == -1.0)
	{
		color = u_col;
	}
	else
	{
		color = texture(textures[int(u_textSlot)], u_textPos);
	}
}