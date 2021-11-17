#version 450 core

layout(location = 0) out vec4 color;

in vec4 u_col;
in flat float u_textSlot;
in vec2 u_textPos;

uniform sampler2D textures[32];

uniform float time;
uniform float quadCount;


void main()
{
	if (u_textSlot >= 0)
	{
		vec4 textCol = texture(textures[int(u_textSlot)], u_textPos);
		color = textCol;
	}
	else
	{
		float timeSin = (sin(time * 10) / 2f) + 1.0f;
		color = vec4(u_col.x * timeSin, u_col.y * timeSin, u_col.z * timeSin, 1.0);
	}
}