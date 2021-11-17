#version 450 core

layout(location = 0) out vec4 color;
//in vec3 v_textCoord;
in vec4 u_col;
in vec2 u_textPos;
flat in float u_textSlot;

uniform float time;
//uniform sampler2D ourTexture;
uniform sampler2D u_textures[32];

void main()
{
	if (u_textSlot == -1.0)
	{
		float timeSin = (sin(time * 10) / 2f) + 1.0f;
		vec4 color1 = vec4(u_col.x * timeSin, u_col.y * timeSin, u_col.z * timeSin, 1.0);
		color = color1;
	}
	else
	{
		color = texture(u_textures[int(u_textSlot)], u_textPos);
	}
}